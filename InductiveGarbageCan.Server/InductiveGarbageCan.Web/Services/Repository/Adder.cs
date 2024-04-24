using InductiveGarbageCan.Database.Log.Models;

namespace InductiveGarbageCan.Web.Services.Repository
{
    public class Adder(IRepository<TbLog> repository): IAdder
    {
        private IRepository<TbLog> _repository = repository;

        public bool Add(int eventType, int triggerCans, DateTime triggerTime)
        {
            _repository.Add(new TbLog()
            {
                EventType = eventType,
                TriggerCans = triggerCans,
                TriggerTime = triggerTime
            });
            return true;
        }

     
    }
}
