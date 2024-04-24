using InductiveGarbageCan.Database.Log;
using InductiveGarbageCan.Web.Services.Repository;

namespace InductiveGarbageCan.Web.Services.Remote
{
    public class RemoteDataService(IAdder loger) : IRemoteService
    {
        private readonly IAdder _loger = loger;
        public void Received(RemoteEvent @event)
        {
            if(@event.EventType != EventType.Clear)
                _loger.Add((int)@event.EventType, (int)@event.TriggerCans, @event.TriggerTime);
            else
            {
                _loger.Add((int)@event.EventType, 0, @event.TriggerTime);
                _loger.Add((int)@event.EventType, 1, @event.TriggerTime);
                _loger.Add((int)@event.EventType, 2, @event.TriggerTime);
                _loger.Add((int)@event.EventType, 3, @event.TriggerTime);
            }
        }
    }
}
