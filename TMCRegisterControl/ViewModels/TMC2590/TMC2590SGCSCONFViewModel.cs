using Events;
using Prism.Events;
using Prism.Mvvm;
using System;
using System.Globalization;
using System.Reflection;

namespace TMCRegisterControl.ViewModels
{
    public class TMC2590SGCSCONFViewModel : BindableBase
    {
        private IEventAggregator _eventAggregator;

        private bool _isConnected;
        public bool IsConnected
        {
            get { return _isConnected; }
            set
            {
                SetProperty(ref _isConnected, value);
            }
        }

        private void updRegValue()
        {
            _RegValue = tmc2590Converter.getSGCSCONF(CS, SGT, SFILT);
            RaisePropertyChanged("RegValue");
        }

        private int _CS;
        public int CS { get { return _CS; } set { SetProperty(ref _CS, value); updRegValue(); } }
        private int _SGT;
        public int SGT
        {
            get { return _SGT; }
            set
            {
                SetProperty(ref _SGT, value);
                updRegValue();
            }
        }
        private int _SFILT;
        public int SFILT
        {
            get { return _SFILT; }
            set
            {
                SetProperty(ref _SFILT, value);
                updRegValue();
            }
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
                tmc2590Converter.getSGCSCONFbits(value, ref _CS, ref _SGT, ref _SFILT);
                RaisePropertyChanged("CS");
                RaisePropertyChanged("SGT");
                RaisePropertyChanged("SFILT");
            }
        }
        public TMC2590SGCSCONFViewModel(IEventAggregator ea)
        {
            RegValue = 0xD0006;
            _eventAggregator = ea;
            ea.GetEvent<ConnectEvent>().Subscribe((value) => IsConnected = value);
        }
    }
}
