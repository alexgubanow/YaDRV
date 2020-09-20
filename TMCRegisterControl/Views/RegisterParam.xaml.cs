using System.Windows;
using System.Windows.Controls;

namespace TMCRegisterControl.Views
{
    /// <summary>
    /// Interaction logic for RegisterParam.xaml
    /// </summary>
    public partial class RegisterParam : UserControl
    {
        public RegisterParam()
        {
            InitializeComponent();
        }

        public string RegParName { get { return (string)GetValue(RegParNameProperty); } set { SetValue(RegParNameProperty, value); } }

        public static readonly DependencyProperty RegParNameProperty = DependencyProperty.Register("RegParName", typeof(string),
            typeof(RegisterParam), new UIPropertyMetadata(""));
        public string RegParExplained { get { return (string)GetValue(RegParExplainedProperty); } set { SetValue(RegParExplainedProperty, value); } }

        public static readonly DependencyProperty RegParExplainedProperty = DependencyProperty.Register("RegParExplained", typeof(string),
            typeof(RegisterParam), new UIPropertyMetadata(""));
        public int? RegParValue { get => (int)GetValue(RegParValueProperty); set { SetValue(RegParValueProperty, value); } }

        public static readonly DependencyProperty RegParValueProperty = DependencyProperty.Register("RegParValue", typeof(int),
            typeof(RegisterParam), new UIPropertyMetadata(0));
        public int RegParMin { 
            get { return (int)GetValue(RegParMinProperty); } 
            set { SetValue(RegParMinProperty, value); } }

        public static readonly DependencyProperty RegParMinProperty = DependencyProperty.Register("RegParMin", typeof(int),
            typeof(RegisterTotal), new UIPropertyMetadata(0));
        public int RegParMax { get { return (int)GetValue(RegParMaxProperty); } set { SetValue(RegParMaxProperty, value); } }

        public static readonly DependencyProperty RegParMaxProperty = DependencyProperty.Register("RegParMax", typeof(int),
            typeof(RegisterTotal), new UIPropertyMetadata(0));
    }
}
