namespace InductiveGarbageCan.Web.Services.ML
{
    public interface IDateTimeForecaster
    {
        public DateTime Forecast(IEnumerable<DateTime> data);
    }
}
