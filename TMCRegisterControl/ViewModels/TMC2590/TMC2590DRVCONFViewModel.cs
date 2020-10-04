using Events;
using Prism.Commands;
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
        private DelegateCommand _WriteCMD;
        public DelegateCommand WriteCMD => _WriteCMD ??= new DelegateCommand(() =>
        _eventAggregator.GetEvent<WriteToDeviceEvent>().Publish(new usbParcel() { report = usbReports_t.DRVCONFreport, value = RegValue }));

        private void updRegValue()
        {
            _RegValue = tmc2590Converter.getDRVCONF(EN_S2VS, EN_PFD, SHRTSENS, OTSENS, RDSEL, VSENSE, SDOFF, TS2G, DIS_S2G, SLP, SLPL, SLPH, TST);
            RaisePropertyChanged("RegValue");
        }
        private int _EN_S2VS;
        public int EN_S2VS
        {
            get { return _EN_S2VS; }
            set { SetProperty(ref _EN_S2VS, value); updRegValue(); }
        }
        private int _EN_PFD;
        public int EN_PFD
        {
            get { return _EN_PFD; }
            set { SetProperty(ref _EN_PFD, value); updRegValue(); }
        }
        private int _SHRTSENS;
        public int SHRTSENS
        {
            get { return _SHRTSENS; }
            set { SetProperty(ref _SHRTSENS, value); updRegValue(); }
        }
        private int _OTSENS;
        public int OTSENS
        {
            get { return _OTSENS; }
            set { SetProperty(ref _OTSENS, value); updRegValue(); }
        }
        private int _RDSEL;
        public int RDSEL
        {
            get { return _RDSEL; }
            set { SetProperty(ref _RDSEL, value); updRegValue(); _eventAggregator.GetEvent<RDChangedEvent>().Publish(value); }
        }
        private int _VSENSE;
        public int VSENSE
        {
            get { return _VSENSE; }
            set { SetProperty(ref _VSENSE, value); updRegValue(); }
        }
        private int _SDOFF;
        public int SDOFF
        {
            get { return _SDOFF; }
            set { SetProperty(ref _SDOFF, value); updRegValue(); }
        }
        private int _TS2G;
        public int TS2G
        {
            get { return _TS2G; }
            set { SetProperty(ref _TS2G, value); updRegValue(); }
        }
        private int _DIS_S2G;
        public int DIS_S2G
        {
            get { return _DIS_S2G; }
            set { SetProperty(ref _DIS_S2G, value); updRegValue(); }
        }
        private int _SLP;
        public int SLP
        {
            get { return _SLP; }
            set { SetProperty(ref _SLP, value); updRegValue(); }
        }
        private int _SLPL;
        public int SLPL
        {
            get { return _SLPL; }
            set { SetProperty(ref _SLPL, value); updRegValue(); }
        }
        private int _SLPH;
        public int SLPH
        {
            get { return _SLPH; }
            set { SetProperty(ref _SLPH, value); updRegValue(); }
        }
        private int _TST;
        public int TST
        {
            get { return _TST; }
            set { SetProperty(ref _TST, value); updRegValue(); }
        }
        private int _RegValue;
        public int RegValue
        {
            get { return _RegValue; }
            set { SetProperty(ref _RegValue, value);
                tmc2590Converter.getDRVCONFbits(value, ref _EN_S2VS, ref _EN_PFD, ref _SHRTSENS, ref _OTSENS, ref _RDSEL, ref _VSENSE, ref _SDOFF, ref _TS2G, ref _DIS_S2G, ref _SLP, ref _SLPL, ref _SLPH, ref _TST);
                RaisePropertyChanged("EN_S2VS");
                RaisePropertyChanged("EN_PFD");
                RaisePropertyChanged("SHRTSENS");
                RaisePropertyChanged("OTSENS");
                RaisePropertyChanged("RDSEL");
                RaisePropertyChanged("VSENSE");
                RaisePropertyChanged("SDOFF");
                RaisePropertyChanged("TS2G");
                RaisePropertyChanged("DIS_S2G");
                RaisePropertyChanged("SLP");
                RaisePropertyChanged("SLPL");
                RaisePropertyChanged("SLPH");
                RaisePropertyChanged("TST");
            }
        }
        public TMC2590DRVCONFViewModel(IEventAggregator ea)
        {
            _eventAggregator = ea;
            ea.GetEvent<ConnectEvent>().Subscribe((value) => IsConnected = value);
            ea.GetEvent<SaveToFlashEvent>().Subscribe(() => _eventAggregator.GetEvent<WriteToDeviceEvent>().Publish(
                new usbParcel() { report = usbReports_t.DRVCONFreport, value = RegValue }));
            ea.GetEvent<ReadAllEvent>().Subscribe(() => _eventAggregator.GetEvent<ReadFromDeviceEvent>().Publish(usbReports_t.DRVCONFreport));
            ea.GetEvent<getDRVCONFResponseEvent>().Subscribe((value) => RegValue = value);
        }
    }
}
