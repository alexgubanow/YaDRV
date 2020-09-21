using Events;
using Prism.Events;
using Prism.Mvvm;

namespace TMCRegisterControl.ViewModels
{
    public class TMC2590CHOPCONFViewModel : BindableBase
    {
        private IEventAggregator _eventAggregator;

        private bool _isConnected;
        public bool IsConnected
        {
            get { return _isConnected; }
            set { SetProperty(ref _isConnected, value); }
        }
        private int _TOFF;
        public int TOFF
        {
            get { return _TOFF; }
            set { SetProperty(ref _TOFF, value); }
        }
        private int _HSTRT;
        public int HSTRT
        {
            get { return _HSTRT; }
            set { SetProperty(ref _HSTRT, value); }
        }
        private int _HEND;
        public int HEND
        {
            get { return _HEND; }
            set { SetProperty(ref _HEND, value); }
        }
        private int _HDEC;
        public int HDEC
        {
            get { return _HDEC; }
            set { SetProperty(ref _HDEC, value); }
        }
        private int _RNDTF;
        public int RNDTF
        {
            get { return _RNDTF; }
            set { SetProperty(ref _RNDTF, value); }
        }
        private int _CHM;
        public int CHM
        {
            get { return _CHM; }
            set { SetProperty(ref _CHM, value); }
        }
        private int _TBL;
        public int TBL
        {
            get { return _TBL; }
            set { SetProperty(ref _TBL, value); }
        }
        private int _RegValue;
        public int RegValue
        {
            get { return _RegValue; }
            set { SetProperty(ref _RegValue, value); }
        }
        public TMC2590CHOPCONFViewModel(IEventAggregator ea)
        {
            _eventAggregator = ea;
            ea.GetEvent<ConnectEvent>().Subscribe((value) => IsConnected = value);
        }
    }
}
