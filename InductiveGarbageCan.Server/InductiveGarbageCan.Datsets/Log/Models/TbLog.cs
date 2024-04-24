using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

#nullable disable

namespace InductiveGarbageCan.Database.Log.Models
{
    public class TbLog
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public int Id { get; set; }

        public int EventType { get; set; }
        public int TriggerCans { get; set; }

        public DateTime TriggerTime { get; set; }

        [NotMapped]
        public string DisplayEventType
        {
            get => EventType switch
            {
                0 => "预警事件",
                1 => "丢垃圾事件",
                2 => "清理垃圾事件",
                _ => throw new Exception("未知事件")
            };
            set => EventType = (new List<string>() { "预警事件", "丢垃圾事件", "清理垃圾事件" }).IndexOf(value);
        }

        [NotMapped]
        public string DisplayTriggerCans
        {
            get => TriggerCans switch
            {
                0 => "湿垃圾",
                1 => "可回收垃圾",
                2 => "干垃圾",
                3 => "有害垃圾",
                _ => throw new Exception("未知垃圾类型")
            };
            set => TriggerCans = (new List<string>() { "湿垃圾", "可回收垃圾", "干垃圾", "有害垃圾" }).IndexOf(value);
        }
    }
}
