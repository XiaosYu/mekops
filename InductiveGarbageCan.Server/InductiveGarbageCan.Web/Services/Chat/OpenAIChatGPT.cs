
using System.Net;
using System.Text.Json.Nodes;

namespace InductiveGarbageCan.Web.Services.Chat
{
    public class OpenAIChatGPT : IChat
    {
        private static string Uri;
        private static string Authorization;
        private readonly HttpClient _client = new();

        public async Task<ChatMessage?> GetReplyAsync(List<ChatMessage> messages)
        {
            var request = new HttpRequestMessage();
            request.RequestUri = new Uri(Uri);
            request.Headers.Add("Authorization", $"Bearer {Authorization}");

            var body = new
            {
                model = "gpt-3.5-turbo",
                messages = messages
            };

            request.Content = JsonContent.Create(body);
            request.Method = HttpMethod.Post;

            var response = await _client.SendAsync(request);
            if (!response.IsSuccessStatusCode) return null;
            else
            {
                var content = await response.Content.ReadFromJsonAsync<JsonObject>();
                var replay = content!["choices"]![0]!["message"]!["content"]!.ToString();
                return new ChatMessage()
                {
                    Role = "assistant",
                    Content = replay
                };
            }
        }
    }
}
