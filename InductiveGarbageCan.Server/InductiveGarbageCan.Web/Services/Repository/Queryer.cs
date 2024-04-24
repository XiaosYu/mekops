using InductiveGarbageCan.Database.Log.Models;
using InductiveGarbageCan.Web.Services.Remote;
using System.Linq.Expressions;

namespace InductiveGarbageCan.Web.Services.Repository
{
    public class Queryer(IRepository<TbLog> repository) : IQueryer
    {
        private readonly IRepository<TbLog> _repository = repository;

        public IEnumerable<TbLog> ListData() => _repository.GetAll();

        public IEnumerable<TbLog> QueryByEventType(int eventType) => _repository.Query(s => s.EventType == eventType);

        public IEnumerable<TbLog> QueryByTriggerCans(int triggerCans) => _repository.Query(s => s.TriggerCans == triggerCans);

        public IEnumerable<TbLog> QueryByTriggerTime(DateTime date) => _repository.Query(s=>s.TriggerTime.Date == date);

        public IEnumerable<TbLog> QueryByTriggerTimeSpan(DateTime startTime, DateTime endTime) => _repository.Query(s => startTime < s.TriggerTime && s.TriggerTime < endTime);
    }
}
