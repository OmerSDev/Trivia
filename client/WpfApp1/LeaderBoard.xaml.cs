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
    /// Interaction logic for LeaderBoard.xaml
    /// </summary>
    public partial class LeaderBoard : Window
    {
        public LeaderBoard()
        {
            InitializeComponent();

            JObject j = new JObject();
            byte[] buffer = tcp.Serialize(j, 4);
            tcp.clientStream.Write(buffer, 0, buffer.Length);
            tcp.clientStream.Flush();
            message res = tcp.Deserialize();

            leaderboards.Visibility = Visibility.Visible;
            JArray arr = (JArray)res.content["HighScores"];
            leaderboards.Text = "";
            for (int i = 0; i < arr.Count; i++)
            {
                leaderboards.Text += "\n" + arr[i];
            }
        }

        private void BackBTN_Click(object sender, RoutedEventArgs e)
        {
            Statistics stats = new Statistics();
            stats.Left = this.Left;
            stats.Top = this.Top;
            stats.Show();
            this.Close();
        }
    }
}
