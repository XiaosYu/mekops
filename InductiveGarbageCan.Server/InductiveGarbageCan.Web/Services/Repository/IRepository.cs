using System.Linq.Expressions;

namespace InductiveGarbageCan.Web.Services.Repository
{
    public interface IRepository<T>
    {
        public IEnumerable<T> GetAll();
        public void Add(T entity);
        public void Update(T entity);
        public void Delete(T entity);

        public List<T> Query(Expression<Func<T, bool>> predicate);
        public T? QueryFirst(Expression<Func<T, bool>> predicate);
    }
}
