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
    /// Interaction logic for WaitingRoom.xaml
    /// </summary>
    public partial class WaitingRoom : Window
    {
        System.Windows.Threading.DispatcherTimer dispatcherTimer = new System.Windows.Threading.DispatcherTimer();

        private void updateScreen(object sender, EventArgs e)
        {
            JObject j = new JObject();
            byte[] buffer = tcp.Serialize(j, 11);
            tcp.clientStream.Write(buffer, 0, buffer.Length);
            tcp.clientStream.Flush();
            message res = tcp.Deserialize();

            if (res.code == 10)
            {
                dispatcherTimer.Stop();
                Menu menu = new Menu();
                menu.Left = this.Left;
                menu.Top = this.Top;
                menu.Show();

                this.Close();
                return;
            }

            JArray players = (JArray)res.content["players"];
            playersList.Items.Clear();
            for (int i = 0; i < players.Count; i++)
            {
                playersList.Items.Add(players[i]);
            }

            answerTimeoutText.Text = "Answer Timeout: " + (string)res.content["answerTimeout"];
            questionCountText.Text = "Question Count: " + (string)res.content["questionCount"];
        }

        public WaitingRoom()
        {
            InitializeComponent();

            JObject j = new JObject();
            byte[] buffer = tcp.Serialize(j, 11);
            tcp.clientStream.Write(buffer, 0, buffer.Length);
            tcp.clientStream.Flush();
            message res = tcp.Deserialize();

            if (res.code == 10)
            {
                dispatcherTimer.Stop();
                Menu menu = new Menu();
                menu.Left = this.Left;
                menu.Top = this.Top;
                menu.Show();

                this.Close();
                return;
            }

            JArray players = (JArray)res.content["players"];
            playersList.Items.Clear();
            for (int i = 0; i < players.Count; i++)
            {
                playersList.Items.Add(players[i]);
            }

            answerTimeoutText.Text = "Answer Timeout: " + (string)res.content["answerTimeout"];
            questionCountText.Text = "Question Count: " + (string)res.content["questionCount"];

            dispatcherTimer.Tick += new EventHandler(updateScreen);
            dispatcherTimer.Interval = new TimeSpan(0, 0, 3);
            dispatcherTimer.Start();
        }

        private void ExitBTN_Click(object sender, RoutedEventArgs e)
        {
            JObject j = new JObject();
            byte[] buffer = tcp.Serialize(j, 10);
            tcp.clientStream.Write(buffer, 0, buffer.Length);
            tcp.clientStream.Flush();
            message res = tcp.Deserialize();

            dispatcherTimer.Stop();

            Menu menu = new Menu();
            menu.Left = this.Left;
            menu.Top = this.Top;
            menu.Show();
            this.Close();
        }
    }
}
