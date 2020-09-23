using Events;
using Prism.Events;
using Prism.Mvvm;
using System;
using System.Globalization;
using System.Reflection;
using System.Windows;

namespace TMCRegisterControl.ViewModels
{
    public class TMC2590readResponseViewModel : BindableBase
    {
        private readonly IEventAggregator _eventAggregator;
        private Visibility _RD0;
        public Visibility RD0
        {
            get { return _RD0; }
            set { SetProperty(ref _RD0, value); }
        }
        private Visibility _RD1;
        public Visibility RD1
        {
            get { return _RD1; }
            set { SetProperty(ref _RD1, value); }
        }
        private Visibility _RD2;
        public Visibility RD2
        {
            get { return _RD2; }
            set { SetProperty(ref _RD2, value); }
        }
        private Visibility _RD3;
        public Visibility RD3
        {
            get { return _RD3; }
            set { SetProperty(ref _RD3, value); }
        }
        void RDvalueParser(int val)
        {
            switch (val)
            {
                case 0:
                    RD0 = Visibility.Visible;
                    RD1 = Visibility.Collapsed;
                    RD2 = Visibility.Collapsed;
                    RD3 = Visibility.Collapsed;
                    break;
                case 1:
                    RD0 = Visibility.Collapsed;
                    RD1 = Visibility.Visible;
                    RD2 = Visibility.Collapsed;
                    RD3 = Visibility.Collapsed;
                    break;
                case 2:
                    RD0 = Visibility.Collapsed;
                    RD1 = Visibility.Collapsed;
                    RD2 = Visibility.Visible;
                    RD3 = Visibility.Collapsed;
                    break;
                case 3:
                    RD0 = Visibility.Collapsed;
                    RD1 = Visibility.Collapsed;
                    RD2 = Visibility.Collapsed;
                    RD3 = Visibility.Visible;
                    break;
            }
        }
        private int _MSTEP09;
        public int MSTEP09
        {
            get { return _MSTEP09; }
            set { SetProperty(ref _MSTEP09, value); }
        }
        private int _SG09;
        public int SG09
        {
            get { return _SG09; }
            set { SetProperty(ref _SG09, value); }
        }
        private int responseValue;
        public int ResponseValue
        {
            get { return responseValue; }
            set { SetProperty(ref responseValue, value); }
        }
        public TMC2590readResponseViewModel(IEventAggregator ea)
        {
            RD0 = Visibility.Collapsed;
            RD1 = Visibility.Visible;
            RD2 = Visibility.Collapsed;
            RD3 = Visibility.Collapsed;
            _eventAggregator = ea;
            ea.GetEvent<RDChangedEvent>().Subscribe((value) => RDvalueParser(value));
            ea.GetEvent<ResponseFromDeviceEvent>().Subscribe((value) => ResponseValue = value);
        }
        public TMC2590readResponseViewModel()
        {
            RD0 = Visibility.Collapsed;
            RD1 = Visibility.Visible;
            RD2 = Visibility.Collapsed;
            RD3 = Visibility.Collapsed;
        }
    }
}
