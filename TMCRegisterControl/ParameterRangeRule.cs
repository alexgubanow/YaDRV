using System;
using System.Globalization;
using System.Windows.Controls;

namespace TMCRegisterControl
{
    public class ParameterRangeRule : ValidationRule
    {
        public Int32RangeChecker ValidRange { get; 
            set; }

        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            int ParamValue = 0;

            try
            {
                if (((string)value).Length > 0)
                    ParamValue = int.Parse((string)value);
            }
            catch (Exception e)
            {
                return new ValidationResult(false, $"Illegal characters or {e.Message}");
            }
            if ((ParamValue < ValidRange.Minimum) || (ParamValue > ValidRange.Maximum))
            {
                return new ValidationResult(false,
                  $"Please enter an value in the range: {ValidRange.Minimum}-{ValidRange.Maximum}.");
            }
            return ValidationResult.ValidResult;
        }
    }
}
