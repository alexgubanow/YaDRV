using Events;
using Prism.Commands;
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
        private DelegateCommand _WriteCMD;
        public DelegateCommand WriteCMD => _WriteCMD ??= new DelegateCommand(() =>
        _eventAggregator.GetEvent<WriteToDeviceEvent>().Publish(new usbParcel() { report = usbReports_t.SMARTENreport, value = RegValue }));
        private void updRegValue()
        {
            _RegValue = tmc2590Converter.getSMARTEN(SEMIN, SEUP, SEMAX, SEDN, SEIMIN);
            RaisePropertyChanged("RegValue");
        }
        private int _SEMIN;
        public int SEMIN
        {
            get { return _SEMIN; }
            set { SetProperty(ref _SEMIN, value); updRegValue(); }
        }
        private int _SEUP;
        public int SEUP
        {
            get { return _SEUP; }
            set { SetProperty(ref _SEUP, value); updRegValue(); }
        }
        private int _SEMAX;
        public int SEMAX
        {
            get { return _SEMAX; }
            set { SetProperty(ref _SEMAX, value); updRegValue(); }
        }
        private int _SEDN;
        public int SEDN
        {
            get { return _SEDN; }
            set { SetProperty(ref _SEDN, value); updRegValue(); }
        }
        private int _SEIMIN;
        public int SEIMIN
        {
            get { return _SEIMIN; }
            set { SetProperty(ref _SEIMIN, value); updRegValue(); }
        }
        private int _RegValue;
        public int RegValue
        {
            get
            {
                return _RegValue;
            }
            set
            {
                SetProperty(ref _RegValue, value);
                tmc2590Converter.getSMARTENbits(value, ref _SEMIN, ref _SEUP, ref _SEMAX, ref _SEDN, ref _SEIMIN);
                RaisePropertyChanged("SEMIN");
                RaisePropertyChanged("SEUP");
                RaisePropertyChanged("SEMAX");
                RaisePropertyChanged("SEDN");
                RaisePropertyChanged("SEIMIN");
            }
        }
        public TMC2590SMARTENViewModel(IEventAggregator ea)
        {
            _eventAggregator = ea;
            ea.GetEvent<ConnectEvent>().Subscribe((value) => IsConnected = value);
            ea.GetEvent<SaveToFlashEvent>().Subscribe(() => _eventAggregator.GetEvent<WriteToDeviceEvent>().Publish(
                new usbParcel() { report = usbReports_t.SMARTENreport, value = RegValue }));
            ea.GetEvent<ReadAllEvent>().Subscribe(() => _eventAggregator.GetEvent<ReadFromDeviceEvent>().Publish(usbReports_t.SMARTENreport));
            ea.GetEvent<getSMARTENResponseEvent>().Subscribe((value) => RegValue = value);
        }
    }
}
