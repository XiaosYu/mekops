using InductiveGarbageCan.Database.Log.Models;
using InductiveGarbageCan.Web.Services.ML;
using InductiveGarbageCan.Web.Services.Repository;
using Microsoft.AspNetCore.Mvc;
using SQLitePCL;

namespace InductiveGarbageCan.Web.Controllers
{
    [ApiController]
    [Route("api/[controller]/[action]")]
    public class ForecastController(IQueryer queryer, IDateTimeForecaster forecaster) : ControllerBase
    {
        private readonly IDateTimeForecaster _forecaster = forecaster;
        private readonly IQueryer _queryer = queryer;

        [HttpGet]
        public IActionResult Forecast()
        {
            var data = _queryer.ListData().Where(s => s.EventType == 2).Select(s => s.TriggerTime);
            var predict = _forecaster.Forecast(data);
            return Ok(predict);
        }

    }
}
