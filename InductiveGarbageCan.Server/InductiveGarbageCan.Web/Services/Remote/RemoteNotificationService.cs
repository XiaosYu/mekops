using InductiveGarbageCan.Web.Services.Hubs;
using Microsoft.AspNetCore.SignalR;

namespace InductiveGarbageCan.Web.Services.Remote
{
    public class RemoteNotificationService(IHubContext<MainHub> hub) : IRemoteService
    {
        private readonly IHubContext<MainHub> _hub = hub;

        public async void Received(RemoteEvent @event)
        {
            await _hub.Clients.All.SendAsync("ReceiveNotification", (int)@event.EventType, 
                (int)@event.TriggerCans, @event.TriggerTime);
        }
    }
}
