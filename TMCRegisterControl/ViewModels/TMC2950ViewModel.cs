using Prism.Mvvm;

namespace TMCRegisterControl.ViewModels
{
    public class TMC2590ViewModel : BindableBase
    {
        private string _title = "Tune YaDRV";
        public string Title
        {
            get { return _title; }
            set { SetProperty(ref _title, value); }
        }

        public TMC2590ViewModel()
        {

        }
    }
}
