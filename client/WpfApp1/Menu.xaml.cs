using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for Menu.xaml
    /// </summary>
    public partial class Menu : Window
    {
        public Menu()
        {
            InitializeComponent();
        }

        private void CreateBtn_Click(object sender, RoutedEventArgs e)
        {
            CreateRoom createRoom = new CreateRoom();
            createRoom.Left = this.Left;
            createRoom.Top = this.Top;
            createRoom.Show();
            this.Close();
        }

        private void JoinBtn_Click(object sender, RoutedEventArgs e)
        {
            JoinRoom joinRoom = new JoinRoom();
            joinRoom.Left = this.Left;
            joinRoom.Top = this.Top;
            joinRoom.Show();
            this.Close();
        }

        private void StatsBtn_Click(object sender, RoutedEventArgs e)
        {
            Statistics stats = new Statistics();
            stats.Left = this.Left;
            stats.Top = this.Top; 
            stats.Show();
            this.Close();
        }

        private void quitBtn_Click(object sender, RoutedEventArgs e)
        {
            JObject j = new JObject();
            byte[] buffer = tcp.Serialize(j, 1);
            tcp.clientStream.Write(buffer, 0, buffer.Length);
            tcp.clientStream.Flush();
            message res = tcp.Deserialize();

            int status = Convert.ToInt32((string)res.content["status"]);

            if (status == 33)
            {
                Login login = new Login();
                login.Left = this.Left;
                login.Top = this.Top;
                login.Show();
                this.Close();
            }
        }
    }
}
