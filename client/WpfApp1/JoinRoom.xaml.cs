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
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        private class rooms
        {
            public static string[] nameArr;
            public static string[] idArr;
        }

        System.Windows.Threading.DispatcherTimer dispatcherTimer = new System.Windows.Threading.DispatcherTimer();

        private void updateScreen(object sender, EventArgs e)
        {
            JObject j = new JObject();
            byte[] buffer = tcp.Serialize(j, 2);

            tcp.clientStream.Write(buffer, 0, buffer.Length);
            tcp.clientStream.Flush();
            message res = tcp.Deserialize();

            JArray arr = (JArray)res.content["Rooms"];
            rooms.nameArr = new string[arr.Count];
            rooms.idArr = new string[arr.Count];

            for (int i = 0; i < arr.Count; i++)
            {
                rooms.idArr[i] = arr[i]["id"].ToString();
                rooms.nameArr[i] = arr[i]["name"].ToString();
                if (!roomList.Items.Contains(rooms.nameArr[i]))
                {
                    roomList.Items.Insert(i, rooms.nameArr[i]);
                }
            }

            for (int i = 0; i < roomList.Items.Count; i++)
            {
                if (Array.Find(rooms.nameArr, name => name == roomList.Items[i].ToString()) == null)
                {
                    roomList.Items.Remove(roomList.Items[i]);
                }
            }
        }


        public JoinRoom()
        {
            InitializeComponent();

            JObject j = new JObject();
            byte[] buffer = tcp.Serialize(j, 2);

            tcp.clientStream.Write(buffer, 0, buffer.Length);
            tcp.clientStream.Flush();
            message res = tcp.Deserialize();

            JArray arr = (JArray)res.content["Rooms"];
            rooms.nameArr = new string[arr.Count];
            rooms.idArr = new string[arr.Count];

            for (int i = 0; i < arr.Count; i++)
            {
                rooms.idArr[i] = arr[i]["id"].ToString();
                rooms.nameArr[i] = arr[i]["name"].ToString();
                if (!roomList.Items.Contains(rooms.nameArr[i]))
                {
                    roomList.Items.Insert(i, rooms.nameArr[i]);
                }
            }

            for (int i = 0; i < roomList.Items.Count; i++)
            {
                if (Array.Find(rooms.nameArr, name => name == roomList.Items[i].ToString()) == null)
                {
                    roomList.Items.Remove(roomList.Items[i]);
                }
            }

            dispatcherTimer.Tick += new EventHandler(updateScreen);
            dispatcherTimer.Interval = new TimeSpan(0, 0, 3);
            dispatcherTimer.Start();


        }



        private void BackBTN_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu();
            menu.Left = this.Left;
            menu.Top = this.Top;
            menu.Show();
            this.Close();
        }

        private void EnterRoomBTN_Click(object sender, RoutedEventArgs e)
        {
            if (roomList.SelectedIndex != -1)
            {
                JObject j = new JObject();
                j["roomid"] = rooms.idArr[roomList.SelectedIndex];
                byte[] buffer = tcp.Serialize(j, 6);

                tcp.clientStream.Write(buffer, 0, buffer.Length);
                tcp.clientStream.Flush();
                message res = tcp.Deserialize();

                int status = Convert.ToInt32((string)res.content["status"]);

                if (status == 42)
                {
                    dispatcherTimer.Stop();
                    currRoom.id = int.Parse(rooms.idArr[roomList.SelectedIndex]);
                    WaitingRoom waitingRoom = new WaitingRoom();
                    waitingRoom.Left = this.Left;
                    waitingRoom.Top = this.Top;
                    waitingRoom.Show();
                    this.Close();
                }
            }
        }
    }
}
