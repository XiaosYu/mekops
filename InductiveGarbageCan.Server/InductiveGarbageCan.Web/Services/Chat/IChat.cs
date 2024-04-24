namespace InductiveGarbageCan.Web.Services.Chat
{
    public interface IChat
    {
        public Task<ChatMessage?> GetReplyAsync(List<ChatMessage> messages);
    }
}
