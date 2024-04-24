using BootstrapBlazor.Components;
using InductiveGarbageCan.App.Services;
using InductiveGarbageCan.Database.Log.Models;
using Microsoft.AspNetCore.Components;
using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InductiveGarbageCan.App.Components.Pages
{
    public partial class Counter
    {
        [NotNull]
        [Inject]
        public DataService? DataService { get; set; }

        [NotNull]
        private Table<TbLog>? MainTable { get; set; }

        private TbLog SearchModel = new();

        private List<SelectedItem> SelectedEventType = new List<string>() { "预警事件", "丢垃圾事件", "清理垃圾事件" }.Select(s=>new SelectedItem(s, s)).ToList();
        private List<SelectedItem> SelectedTriggerCans = new List<string>() { "湿垃圾", "可回收垃圾", "干垃圾", "有害垃圾" }.Select(s => new SelectedItem(s, s)).ToList();
        private DateTime StartDate { get; set; } = default;
        private DateTime EndDate { get; set; } = default;

        private async Task<QueryData<TbLog>> OnSearchModelQueryAsync(QueryPageOptions options)
        {
            var items = await DataService.ListDataAsync();

            if(items == null)
            {
                return new QueryData<TbLog>()
                {
                    Items = items,
                    TotalCount = 0,
                    IsSorted = false,
                    IsFiltered = false,
                    IsSearch = false
                };
            }

            if (!string.IsNullOrEmpty(options.SearchText))
            {
                if(options.SearchText != "*")
                    items = items.Where(i => (i.Id.ToString()?.Contains(options.SearchText, StringComparison.OrdinalIgnoreCase) ?? false) || (i.DisplayEventType?.Contains(options.SearchText, StringComparison.OrdinalIgnoreCase) ?? false || (i.DisplayTriggerCans?.Contains(options.SearchText, StringComparison.OrdinalIgnoreCase)  ?? false)));
            }
            else
            {
                // 处理自定义搜索条件
                if (!string.IsNullOrEmpty(SearchModel.DisplayTriggerCans) && SearchModel.DisplayTriggerCans != "任意")
                {
                    items = items.Where(i => i.DisplayTriggerCans == SearchModel.DisplayTriggerCans);
                }
                if (!string.IsNullOrEmpty(SearchModel.DisplayEventType) && SearchModel.DisplayEventType != "任意")
                {
                    items = items.Where(i => i.DisplayEventType == SearchModel.DisplayEventType);
                }
                if(StartDate != default && EndDate != default)
                {
                    items = items.Where(i => StartDate < i.TriggerTime && i.TriggerTime < EndDate);
                }
        
            }

            // 设置记录总数
            var total = items.Count();
            // 内存分页
            items = items.Skip((options.PageIndex - 1) * options.PageItems).Take(options.PageItems).ToList();
            return new QueryData<TbLog>()
            {
                Items = items,
                TotalCount = total,
                IsSorted = true,
                IsFiltered = options.Filters.Any(),
                IsSearch = options.Searches.Any(),
                IsAdvanceSearch = options.AdvanceSearches.Any()
            };
        }
    }

}
