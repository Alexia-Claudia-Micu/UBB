using Lab4.Parser;
using System;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Lab4;
class Program
{
    static void Main()
    {
        var hosts = new List<string> {
                "www.cs.ubbcluj.ro/~vancea/",
                "www.cs.ubbcluj.ro/~forest/newton/index.html",
                "www.cs.ubbcluj.ro/~rlupsa/edu/pdp/index.html"
            };

        //DirectCallback.Run(hosts);
        //TasksMechanism.Run(hosts);
        AsyncTasksMechanism.Run(hosts);
    }
}
