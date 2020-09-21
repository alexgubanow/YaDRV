using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using Prism.Ioc;
using Prism.Events;
using Prism.Regions;

namespace UsbHIDControl.Views
{
    /// <summary>
    /// Interaction logic for UsbHID.xaml
    /// </summary>
    public partial class UsbHID : UserControl
    {
        public UsbHID()
        {
            try
            {
                InitializeComponent();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Exception message:\n" + ex.Message + "\n" + "Inner Exception message:\n" + ex.InnerException.Message, "Error while loading");
                Application.Current.Shutdown();
            }
        }
    }
}
