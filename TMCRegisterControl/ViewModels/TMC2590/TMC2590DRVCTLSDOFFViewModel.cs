using Events;
using Prism.Events;
using Prism.Mvvm;

namespace TMCRegisterControl.ViewModels
{
    public class TMC2590DRVCTLSDOFFViewModel : BindableBase
    {
        private IEventAggregator _eventAggregator;

        private bool _isConnected;
        public bool IsConnected
        {
            get { return _isConnected; }
            set { SetProperty(ref _isConnected, value); }
        }
        private int _CB;
        public int CB
        {
            get { return _CB; }
            set { SetProperty(ref _CB, value); }
        }
        private int _PHB;
        public int PHB
        {
            get { return _PHB; }
            set { SetProperty(ref _PHB, value); }
        }
        private int _CA;
        public int CA
        {
            get { return _CA; }
            set { SetProperty(ref _CA, value); }
        }
        private int _PHA;
        public int PHA
        {
            get { return _PHA; }
            set { SetProperty(ref _PHA, value); }
        }
        private int _RegValue;
        public int RegValue
        {
            get { return _RegValue; }
            set { SetProperty(ref _RegValue, value); }
        }
        public TMC2590DRVCTLSDOFFViewModel(IEventAggregator ea)
        {
            _eventAggregator = ea;
            ea.GetEvent<ConnectEvent>().Subscribe((value) => IsConnected = value);
        }
    }
}
