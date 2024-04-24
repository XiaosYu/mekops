using InductiveGarbageCan.App.Services;
using InductiveGarbageCan.Database.Log.Models;
using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.SignalR.Client;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InductiveGarbageCan.App.Components.Pages
{
    public partial class Home: IAsyncDisposable
    {
        [Inject]
        [NotNull]
        public DataService? DataService { set; get; }

        [Inject]
        [NotNull]
        public ForecastService? ForecastService { set; get; }

        [Inject]
        [NotNull]
        public NotificationService? NotificationService { get; set; }


        private HubConnection? HubConnection;

        private List<TbLog> TbLogs { get; set; } = [];

        private DateTime NextClearTime { get; set; } = default;

        private List<int> CurrentCans { get; set; } = [0, 0, 0, 0];


        protected override async Task OnInitializedAsync()
        {
            if (!await DataService.IsConnected()) return;

            if (HubConnection == null)
            {
                HubConnection = new HubConnectionBuilder()
                    .WithUrl($"{ServiceBase.BaseUri}/main")
                    .Build();

                HubConnection.On<int, int, DateTime>("ReceiveNotification", async (eventType, triggerCans, triggerTime) =>
                {
                    await NotificationService.ToastSuccess("通知", $"{triggerTime:t}检测到{triggerCans switch
                    {
                        0 => "湿垃圾",
                        1 => "可回收垃圾",
                        2 => "干垃圾",
                        3 => "有害垃圾",
                        _ => "Unknown"
                    }}桶触发了{eventType switch
                    {
                        0 => "Warning",
                        1 => "Throw",
                        2 => "Clear",
                        _ => "Unknown"
                    }}事件");
                    await InvokeAsync(StateHasChanged);
                });

                HubConnection.On<string>("ReceiveMessage", async (message) =>
                {
                    await NotificationService.ToastSuccess("通知", $"{message}");
                    await InvokeAsync(StateHasChanged);
                });

                await HubConnection.StartAsync();
            }



            TbLogs.Clear();
            CurrentCans = [0, 0, 0, 0];
            var totalData = await DataService.ListDataAsync();
            if (totalData != null)
            {
                TbLogs.AddRange(totalData);
                Stack<TbLog>[] stacks = [new(), new(), new(), new()];
                foreach(var log in TbLogs)
                {
                    if (log.EventType == 1)
                    {
                        stacks[log.TriggerCans].Push(log);
                    }
                    else
                    {
                        stacks[log.TriggerCans].Clear();
                    }
                }
                for (var i = 0; i < 4; i++)
                {
                    CurrentCans[i] = stacks[i].Count;
                }
                NextClearTime = await ForecastService.ForecastAsync();
            }

            await base.OnInitializedAsync();
        }

        public int GetCansCount(int cans) => TbLogs.Where(s => s.TriggerCans == cans).Count();

        public async ValueTask DisposeAsync()
        {
            if (HubConnection is not null)
            {
                await HubConnection.DisposeAsync();
            }
        }
    }
}
