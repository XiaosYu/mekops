using InductiveGarbageCan.Web.Services.Remote;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace InductiveGarbageCan.Web.Controllers
{
    [Route("api/[controller]/[action]")]
    [ApiController]
    public class CommandController(IBcpdSender sender) : ControllerBase
    {
        private readonly IBcpdSender _sender = sender;

        [HttpGet]
        public async Task<IActionResult> OpenCans(int cans)
        {
            var result = await _sender.SendAsync((byte)cans, 0);
            return result ? Ok() : BadRequest();
        }
    }
}
