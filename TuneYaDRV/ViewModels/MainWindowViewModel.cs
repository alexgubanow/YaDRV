using Prism.Mvvm;

namespace TuneYaDRV.ViewModels
{
    public class MainWindowViewModel : BindableBase
    {
        private string _title = "Tune YaDRV";
        public string Title
        {
            get { return _title; }
            set { SetProperty(ref _title, value); }
        }

        public MainWindowViewModel()
        {

        }
    }
}
