using System.Windows;
using System.Windows.Controls;

namespace TMCRegisterControl.Views
{
    /// <summary>
    /// Interaction logic for RegisterTotal.xaml
    /// </summary>
    public partial class RegisterTotal : UserControl
    {
        public RegisterTotal() : base()
        {
            InitializeComponent();
        }

       public int RegTotValue { get { return (int)GetValue(RegTotValueProperty); } set { SetValue(RegTotValueProperty, value); } }

        public static readonly DependencyProperty RegTotValueProperty = DependencyProperty.Register("RegTotValue", typeof(int),
            typeof(RegisterTotal), new UIPropertyMetadata(0));
        public int RegTotMin
        {
            get { return (int)GetValue(RegTotMinProperty); }
            set { SetValue(RegTotMinProperty, value); }
        }

        public static readonly DependencyProperty RegTotMinProperty = DependencyProperty.Register("RegTotMin", typeof(int),
            typeof(RegisterTotal), new UIPropertyMetadata(0));
        public int RegParMax { get { return (int)GetValue(RegTotMaxProperty); } set { SetValue(RegTotMaxProperty, value); } }

        public static readonly DependencyProperty RegTotMaxProperty = DependencyProperty.Register("RegTotMax", typeof(int),
            typeof(RegisterTotal), new UIPropertyMetadata(0xFFFFF));
    }
}
