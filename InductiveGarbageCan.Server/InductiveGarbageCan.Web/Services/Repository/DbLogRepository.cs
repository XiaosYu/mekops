using InductiveGarbageCan.Database.Log;
using Microsoft.EntityFrameworkCore;
using System.Linq.Expressions;

namespace InductiveGarbageCan.Web.Services.Repository
{
    public class DbLogRepository<T>(DbLogContext context) : IRepository<T> where T : class
    {
        private readonly DbLogContext _context = context;
        public IEnumerable<T> GetAll()
        {
            return _context.Set<T>().ToList();
        }

        public void Add(T entity)
        {
            _context.Set<T>().Add(entity);
            _context.SaveChanges();
        }

        public void Update(T entity)
        {
            _context.Set<T>().Update(entity);
            _context.SaveChanges();
        }

        public void Delete(T entity)
        {
            _context.Set<T>().Remove(entity);
            _context.SaveChanges();
        }

        public List<T> Query(Expression<Func<T, bool>> predicate)
        {
            return _context.Set<T>().Where(predicate).ToList();
        }

        public T? QueryFirst(Expression<Func<T, bool>> predicate)
        {
            return _context.Set<T>().FirstOrDefault(predicate);
        }
    }
}
