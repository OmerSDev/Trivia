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
using static WpfApp1.Login;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for SignUp.xaml
    /// </summary>
    public partial class SignUp : Window
    {
        public SignUp()
        {
            InitializeComponent();
        }

        private void backBtn_Click(object sender, RoutedEventArgs e)
        {
            Login main = new Login();
            main.Left = this.Left;
            main.Top = this.Top;
            main.Show();
            this.Close();
        }

        private void SignupBtn_Click(object sender, RoutedEventArgs e)
        {
            JObject j = new JObject();
            j["username"] = Username_Signup.Text;
            j["password"] = Password_Signup.Password;
            j["mail"] = Email_Signup.Text;
            byte[] buffer = tcp.Serialize(j, 222);

            tcp.clientStream.Write(buffer, 0, buffer.Length);
            tcp.clientStream.Flush();
            message res = tcp.Deserialize();
            int status = Convert.ToInt32((string)res.content["status"]);

            if (status == 31)
            {
                Username_Signup.Text = "";
                Password_Signup.Password = "";
                Email_Signup.Text = "";
            }
            Login main = new Login();
            main.Left = this.Left;
            main.Top = this.Top;
            main.Show();
            this.Close();
        }
    }
}
