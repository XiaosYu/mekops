using InductiveGarbageCan.Database.Log.Models;
using InductiveGarbageCan.Web.Services.Remote;
using System.Linq.Expressions;

namespace InductiveGarbageCan.Web.Services.Repository
{
    public interface IQueryer
    {
        public IEnumerable<TbLog> ListData();
        public IEnumerable<TbLog> QueryByEventType(int eventType);
        public IEnumerable<TbLog> QueryByTriggerCans(int triggerCans);
        public IEnumerable<TbLog> QueryByTriggerTime(DateTime date);
        public IEnumerable<TbLog> QueryByTriggerTimeSpan(DateTime startTime, DateTime endTime);
    }
}
