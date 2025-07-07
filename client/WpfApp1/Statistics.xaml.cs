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
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class Statistics : Window
    {
        public Statistics()
        {
            InitializeComponent();
        }

        private void BackBTN_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu();
            menu.Left = this.Left;
            menu.Top = this.Top;
            menu.Show();
            this.Close();
        }

        private void MyStatsBTN_Click(object sender, RoutedEventArgs e)
        {
            Personal_Stats personal_Stats = new Personal_Stats();
            personal_Stats.Left = this.Left;
            personal_Stats.Top = this.Top;
            personal_Stats.Show();
            this.Close();
        }

        private void RecordsBTN_Click(object sender, RoutedEventArgs e)
        {
            LeaderBoard leaderboard = new LeaderBoard();
            leaderboard.Left = this.Left;
            leaderboard.Top = this.Top;
            leaderboard.Show();
            this.Close();
        }
    }
}
