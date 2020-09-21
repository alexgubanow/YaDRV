using Events;
using Prism.Events;
using Prism.Mvvm;

namespace TMCRegisterControl.ViewModels
{
    public class TMC2590SMARTENViewModel : BindableBase
    {
        private IEventAggregator _eventAggregator;

        private bool _isConnected;
        public bool IsConnected
        {
            get { return _isConnected; }
            set { SetProperty(ref _isConnected, value); }
        }
        private int _SEMIN;
        public int SEMIN
        {
            get { return _SEMIN; }
            set { SetProperty(ref _SEMIN, value); }
        }
        private int _SEUP;
        public int SEUP
        {
            get { return _SEUP; }
            set { SetProperty(ref _SEUP, value); }
        }
        private int _SEMAX;
        public int SEMAX
        {
            get { return _SEMAX; }
            set { SetProperty(ref _SEMAX, value); }
        }
        private int _SEDN;
        public int SEDN
        {
            get { return _SEDN; }
            set { SetProperty(ref _SEDN, value); }
        }
        private int _SEIMIN;
        public int SEIMIN
        {
            get { return _SEIMIN; }
            set { SetProperty(ref _SEIMIN, value); }
        }
        public TMC2590SMARTENViewModel(IEventAggregator ea)
        {
            _eventAggregator = ea;
            ea.GetEvent<ConnectEvent>().Subscribe((value) => IsConnected = value);
        }
    }
}
