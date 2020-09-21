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
        private readonly IEventAggregator _eventAggregator;
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

        private hidDeviceInfo _Sdev;
        public hidDeviceInfo Sdev
        {
            get { return _Sdev; }
            set { SetProperty(ref _Sdev, value); }
        }
        private int devIdx;
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
        public DelegateCommand ConnectCMD => _connectCMD ??= new DelegateCommand(ExecuteConnectCMD);

        void ExecuteConnectCMD()
        {
            if (Sdev != null)
            {
                Status = "";
            }
            else
            {
                Status = "Select device from list for first";
                return;
            }
            try
            {
                if (IsConnected && devIdx > -1)
                {
                    Hidapiw.Close(devIdx);
                    devIdx = -1;
                    IsConnected = false;
                }
                else if (IsConnected)
                {
                    IsConnected = false;
                }
                else if (!IsConnected)
                {
                    devIdx = -1;
                    Hidapiw.Open(ref devIdx, Sdev.VendorId, Sdev.ProductId, Sdev.SerialNumber);
                    if (devIdx != -1)
                    {
                        IsConnected = true;
                        Hidapiw.SetBlockingMode(devIdx, false);
                    }
                }
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
                    for (int i = devs.Count - 1; i > -1; i--)
                    {
                        if (devs[i].Product == "")
                        {
                            devs.RemoveAt(i);
                        }
                    }
                    DevList = new ObservableCollection<hidDeviceInfo>(devs);
                }
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
            if (devIdx > -1)
            {
                Hidapiw.Close(devIdx);
            }
            Hidapiw.Dispose();
        }
    }
}
