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
        private void updRegValue()
        {
            _RegValue = tmc2590Converter.getDRVCTRL_SDOFF_1(CB, PHB, CA, PHA);
            RaisePropertyChanged("RegValue");
        }
        private int _CB;
        public int CB
        {
            get { return _CB; }
            set { SetProperty(ref _CB, value); updRegValue(); }
        }
        private int _PHB;
        public int PHB
        {
            get { return _PHB; }
            set { SetProperty(ref _PHB, value); updRegValue(); }
        }
        private int _CA;
        public int CA
        {
            get { return _CA; }
            set { SetProperty(ref _CA, value); updRegValue(); }
        }
        private int _PHA;
        public int PHA
        {
            get { return _PHA; }
            set { SetProperty(ref _PHA, value); updRegValue(); }
        }
        private int _RegValue;
        public int RegValue
        {
            get { return _RegValue; }
            set { SetProperty(ref _RegValue, value);
                tmc2590Converter.getDRVCTRL_SDOFF_1bits(value, ref _CB, ref _PHB, ref _CA, ref _PHA);
                RaisePropertyChanged("CB");
                RaisePropertyChanged("PHB");
                RaisePropertyChanged("CA");
                RaisePropertyChanged("PHA");
            }
        }
        public TMC2590DRVCTLSDOFFViewModel(IEventAggregator ea)
        {
            _eventAggregator = ea;
            ea.GetEvent<ConnectEvent>().Subscribe((value) => IsConnected = value);
        }
    }
}
