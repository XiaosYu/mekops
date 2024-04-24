using InductiveGarbageCan.Web.Services.Hubs;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.SignalR;

namespace InductiveGarbageCan.Web.Controllers
{
    [Route("api/[controller]/[action]")]
    [ApiController]
    public class TestController(IHubContext<MainHub> hub) : ControllerBase
    {
        private readonly IHubContext<MainHub> _hub = hub;

        [HttpGet]
        public async Task<IActionResult> SendNotification(int eventType, int triggerCans)
        {
            await _hub.Clients.All.SendAsync("ReceiveNotification", eventType, triggerCans, DateTime.Now);
            return Ok();
        }

        [HttpGet]
        public async Task<IActionResult> SendMessage(string message)
        {
            await _hub.Clients.All.SendAsync("ReceiveMessage", message);
            return Ok();
        }
    }
}
