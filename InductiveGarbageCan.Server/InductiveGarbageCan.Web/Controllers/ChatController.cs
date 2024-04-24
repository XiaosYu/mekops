using InductiveGarbageCan.Web.Services.Chat;
using InductiveGarbageCan.Web.Services.Repository;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;
using System.Text;
using System.Text.Json;

namespace InductiveGarbageCan.Web.Controllers
{
    [Route("api/[controller]/[action]")]
    [ApiController]
    public class ChatController(IChat chat, IQueryer queryer) : ControllerBase
    {
        private readonly IChat _chat = chat;
        private readonly IQueryer _queryer = queryer;

        [HttpPost]
        public async Task<IActionResult> Chat([FromBody]List<ChatMessage> messages)
        {
            var replay = await _chat.GetReplyAsync(messages);
            return Ok(replay);
        }

        [HttpPost]
        public async Task<IActionResult> AnalyseData([FromBody] List<ChatMessage> messages)
        {
            var stringBuilder = new StringBuilder();
            stringBuilder.AppendLine("以下数据是我们小区的垃圾回收站每个垃圾桶的实时数据，请对所有数据做出简单的分析,如居民生活大概是怎样的，丢垃圾的频次怎样的，垃圾分布怎样的");
            var text = string.Join(',', _queryer
                            .ListData()
                            .OrderBy(s => s.TriggerTime)
                            .TakeLast(100)
                            .Select(s => $"{s.TriggerTime}在{s.DisplayTriggerCans}中发生了{s.DisplayEventType}"));

            stringBuilder.AppendLine(text);

            var chatMessage = new ChatMessage()
            {
                Role = "user",
                Content = stringBuilder.ToString()
            };

            messages.Add(chatMessage);

            var relay = await _chat.GetReplyAsync(messages);
            return Ok(relay);
        }
    }
}
