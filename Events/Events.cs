using Prism.Events;
using System;

namespace Events
{
    public class ConnectEvent : PubSubEvent<bool> { }
    public class RDChangedEvent : PubSubEvent<int> { }
}
