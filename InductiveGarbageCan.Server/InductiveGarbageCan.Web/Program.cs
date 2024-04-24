using InductiveGarbageCan.Database;
using InductiveGarbageCan.Database.Log;
using InductiveGarbageCan.Database.Log.Models;
using InductiveGarbageCan.Web.Services;
using InductiveGarbageCan.Web.Services.Chat;
using InductiveGarbageCan.Web.Services.Hubs;
using InductiveGarbageCan.Web.Services.ML;
using InductiveGarbageCan.Web.Services.Remote;
using InductiveGarbageCan.Web.Services.Repository;
using Microsoft.AspNetCore.ResponseCompression;
using Microsoft.Extensions.Options;
using System.Net;

var builder = WebApplication.CreateBuilder(args);

var listener = new SocketListener(new IPEndPoint(IPAddress.Any, 520));

builder.Services.AddSingleton<IBcpdSender>(listener);
builder.Services.AddScoped<IRemoteService, RemoteDataService>();
builder.Services.AddScoped<IRemoteService, RemoteNotificationService>();
builder.Services.AddScoped<IProtocol<RemoteEvent>, BcpdProtocol>();
builder.Services.AddScoped<IAdder, Adder>();
builder.Services.AddScoped<IQueryer, Queryer>();
builder.Services.AddScoped<IRepository<TbLog>, DbLogRepository<TbLog>>();

builder.Services.AddScoped<IDateTimeForecaster, DotNetMLDateTimeForecaster>();

builder.Services.AddScoped<IChat, OpenAIChatGPT>();

builder.Services.AddDbContextWithSqlite<DbLogContext>("DataSource=dblog.db");
builder.Services.AddControllers();
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();
builder.Services.AddSignalR();

builder.Services.AddResponseCompression(opts =>
{
    opts.MimeTypes = ResponseCompressionDefaults.MimeTypes.Concat(
          new[] { "application/octet-stream" });
});

var app = builder.Build();

listener.Run(app.Services);


if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

//app.UseHttpsRedirection();

app.UseAuthorization();

app.MapControllers();

app.MapHub<MainHub>("/main");

app.Run();
