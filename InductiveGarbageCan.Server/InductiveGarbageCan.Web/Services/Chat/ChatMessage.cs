using System.Text.Json.Serialization;

namespace InductiveGarbageCan.Web.Services.Chat
{
    public class ChatMessage
    {
        [JsonPropertyName("role")]
        public string Role { get; set; }

        [JsonPropertyName("content")]
        public string Content { get; set; }
    }
}
