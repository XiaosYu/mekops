
using InductiveGarbageCan.DL;
using InductiveGarbageCan.Web.Services.Repository;

namespace InductiveGarbageCan.Web.Services.ML
{
    public class DotNetMLDateTimeForecaster: IDateTimeForecaster
    {
        private readonly MLTrainTaskBuilder _trainTaskBuilder = new();

        public DateTime Forecast(IEnumerable<DateTime> data)
        {
            if (data.Count() > 30)
            {
                var model = _trainTaskBuilder
                           .AddTrainData(data)
                           .SetHorizon(10)
                           .Build();

                var prediction = model.Predict();
                return prediction.Forecasteds[0];
            }
            else return DateTime.Now;
        }
    }
}
