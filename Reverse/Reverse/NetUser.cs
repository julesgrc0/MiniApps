using System;
using System.Collections.Generic;
using System.Net;
using System.Text;

namespace Reverse
{
    class NetUser
    {
        public IPAddress Ip { get; private set; }
        public string MacAddress { get; private set; }
        public string HostName { get; private set; }
        public byte[] Buffer { get; private set; }
        public long Duration { get; private set; }

        public NetUser(IPAddress ip, string mac, string host, byte[] buffer, long duration)
        {
            this.Ip = ip;
            this.MacAddress = mac;
            this.HostName = host;
            this.Buffer = buffer;
            this.Duration = duration;
        }
    }
}
