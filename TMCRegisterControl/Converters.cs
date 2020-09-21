using System;
using System.Globalization;
using System.Windows.Data;

namespace TMCRegisterControl
{
    public class HexToDecConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return string.Format(culture, "0x{0:X}", value);
        }

        private readonly char[] _trim_hex = new char[] { '0', 'x' };
        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            int.TryParse(((string)value).TrimStart(_trim_hex), NumberStyles.HexNumber, culture, out int result);
            return result;
        }
    }
    //public class BinToDecConverter : IValueConverter
    //{
    //    public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
    //    {
    //        return string.Format(culture, "0b{0:B}", value);
    //    }

    //    private readonly char[] _trim_hex = new char[] { '0', 'x' };
    //    public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
    //    {
    //        int.TryParse(((string)value).TrimStart(_trim_hex), NumberStyles.HexNumber, culture, out int result);
    //        return result;
    //    }
    //}
}
