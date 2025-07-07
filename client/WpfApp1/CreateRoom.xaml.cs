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
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Window
    {
        public CreateRoom()
        {
            InitializeComponent();
        }


        private void CreateBtn_Click(object sender, RoutedEventArgs e)
        {
            JObject j = new JObject();
            j["roomName"] = Room_Name.Text;
            j["maxUsers"] = Player_Amount.Text;
            j["questionCount"] = Question_Amount.Text;
            j["answerTimeout"] = Question_Time.Text;
            byte[] buffer = tcp.Serialize(j, 7);

            tcp.clientStream.Write(buffer, 0, buffer.Length);
            tcp.clientStream.Flush();
            message res = tcp.Deserialize();
            int status = Convert.ToInt32((string)res.content["status"]);

            if (status == 61)
            {
                AdminRoom adminRoom = new AdminRoom();
                adminRoom.Left = this.Left;
                adminRoom.Top = this.Top;
                adminRoom.Show();
                this.Close();
            }
        }

        private void backBtn_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu();
            menu.Left = this.Left;
            menu.Top = this.Top;
            menu.Show();
            this.Close();
        }
    }
}
