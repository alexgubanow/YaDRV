using Prism.Mvvm;

namespace UsbHIDControl.ViewModels
{
    public class UsbHIDViewModel : BindableBase
    {
        private string _status;
        public string Status
        {
            get => _status;
            set => SetProperty(ref _status, value);
        }

        private bool _isConnected;
        public bool IsConnected
        {
            get { return _isConnected; }
            set { SetProperty(ref _isConnected, value); ConnectBtnText = value ? "Disconnect" : "Connect"; }
        }

        private string _connectBtnText;
        public string ConnectBtnText
        {
            get { return _connectBtnText; }
            set { SetProperty(ref _connectBtnText, value); }
        }

        public UsbHIDViewModel()
        {
            Status = "No active connection";
            IsConnected = false;
        }
    }
}
