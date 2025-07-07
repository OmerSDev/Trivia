using Newtonsoft.Json.Linq;
using System.Net;
using System.Net.Sockets;
using System.Security.Cryptography;
using System.Security.RightsManagement;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using static WpfApp1.Login;

namespace WpfApp1
{
    public class currRoom
    {
        public static int id;
    }

    public class message
    {
        public byte code;
        public int length;
        public JObject content;
    }

    public class login
    {
        public static string username;
    }

    public class tcp
    {
        public static TcpClient client;
        public static IPEndPoint serverEndPoint;
        public static NetworkStream clientStream;
        public static bool connected = false;

        public static message Deserialize()
        {
            message res = new message();
            byte[] buffer = new byte[4096];
            tcp.clientStream.Read(buffer, 0, 1);
            res.code = buffer[0];

            buffer = new byte[4096];
            tcp.clientStream.Read(buffer, 0, 4);
            res.length = BitConverter.ToInt32(buffer, 0);

            buffer = new byte[4096];
            tcp.clientStream.Read(buffer, 0, res.length);
            string json = Encoding.Default.GetString(buffer);
            res.content = JObject.Parse(json);

            //add error message
            //if(res.code == 0)
            //{

            //}
            return res;
        }

        public static byte[] Serialize(JObject j, byte c)
        {
            string json = j.ToString();

            byte[] code = new byte[1];
            code[0] = c;

            byte[] length = BitConverter.GetBytes(json.Length);
            byte[] content = Encoding.ASCII.GetBytes(json);

            byte[] buffer = new byte[code.Length + length.Length + content.Length];
            Buffer.BlockCopy(code, 0, buffer, 0, code.Length);
            Buffer.BlockCopy(length, 0, buffer, code.Length, length.Length);
            Buffer.BlockCopy(content, 0, buffer, code.Length + length.Length, content.Length);

            return buffer;
        }

        
    }
    
}
