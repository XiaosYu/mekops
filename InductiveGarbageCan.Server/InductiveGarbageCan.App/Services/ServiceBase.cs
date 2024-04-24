using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http.Json;
using System.Text;
using System.Threading.Tasks;

namespace InductiveGarbageCan.App.Services
{
    public class ServiceBase(IHttpClientFactory factory)
    {
        private readonly IHttpClientFactory _factory = factory;

        private bool _enable = true;

        public static string BaseUri { set; get; } = "http://10.135.118.0:5034";

        protected async Task<TResult?> PostAsync<TResult>(string region, string function, object body)
        {
            if (!_enable) return default;
            var context = _factory.CreateClient();
            var builder = new StringBuilder();
            builder.Append(BaseUri);
            builder.Append($"/api/{region}/{function}");
            
            try
            {
                var response = await context.PostAsync(builder.ToString(), JsonContent.Create(body));
                return response.IsSuccessStatusCode ? await response.Content.ReadFromJsonAsync<TResult>() : default;
            }
            catch
            {
                return default;
            }
        }

        protected async Task<TResult?> GetAsync<TResult>(string region, string function, Dictionary<string, object>? args = null)
        {
            if (!_enable) return default;
            var context = _factory.CreateClient();
            var builder = new StringBuilder();
            builder.Append(BaseUri);
            builder.Append($"/api/{region}/{function}");
            if (args != null)
            {
                builder.Append('/');
                builder.Append(string.Join('&', args.Select(kv => $"{kv.Key}={kv.Value}")));
            }

            try
            {
                var response = await context.GetAsync(builder.ToString());
                return response.IsSuccessStatusCode ? await response.Content.ReadFromJsonAsync<TResult>() : default;
            }
            catch
            {
                return default;
            }
        }
        protected async Task<TResult?> GetAsync<TResult>(string region, string function, string[]? names, object[]? values)
        {
            var context = new HttpClient();
            var builder = new StringBuilder();
            builder.Append(BaseUri);
            builder.Append($"/api/{region}/{function}");
            if (names != null && values != null)
            {
                builder.Append('/');
                builder.Append(string.Join('&', names.Zip(values).Select((k, v) => $"{k}={v}")));
            }
            var response = await context.GetAsync(builder.ToString());
            return response.IsSuccessStatusCode ? await response.Content.ReadFromJsonAsync<TResult>() : default;
        }
    }
}
