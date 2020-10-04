using Events;
using Prism.Commands;
using Prism.Events;
using Prism.Mvvm;

namespace TMCRegisterControl.ViewModels
{
    public class TMC2590regsViewModel : BindableBase
    {
        private IEventAggregator _eventAggregator;

        private bool _isConnected;
        public bool IsConnected
        {
            get { return _isConnected; }
            set { SetProperty(ref _isConnected, value); }
        }
        public TMC2590regsViewModel(IEventAggregator ea)
        {
            _eventAggregator = ea;
            ea.GetEvent<ConnectEvent>().Subscribe((value) => IsConnected = value);
        }
        public TMC2590regsViewModel()
        {
        }

        private DelegateCommand _SaveToFlashCMD;
        public DelegateCommand SaveToFlashCMD => _SaveToFlashCMD ??= new DelegateCommand(() =>
        _eventAggregator.GetEvent<SaveToFlashEvent>().Publish());

        private DelegateCommand _ReadAllCMD;
        public DelegateCommand ReadAllCMD => _ReadAllCMD ??= new DelegateCommand(() =>
        _eventAggregator.GetEvent<ReadAllEvent>().Publish());
    }
}
