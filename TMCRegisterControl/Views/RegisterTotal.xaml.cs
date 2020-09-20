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

       public int Value { get { return (int)GetValue(ValueProperty); } set { SetValue(ValueProperty, value); } }

        public static readonly DependencyProperty ValueProperty = DependencyProperty.Register("Value", typeof(int),
            typeof(RegisterTotal), new UIPropertyMetadata(0));
    }
}
