namespace InductiveGarbageCan.Web.Services.Remote
{
    public class BcpdProtocol : IProtocol<RemoteEvent>
    {
        public RemoteEvent? ParseBytesToEntity(byte[] bytes)
        {
          
            var @byte = bytes[0];
            var lowBits = @byte & 0b00001111;
            var hightBits = (@byte & 0b11110000) >> 4;

            if (hightBits != 0b1110) return null;

            var eventType = (lowBits & 1100) >> 2;
            var triggerCans = lowBits & 0011;

            var @event = new RemoteEvent
            {
                EventType = (EventType)eventType,
                TriggerCans = (TriggerCans)triggerCans,
                TriggerTime = DateTime.Now
            };
            return @event;
        }

        public byte[] ParseEntityToBytes(RemoteEvent value)
        {
            var hightBits = 0b11010000;
            var lowBits = (int)value.TriggerCans;
            lowBits = (int)value.EventType << 2 | lowBits;
            var @byte = hightBits | lowBits;
            return [(byte)@byte];
        }
    }
}
