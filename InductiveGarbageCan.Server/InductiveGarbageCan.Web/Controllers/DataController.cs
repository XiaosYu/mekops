using InductiveGarbageCan.Database.Log.Models;
using InductiveGarbageCan.Web.Services.Repository;
using Microsoft.AspNetCore.Mvc;

namespace InductiveGarbageCan.Web.Controllers
{
    [ApiController]
    [Route("api/[controller]/[action]")]
    public class DataController(IQueryer queryer) : ControllerBase
    {
        private readonly IQueryer _queryer = queryer;

        [HttpGet]
        public IActionResult IsConnected() => Ok(true);

        [HttpGet]
        public IActionResult ListData() => Ok(_queryer.ListData());

        [HttpGet]
        public IActionResult QueryQueryByEventType(int eventType) => Ok(_queryer.QueryByEventType(eventType));

        [HttpGet]
        public IActionResult QueryByTriggerCans(int triggerCans) => Ok(_queryer.QueryByTriggerCans(triggerCans));

        [HttpGet]
        public IActionResult QueryByTriggerTime(string triggerTime) => Ok(_queryer.QueryByTriggerTime(DateTime.Parse(triggerTime)));

        [HttpGet]
        public IActionResult QueryByTriggerTimeSpan(string startTime, string endTime) => Ok(_queryer.QueryByTriggerTimeSpan(DateTime.Parse(startTime), DateTime.Parse(endTime)));


    }
}
