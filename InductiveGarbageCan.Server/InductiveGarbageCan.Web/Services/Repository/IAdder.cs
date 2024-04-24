using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InductiveGarbageCan.Web.Services.Repository
{
    public interface IAdder
    {
        public bool Add(int eventType, int triggerCans, DateTime triggerTime);
    }
}
