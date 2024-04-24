using BootstrapBlazor.Components;
using System.Diagnostics;
using Color = BootstrapBlazor.Components.Color;

namespace InductiveGarbageCan.App.Services
{
    public class NotificationService
    {
        public NotificationService(MessageService message, ToastService toast, DialogService dialog)
        {
            Message = message;
            Toast = toast;
            Dialog = dialog;

            
        }

        private MessageService Message { get; }
        private ToastService Toast { get; }
        private DialogService Dialog { get; }

        public Task ToastSuccess(string title, string content)
            => Toast.Success(title, content);

        public Task ToastError(string title, string content)
            => Toast.Error(title, content);

        public Task MessageSuccess(string content)
            => Message.Show(new MessageOption()
            {
                Color = Color.Success,
                Content = content,
            });

        public Task MessageError(string content)
            => Message.Show(new MessageOption()
            {
                Color = Color.Danger,
                Content = content,
            });

        public Task DialogShow(DialogOption option)
            => Dialog.Show(option);
    }
}
