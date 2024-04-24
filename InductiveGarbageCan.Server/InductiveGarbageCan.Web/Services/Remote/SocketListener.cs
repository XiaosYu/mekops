using Microsoft.Extensions.Logging;
using System.Diagnostics;
using System.Net;
using System.Net.Sockets;

namespace InductiveGarbageCan.Web.Services.Remote
{
    public class SocketListener(IPEndPoint endPoint): IBcpdSender
    {
        private readonly IPEndPoint _endPoint = endPoint;

        public RunState RunState { get; set; }

        private Socket? _server;
        private Socket? _client;
        private IServiceProvider? _provider;

        public SocketListener Run(IServiceProvider provider)
        {
            _provider = provider;
            RunState = RunState.Runing;

            Task.Factory.StartNew(() =>
            {
                _server = new(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                _server.Bind(_endPoint);
                _server.Listen(1);

                while (RunState == RunState.Runing)
                {
                    try
                    {
                        _client = _server.Accept();

#if DEBUG
                        Debug.WriteLine("接收到连接");
#endif
                        while (RunState == RunState.Runing)
                        {
                            try
                            {
                                var buffer = new byte[1];
                                var length = _client.Receive(buffer);

                                Task.Run(() =>
                                {
                                    var scope = _provider.CreateAsyncScope();
                                    var handler = scope.ServiceProvider.GetService<IProtocol<RemoteEvent>>() 
                                                        ?? throw new Exception("未指定解析协议");

                                    var remoteEvent = handler.ParseBytesToEntity(buffer);

                                    if (remoteEvent == null) return;

                                    //反射所有的服务，进行链接
                                    var services = scope.ServiceProvider.GetServices<IRemoteService>();
                                    foreach (var service in services)
                                        service.Received(remoteEvent);
                                });

                            }
                            catch (Exception ex)
                            {
                                Debug.WriteLine(ex);
                                _client?.Close();
                                break;
                            }
                        }

                    }catch(Exception e)
                    {
                        Debug.WriteLine(e.Message);
                    }
                    
                }
                _server.Close();
                _server.Dispose();
            });
            return this;
        }

        async Task<bool> IBcpdSender.SendAsync(byte cans, byte command)
        {
            if (_client != null && _client.Connected && _provider != null)
            {
                var scope = _provider.CreateAsyncScope();
                var handler = scope.ServiceProvider.GetService<IProtocol<RemoteEvent>>() ?? throw new Exception("未指定解析协议");
                var data = handler.ParseEntityToBytes(new RemoteEvent()
                {
                    EventType = (EventType)command,
                    TriggerCans = (TriggerCans)cans
                });
                var length = await _client.SendAsync(data);
                return length == data.Length;
            }
            else return false;
        }
    }

    public enum RunState { Runing, Close }
}
