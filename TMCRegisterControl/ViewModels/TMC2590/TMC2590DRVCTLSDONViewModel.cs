using Events;
using Prism.Events;
using Prism.Mvvm;

namespace TMCRegisterControl.ViewModels
{
    public class TMC2590DRVCTLSDONViewModel : BindableBase
    {
        private IEventAggregator _eventAggregator;

        private bool _isConnected;
        public bool IsConnected
        {
            get { return _isConnected; }
            set { SetProperty(ref _isConnected, value); }
        }
        private int _MRES;
        public int MRES
        {
            get { return _MRES; }
            set { SetProperty(ref _MRES, value); }
        }
        private int _DEDGE;
        public int DEDGE
        {
            get { return _DEDGE; }
            set { SetProperty(ref _DEDGE, value); }
        }
        private int _INTPOL;
        public int INTPOL
        {
            get { return _INTPOL; }
            set { SetProperty(ref _INTPOL, value); }
        }
        private int _RegValue;
        public int RegValue
        {
            get { return _RegValue; }
            set { SetProperty(ref _RegValue, value); }
        }
        public TMC2590DRVCTLSDONViewModel(IEventAggregator ea)
        {
            _eventAggregator = ea;
            ea.GetEvent<ConnectEvent>().Subscribe((value) => IsConnected = value);
        }
    }
}
