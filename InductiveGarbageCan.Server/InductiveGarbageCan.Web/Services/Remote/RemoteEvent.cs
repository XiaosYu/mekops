namespace InductiveGarbageCan.Web.Services.Remote
{
    public class RemoteEvent
    {
        public DateTime TriggerTime { get; set; }
        public EventType EventType { get; set; }
        public TriggerCans TriggerCans { get; set; }

    }
}
