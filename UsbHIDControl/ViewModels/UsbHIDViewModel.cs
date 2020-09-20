using Events;
using Prism.Commands;
using Prism.Events;
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Runtime.InteropServices;

namespace UsbHIDControl.ViewModels
{
    public class UsbHIDViewModel : BindableBase, IDisposable
    {
        private IEventAggregator _eventAggregator;
        private hidapiw _hidapiw_native;
        public hidapiw Hidapiw
        {
            get { return _hidapiw_native; }
            set { SetProperty(ref _hidapiw_native, value); }
        }

        private ObservableCollection<hidDeviceInfo> _devList;
        public ObservableCollection<hidDeviceInfo> DevList
        {
            get { return _devList; }
            set { SetProperty(ref _devList, value); }
        }

        private string _status;
        public string Status
        {
            get => _status;
            set => SetProperty(ref _status, value);
        }

        private bool _isConnected;
        public bool IsConnected
        {
            get { return _isConnected; }
            set
            {
                SetProperty(ref _isConnected, value);
                ConnectBtnText = value ? "Disconnect" : "Connect";
                _eventAggregator.GetEvent<ConnectEvent>().Publish(value);
            }
        }

        private string _connectBtnText;
        public string ConnectBtnText
        {
            get { return _connectBtnText; }
            set { SetProperty(ref _connectBtnText, value); }
        }

        private DelegateCommand _connectCMD;
        public DelegateCommand ConnectCMD => _connectCMD ??= new DelegateCommand(ExecuteConnectCMD, CanExecuteConnectCMD);

        void ExecuteConnectCMD()
        {
            IsConnected = !IsConnected;
        }

        bool CanExecuteConnectCMD()
        {
            //need to implement here check for device been choosen from list
            return true;
        }

        private DelegateCommand _refreshDevListCMD;
        public DelegateCommand RefreshDevListCMD => _refreshDevListCMD ??= new DelegateCommand(ExecuteRefreshDevListCMD);

        void ExecuteRefreshDevListCMD()
        {
            try
            {
                if (Hidapiw != null)
                {
                    List<hidDeviceInfo> devs = new List<hidDeviceInfo>();
                    Hidapiw.Enumerate(ref devs, 0, 0);
                    DevList = new ObservableCollection<hidDeviceInfo>(devs);
                }
                //foreach (var device in DevList)
                //{
                //    if (device.vendor_id == 1155 && device.product_id == 22352)
                //    {
                //        Console.WriteLine("VID 0x{0:X} PID 0x{1:X} Manufacturer \"{2}\" Product \"{3}\"",
                //            device.vendor_id, device.product_id, device.manufacturer_string, device.product_string);
                //    }
                //}
            }
            catch (SEHException e)
            {
                if (e.StackTrace is string s)
                {
                    Status = s;
                }
            }
            catch (Exception ex)
            {
                Status = ex.Message;
            }
        }

        public UsbHIDViewModel(IEventAggregator ea)
        {
            _eventAggregator = ea;
            Status = "No active connection";
            IsConnected = false;
            Hidapiw = new hidapiw();
            DevList = new ObservableCollection<hidDeviceInfo>();
        }

        public void Dispose()
        {
            Hidapiw.Dispose();
        }
    }
}
