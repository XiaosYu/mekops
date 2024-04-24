using Azure.AI.OpenAI;
using BootstrapBlazor.Components;
using InductiveGarbageCan.Database.Log.Models;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net.Http.Json;
using System.Text;
using System.Text.Json.Nodes;
using System.Threading.Tasks;

namespace InductiveGarbageCan.App.Services
{
    public class ChatService(IHttpClientFactory factory): ServiceBase(factory)
    {
        public async Task<AzureOpenAIChatMessage?> GetReply(List<AzureOpenAIChatMessage> messages)
        {
            var body = messages.Select(s => new
            {
                role = s.Role.ToString(),
                content = s.Content
            });
            var result = await PostAsync<JsonObject>("Chat", "Chat", body);
            if (result != null)
            {
                var message = new AzureOpenAIChatMessage();
                message.Role = new ChatRole(result["Role"].ToString());
                message.Content = result["Content"].ToString();
                return message;
            }
            else return null;
        }

        public async Task<AzureOpenAIChatMessage?> GetDataReply(List<AzureOpenAIChatMessage> messages)
        {
            var body = messages.Select(s => new
            {
                role = s.Role.ToString(),
                content = s.Content
            });
            var result = await PostAsync<JsonObject>("Chat", "AnalyseData", body);
            if (result != null)
            {
                var message = new AzureOpenAIChatMessage();
                message.Role = new ChatRole(result["Role"].ToString());
                message.Content = result["Content"].ToString();
                return message;
            }
            else return null;
        }
    }
}
