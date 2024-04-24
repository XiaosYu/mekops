namespace InductiveGarbageCan.Web.Services.Remote
{
    public interface IProtocol<T> where T: class
    {
        public T? ParseBytesToEntity(byte[] bytes);
        public byte[] ParseEntityToBytes(T value);

    }
}
