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
using static System.Net.Mime.MediaTypeNames;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for Personal_Stats.xaml
    /// </summary>
    public partial class Personal_Stats : Window
    {
        public Personal_Stats()
        {
            InitializeComponent();

            JObject j = new JObject();
            byte[] buffer = tcp.Serialize(j, 5);
            tcp.clientStream.Write(buffer, 0, buffer.Length);
            tcp.clientStream.Flush();
            message res = tcp.Deserialize();

            JArray arr = (JArray)res.content["UserStatistics"];

            AverageTimeStat.Text += ((float)arr[0]).ToString("0.00");
            CorrectAnswerStat.Text += arr[1];
            AnswerStat.Text += arr[2];
            GameStat.Text += arr[3];
            ScoreStat.Text += arr[4];

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
