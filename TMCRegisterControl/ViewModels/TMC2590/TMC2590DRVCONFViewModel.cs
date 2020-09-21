using Events;
using Prism.Events;
using Prism.Mvvm;

namespace TMCRegisterControl.ViewModels
{
    public class TMC2590DRVCONFViewModel : BindableBase
    {
        private IEventAggregator _eventAggregator;

        private bool _isConnected;
        public bool IsConnected
        {
            get { return _isConnected; }
            set { SetProperty(ref _isConnected, value); }
        }
        private int _EN_S2VS;
        public int EN_S2VS
        {
            get { return _EN_S2VS; }
            set { SetProperty(ref _EN_S2VS, value); }
        }
        private int _EN_PFD;
        public int EN_PFD
        {
            get { return _EN_PFD; }
            set { SetProperty(ref _EN_PFD, value); }
        }
        private int _SHRTSENS;
        public int SHRTSENS
        {
            get { return _SHRTSENS; }
            set { SetProperty(ref _SHRTSENS, value); }
        }
        private int _OTSENS;
        public int OTSENS
        {
            get { return _OTSENS; }
            set { SetProperty(ref _OTSENS, value); }
        }
        private int _RDSEL;
        public int RDSEL
        {
            get { return _RDSEL; }
            set { SetProperty(ref _RDSEL, value); }
        }
        private int _VSENSE;
        public int VSENSE
        {
            get { return _VSENSE; }
            set { SetProperty(ref _VSENSE, value); }
        }
        private int _SDOFF;
        public int SDOFF
        {
            get { return _SDOFF; }
            set { SetProperty(ref _SDOFF, value); }
        }
        private int _TS2G;
        public int TS2G
        {
            get { return _TS2G; }
            set { SetProperty(ref _TS2G, value); }
        }
        private int _DIS_S2G;
        public int DIS_S2G
        {
            get { return _DIS_S2G; }
            set { SetProperty(ref _DIS_S2G, value); }
        }
        private int _SLP;
        public int SLP
        {
            get { return _SLP; }
            set { SetProperty(ref _SLP, value); }
        }
        private int _SLPL;
        public int SLPL
        {
            get { return _SLPL; }
            set { SetProperty(ref _SLPL, value); }
        }
        private int _SLPH;
        public int SLPH
        {
            get { return _SLPH; }
            set { SetProperty(ref _SLPH, value); }
        }
        private int _TST;
        public int TST
        {
            get { return _TST; }
            set { SetProperty(ref _TST, value); }
        }
        private int _RegValue;
        public int RegValue
        {
            get { return _RegValue; }
            set { SetProperty(ref _RegValue, value); }
        }
        public TMC2590DRVCONFViewModel(IEventAggregator ea)
        {
            _eventAggregator = ea;
            ea.GetEvent<ConnectEvent>().Subscribe((value) => IsConnected = value);
        }
    }
}
