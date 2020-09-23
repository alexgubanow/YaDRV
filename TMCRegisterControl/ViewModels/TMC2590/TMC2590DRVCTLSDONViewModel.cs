using Events;
using Prism.Commands;
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
        private DelegateCommand _WriteCMD;
        public DelegateCommand WriteCMD => _WriteCMD ??= new DelegateCommand(ExecuteWriteCMD);

        void ExecuteWriteCMD()
        {
            _eventAggregator.GetEvent<WriteToDeviceEvent>().Publish(RegValue);
        }
        private void updRegValue()
        {
            _RegValue = tmc2590Converter.getDRVCTRL_SDOFF_0(MRES, DEDGE, INTPOL);
            RaisePropertyChanged("RegValue");
        }
        private int _MRES;
        public int MRES
        {
            get { return _MRES; }
            set { SetProperty(ref _MRES, value); updRegValue(); }
        }
        private int _DEDGE;
        public int DEDGE
        {
            get { return _DEDGE; }
            set { SetProperty(ref _DEDGE, value); updRegValue(); }
        }
        private int _INTPOL;
        public int INTPOL
        {
            get { return _INTPOL; }
            set { SetProperty(ref _INTPOL, value); updRegValue(); }
        }
        private int _RegValue;
        public int RegValue
        {
            get { return _RegValue; }
            set { SetProperty(ref _RegValue, value);
                tmc2590Converter.getDRVCTRL_SDOFF_0bits(value, ref _MRES, ref _DEDGE, ref _INTPOL);
                RaisePropertyChanged("MRES");
                RaisePropertyChanged("DEDGE");
                RaisePropertyChanged("INTPOL");
            }
        }
        public TMC2590DRVCTLSDONViewModel(IEventAggregator ea)
        {
            RegValue = 0x183;
            _eventAggregator = ea;
            ea.GetEvent<ConnectEvent>().Subscribe((value) => IsConnected = value);
        }
    }
}
