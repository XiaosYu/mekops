using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InductiveGarbageCan.App.Services
{
    public class ForecastService(IHttpClientFactory factory) : ServiceBase(factory)
    {
        public async Task<DateTime> ForecastAsync() => await GetAsync<DateTime>("Forecast", "Forecast");
    }
}
