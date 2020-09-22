using Prism.Events;
using System;

namespace Events
{
    public class ConnectEvent : PubSubEvent<bool> { }
    public class RDChangedEvent : PubSubEvent<int> { }
    public struct TmcRegData
    {
        public int addr;
        public int val;
    }
    public class WriteToDeviceEvent : PubSubEvent<TmcRegData> { }
    public class ResponseFromDeviceEvent : PubSubEvent<int> { }
}
