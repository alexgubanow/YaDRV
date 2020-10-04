using Events;
using Prism.Commands;
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
        private DelegateCommand _WriteCMD;
        public DelegateCommand WriteCMD => _WriteCMD ??= new DelegateCommand(() =>
        _eventAggregator.GetEvent<WriteToDeviceEvent>().Publish(new usbParcel() { report = usbReports_t.CHOPCONFreport, value = RegValue }));

        private void updRegValue()
        {
            _RegValue = tmc2590Converter.getCHOPCONF(TOFF, HSTRT, HEND, HDEC, RNDTF, CHM, TBL);
            RaisePropertyChanged("RegValue");
        }
        private int _TOFF;
        public int TOFF
        {
            get { return _TOFF; }
            set { SetProperty(ref _TOFF, value); updRegValue(); }
        }
        private int _HSTRT;
        public int HSTRT
        {
            get { return _HSTRT; }
            set { SetProperty(ref _HSTRT, value); updRegValue(); }
        }
        private int _HEND;
        public int HEND
        {
            get { return _HEND; }
            set { SetProperty(ref _HEND, value); updRegValue(); }
        }
        private int _HDEC;
        public int HDEC
        {
            get { return _HDEC; }
            set { SetProperty(ref _HDEC, value); updRegValue(); }
        }
        private int _RNDTF;
        public int RNDTF
        {
            get { return _RNDTF; }
            set { SetProperty(ref _RNDTF, value); updRegValue(); }
        }
        private int _CHM;
        public int CHM
        {
            get { return _CHM; }
            set { SetProperty(ref _CHM, value); updRegValue(); }
        }
        private int _TBL;
        public int TBL
        {
            get { return _TBL; }
            set { SetProperty(ref _TBL, value); updRegValue(); }
        }
        private int _RegValue;
        public int RegValue
        {
            get { return _RegValue; }
            set
            {
                SetProperty(ref _RegValue, value);
                tmc2590Converter.getCHOPCONFbits(value, ref _TOFF, ref _HSTRT, ref _HEND, ref _HDEC, ref _RNDTF, ref _CHM, ref _TBL);
                RaisePropertyChanged("TOFF");
                RaisePropertyChanged("HSTRT");
                RaisePropertyChanged("HEND");
                RaisePropertyChanged("HDEC");
                RaisePropertyChanged("RNDTF");
                RaisePropertyChanged("CHM");
                RaisePropertyChanged("TBL");
            }
        }
        public TMC2590CHOPCONFViewModel(IEventAggregator ea)
        {
            _eventAggregator = ea;
            ea.GetEvent<ConnectEvent>().Subscribe((value) => IsConnected = value);
            ea.GetEvent<SaveToFlashEvent>().Subscribe(() => _eventAggregator.GetEvent<WriteToDeviceEvent>().Publish(
                new usbParcel() { report = usbReports_t.CHOPCONFreport, value = RegValue }));
            ea.GetEvent<ReadAllEvent>().Subscribe(() => _eventAggregator.GetEvent<ReadFromDeviceEvent>().Publish(usbReports_t.CHOPCONFreport));
            ea.GetEvent<getCHOPCONFResponseEvent>().Subscribe((value) => RegValue = value);
        }
    }
}
