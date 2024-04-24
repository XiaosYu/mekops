namespace InductiveGarbageCan.Web.Services.Remote
{
    public interface IRemoteService
    {
        public void Received(RemoteEvent @event);
    }
}
