using Prism.Events;
using System;

namespace Events
{
    public class ConnectEvent : PubSubEvent<bool> { }
    public class RDChangedEvent : PubSubEvent<int> { }
    public class WriteToDeviceEvent : PubSubEvent<int> { }
    public class ResponseFromDeviceEvent : PubSubEvent<int> { }
}
