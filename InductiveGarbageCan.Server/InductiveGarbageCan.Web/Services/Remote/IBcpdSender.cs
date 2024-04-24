namespace InductiveGarbageCan.Web.Services.Remote
{
    public interface IBcpdSender
    {
        public Task<bool> SendAsync(byte cans, byte command);
    }
}
