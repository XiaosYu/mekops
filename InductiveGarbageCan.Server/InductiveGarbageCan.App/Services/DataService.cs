using InductiveGarbageCan.Database.Log.Models;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net.Http.Json;
using System.Text;
using System.Threading.Tasks;

namespace InductiveGarbageCan.App.Services
{
    public class DataService(IHttpClientFactory factory): ServiceBase(factory)
    {
        public async Task<bool> IsConnected() => await GetAsync<bool>("Data", "IsConnected");
        public async Task<IEnumerable<TbLog>?> ListDataAsync() => await GetAsync<IEnumerable<TbLog>>("Data", "ListData");
        public async Task<IEnumerable<TbLog>?> QueryByEventTypeAsync(int eventType) => await GetAsync<IEnumerable<TbLog>>("Data", "QueryByEventType", ["eventType"], [eventType]);
        public async Task<IEnumerable<TbLog>?> QueryByTriggerCansAsync(int triggerCans) => await GetAsync<IEnumerable<TbLog>>("Data", "QueryByTriggerCans", ["triggerCans"], [triggerCans]);
    }
}
