using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InductiveGarbageCan.Database
{
    public static partial class DbContextExtensions
    {
        public static IServiceCollection AddDbContextWithSqlite<TContext>(this IServiceCollection services, string connectString) where TContext : DbContext, new()
        {
            DbContextOptionsBuilder<TContext> builder = new();
            builder.UseSqlite(connectString);
            var options = builder.Options;
            var context = Activator.CreateInstance(typeof(TContext), args: [options]) as TContext;
            context?.Database.EnsureCreated();
            services.AddDbContext<TContext>(options => options.UseSqlite(connectString));
            return services;
        }
    }
}
