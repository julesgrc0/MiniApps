using System;
using System.IO;
using System.Threading;

namespace Reverse
{


    class Program
    {
        static void Main(string[] args)
        {
            DateTime start = DateTime.Now;
            new Thread(() =>
            {
                PingAll users = new PingAll(2000);
                foreach (NetUser user in users.GetNetUsers())
                {
                    Console.WriteLine($"IP: {user.Ip}\nName: {user.HostName}");
                }
                DateTime end = DateTime.Now;
                Console.WriteLine((end - start).TotalSeconds+"s");
            }).Start();
        }
    }   
}
