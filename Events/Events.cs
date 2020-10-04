using Prism.Events;
using System;

namespace Events
{
    public struct usbParcel
    {
        public usbReports_t report;
        public int value;
    }
    public class ConnectEvent : PubSubEvent<bool> { }
    public class RDChangedEvent : PubSubEvent<int> { }
    public class WriteToDeviceEvent : PubSubEvent<usbParcel> { }
    public class ReadAllEvent : PubSubEvent { }
    public class ReadFromDeviceEvent : PubSubEvent<usbReports_t> { }
    public class SaveToFlashEvent : PubSubEvent { }
    public class ResponseFromDeviceEvent : PubSubEvent<int> { }
    public class getDRVCTRLResponseEvent : PubSubEvent<int> { }
    public class getCHOPCONFResponseEvent : PubSubEvent<int> { }
    public class getSMARTENResponseEvent : PubSubEvent<int> { }
    public class getSGCSCONFResponseEvent : PubSubEvent<int> { }
    public class getDRVCONFResponseEvent : PubSubEvent<int> { }
}
