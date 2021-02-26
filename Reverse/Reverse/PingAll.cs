using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Threading;
using System.Text.RegularExpressions;

namespace Reverse
{
    class PingAll
    {
        private List<NetUser> users = new List<NetUser>();
        private string Suffix = string.Empty;

        public PingAll(int timeout)
        {
            string gateIp = NetworkGateway();

            string[] splitGateIp = gateIp.Split('.');

            for (int i = 2; i <= 255; i++)
            {
                string pingIP = splitGateIp[0] + "." + splitGateIp[1] + "." + splitGateIp[2] + "." + i;
                Ping(pingIP, 4, timeout);
            }
        }

        public NetUser[] GetNetUsers()
        {

            List<IPAddress> tempIP = new List<IPAddress>();
            List<NetUser> tempUsers = new List<NetUser>();
            foreach(NetUser user in this.users)
            {
                if(!tempIP.Contains(user.Ip))
                {
                    tempIP.Add(user.Ip);
                    tempUsers.Add(user);
                }
            }
            return tempUsers.ToArray();
        }

        private string NetworkGateway()
        {
            string ip = null;

            foreach (NetworkInterface f in NetworkInterface.GetAllNetworkInterfaces())
            {
                if (f.OperationalStatus == OperationalStatus.Up)
                {
                    foreach (GatewayIPAddressInformation d in f.GetIPProperties().GatewayAddresses)
                    {
                        this.Suffix = f.GetIPProperties().DnsSuffix;
                        ip = d.Address.ToString();
                    }
                }
            }

            return ip;
        }

        private void PingCompleted(object sender, PingCompletedEventArgs e)
        {
            string ip = (string)e.UserState;
            if (e.Reply != null && e.Reply.Status == IPStatus.Success)
            {
                string hostname = GetHostName(ip);
                string macaddres = GetMacAddress(ip);
                bool found = false;

                if (!found)
                {
                    this.users.Add(new NetUser(IPAddress.Parse(ip), macaddres, hostname, e.Reply.Buffer, e.Reply.RoundtripTime));
                }
            }
        }

        public string GetHostName(string ipAddress)
        {
            try
            {
                IPHostEntry entry = Dns.GetHostEntry(ipAddress);
                if (entry != null)
                {
                    return Regex.Replace(entry.HostName,@"\.("+this.Suffix+")$",string.Empty);
                }
            }
            catch (SocketException) { }
            return null;
        }

        public string GetMacAddress(string ipAddress)
        {
            string macAddress = string.Empty;
            System.Diagnostics.Process Process = new System.Diagnostics.Process();
            Process.StartInfo.FileName = "arp";
            Process.StartInfo.Arguments = "-a " + ipAddress;
            Process.StartInfo.UseShellExecute = false;
            Process.StartInfo.RedirectStandardOutput = true;
            Process.StartInfo.CreateNoWindow = true;
            Process.Start();
            string strOutput = Process.StandardOutput.ReadToEnd();
            string[] substrings = strOutput.Split('-');
            if (substrings.Length >= 8)
            {
                macAddress = substrings[3].Substring(Math.Max(0, substrings[3].Length - 2))
                         + "-" + substrings[4] + "-" + substrings[5] + "-" + substrings[6]
                         + "-" + substrings[7] + "-"
                         + substrings[8].Substring(0, 2);
                return macAddress;
            }
            return "No found";
        }

        public void Ping(string host, int attempts, int timeout)
        {
            for (int i = 0; i < attempts; i++)
            {
                new Thread(delegate ()
                {
                    try
                    {
                        Ping ping = new Ping();
                        ping.PingCompleted += new PingCompletedEventHandler(PingCompleted);
                        ping.SendAsync(host, timeout, host);
                    }
                    catch { }
                }).Start();
            }
        }
    }
}
