using Microsoft.EntityFrameworkCore;
using InductiveGarbageCan.Database.Log.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InductiveGarbageCan.Database.Log
{
    public class DbLogContext : DbContext
    {
        public DbLogContext() { }
        public DbLogContext(DbContextOptions<DbLogContext> options) : base(options) { }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            base.OnConfiguring(optionsBuilder);
        }

        public DbSet<TbLog> TbLog { get; set; }



    }
}
