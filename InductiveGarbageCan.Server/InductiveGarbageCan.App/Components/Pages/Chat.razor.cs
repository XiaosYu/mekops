using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Azure.AI.OpenAI;
using BootstrapBlazor.Components;
using InductiveGarbageCan.App.Services;
using Microsoft.AspNetCore.Components;
using Microsoft.JSInterop;

namespace InductiveGarbageCan.App.Components.Pages
{
    public partial class Chat
    {
        [Inject]
        [NotNull]
        public IJSRuntime? JSRuntime { get; set; }

        [Inject]
        [NotNull]
        public ChatService? ChatService { get; set; }

        private IJSObjectReference? module;

        public string Id { get; set; } = "mychat";

        protected override async Task OnInitializedAsync()
        {
            await base.OnInitializedAsync();
        }
        protected override async Task OnAfterRenderAsync(bool firstRender)
        {
            await base.OnAfterRenderAsync(firstRender);

            if(firstRender)
            {
                module = await JSRuntime.InvokeAsync<IJSObjectReference>("import", "./Components/Pages/Chat.razor.js");
                await module.InvokeVoidAsync("init");
            }
            else
            {
                if (module != null)
                    await module.InvokeVoidAsync("scroll", [Id]);
            }
        }

    

     

        private List<AzureOpenAIChatMessage> Messages { get; } = [
            new AzureOpenAIChatMessage() { Role = ChatRole.User, Content = "你好，你现在是一个垃圾回收站的辅导机器人，你只能回答环境保护、垃圾分类相关的知识，其它问题不予回答"},
            new AzureOpenAIChatMessage() { Role = ChatRole.Assistant, Content = "好的，我现在是垃圾回收站的辅导机器人，我只会回答与环境保护、垃圾分类相关的知识" }
            ];

        private string? Context { get; set; }

        private static string? GetStackClass(ChatRole role) => CssBuilder.Default("msg-stack").AddClass("msg-stack-assistant", role == ChatRole.Assistant).Build();


        private async Task OnClickExtensions(DialButtonItem item)
        {
            if (item.Value == "data")
                await GetDataCompletionsAsync();
        }

        private async Task GetDataCompletionsAsync()
        {
            Messages.Clear();
            Messages.AddRange([
            new AzureOpenAIChatMessage() { Role = ChatRole.User, Content = "你好，你现在是一个垃圾回收站的辅导机器人，你只能回答环境保护、垃圾分类相关的知识，其它问题不予回答" },
                new AzureOpenAIChatMessage() { Role = ChatRole.Assistant, Content = "好的，我现在是垃圾回收站的辅导机器人，我只会回答与环境保护、垃圾分类相关的知识" }
            ]);

            var msg = new AzureOpenAIChatMessage()
            {
                Role = ChatRole.Assistant,
                Content = "Thinking ..."
            };
            Messages.Add(msg);
            StateHasChanged();

            bool first = true;

            var chatMessage = await ChatService.GetDataReply(Messages);
            if (chatMessage != null)
            {
                if (first)
                {
                    first = false;
                    msg.Content = string.Empty;
                }

                await Task.Delay(50);
                if (!string.IsNullOrEmpty(chatMessage.Content))
                {
                    msg.Content += chatMessage.Content;
                    StateHasChanged();
                }
            }


        }

        private async Task GetCompletionsAsync()
        {
            Context = Context?.TrimEnd('\n') ?? string.Empty;
            if (!string.IsNullOrEmpty(Context))
            {
                var context = Context;
                Context = string.Empty;
                Messages.Add(new AzureOpenAIChatMessage() { Role = ChatRole.User, Content = context });
                var msg = new AzureOpenAIChatMessage()
                {
                    Role = ChatRole.Assistant,
                    Content = "Thinking ..."
                };
                Messages.Add(msg);
                StateHasChanged();

                bool first = true;

                var chatMessage = await ChatService.GetReply(Messages);
                if(chatMessage != null)
                {
                    if (first)
                    {
                        first = false;
                        msg.Content = string.Empty;
                    }

                    await Task.Delay(50);
                    if (!string.IsNullOrEmpty(chatMessage.Content))
                    {
                        msg.Content += chatMessage.Content;
                        StateHasChanged();
                    }
                }
            }
        }
    }
}
