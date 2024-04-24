using Microsoft.AspNetCore.SignalR;

namespace InductiveGarbageCan.Web.Services.Hubs
{
    public class MainHub: Hub
    {
        public async Task SendNotification(int eventType, int triggerCans, DateTime triggerTime)
        {
            await Clients.All.SendAsync("ReceiveNotification", eventType, triggerCans, triggerTime);
        }

        public async Task SendMessage(string message)
        {
            await Clients.All.SendAsync("ReceiveMessage", message);
        }
    }
}
