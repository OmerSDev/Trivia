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

namespace WpfApp1
{
    public partial class Login : Window
    {
        

        public Login()
        {
            InitializeComponent();


            while (!tcp.connected)
            {
                try
                {
                    tcp.client = new TcpClient();
                    tcp.serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8326);
                    tcp.client.Connect(tcp.serverEndPoint);
                    tcp.clientStream = tcp.client.GetStream();
                    tcp.connected = true;
                }
                catch
                {
                }
            }


        }
        
        private void LoginBtn_Click(object sender, RoutedEventArgs e)
        {
            JObject j = new JObject();
            j["username"] = Username_Login.Text;
            j["password"] = Password_Login.Password;
            byte[] buffer = tcp.Serialize(j, 111);

            tcp.clientStream.Write(buffer, 0, buffer.Length);
            tcp.clientStream.Flush();
            message res = tcp.Deserialize();
            int status = Convert.ToInt32((string)res.content["status"]);

            if (status == 0)
            {
                login.username = Username_Login.Text;
                Menu menu = new Menu();
                menu.Left = this.Left;
                menu.Top = this.Top;
                menu.Show();
                this.Close();
            }
            
        }

        private void moveBtn_Click(object sender, RoutedEventArgs e)
        {
            SignUp signUp = new SignUp();
            signUp.Left = this.Left;
            signUp.Top = this.Top;
            signUp.Show();
            this.Close();
        }

    }
}