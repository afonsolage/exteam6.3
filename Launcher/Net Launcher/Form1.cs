/*
    Code by cristian antunez - kitty
    Bajo licencia de KittySoft.
    tuservermu.com.ve/
*/
using Net_Launcher.Class;
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace Net_Launcher
{
    public partial class Form1 : Form
    {
        public const int WM_NCLBUTTONDOWN = 0xA1;
        public const int HT_CAPTION = 0x2;

        [DllImportAttribute("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd,int Msg, int wParam, int lParam);
        [DllImportAttribute("user32.dll")]
        public static extern bool ReleaseCapture();

        //Variables Glovales
        public string UrlMu, UrlUpdate, UrlSlider, NombreServidor;
        public Form1()
        {
            InitializeComponent();

            Globals.pForm = this;

            //Obtenemos las configuraciones
            if (Common.getIdioma() == "Spn") 
            {
                label2.Text = "Archivo";
                label3.Text = "Total";
                btn_jugar.Text = "Jugar";
            }
            else if (Common.getIdioma() == "Eng") 
            {
                label2.Text = "Archive";
                label3.Text = "Total";
                btn_jugar.Text = "Play";
            }
            else if (Common.getIdioma() == "Por") 
            {
                label2.Text = "Arquivo";
                label3.Text = "Total";
                btn_jugar.Text = "Jogar";
            }
            else 
            {
                label2.Text = "Archivo";
                label3.Text = "Total";
                btn_jugar.Text = "Jugar";
            }

            tm_test.Start();
        }

        private void LeerIni(string Archivo = null) 
        {
            this.UrlMu = Common.URL_MU;
            this.UrlUpdate = Common.URL_UPDATE;
            this.UrlSlider = Common.URL_SLIDER;
            this.NombreServidor = Common.SERVER_NAME;


            //Preguntamos si el nombre del servidor no esta vacio
            if (this.NombreServidor != string.Empty)
            {
                lbl_nombreMuOnline.Text = this.NombreServidor;
            }
            else
            {
                lbl_nombreMuOnline.Text = "Net Launcher";
            }

        }


        private void btn_jugar_Click(object sender, EventArgs e)
        {

            if (Common.IsGameRunning())
            {
                Common.EnableStart();
            }
            else
            {
                Networking.CheckNetwork();
            }

            lbl_mensajes.ResetText();
            btn_jugar.Enabled = false;
        }

        private void btn_cerrar_Click(object sender, EventArgs e)
        {
            Application.Exit(); //Cerramos la aplicacion
        }

        private void btn_minimizar_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized; //Minimizamos el launcher
        }

        private void tm_test_Tick(object sender, EventArgs e)
        {
            if(panel_progressbar1.Width < 560)
            {
               
               panel_progressbar1.Width += (int)11.2;
               panel_progressbar2.Width += (int)11.2;
               lbl_progresoArchivo.Text = Convert.ToString(Math.Round(Convert.ToDouble(panel_progressbar1.Width / 5.6), 0)) + "%";
               lbl_progresoTotal.Text = Convert.ToString(Math.Round(Convert.ToDouble(panel_progressbar2.Width / 5.6), 0)) + "%";
            }
            else
            {
                tm_test.Stop();
                if (Common.getIdioma() == "Spn")
                {
                    lbl_mensajes.Text = "Actualizacion completada.";
                }
                else if (Common.getIdioma() == "Eng")
                {
                    lbl_mensajes.Text = "Update completed.";
                }
                else if (Common.getIdioma() == "Por")
                {
                    lbl_mensajes.Text = "Atualização concluída.";
                }
                else { lbl_mensajes.Text = "Actualizacion completada."; }
                
            }
        }

        private void btn_configs_Click(object sender, EventArgs e)
        {
            Configuraciones cfgs = new Configuraciones();
            cfgs.Show();
            btn_configs.Enabled = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {   

            //Cargamos el slider
            WebBrowserSlider.Navigate(Common.URL_SLIDER);
            //Globals.ServerURL = global.;
        }

        private void lbl_nombreMuOnline_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                ReleaseCapture();
                SendMessage(Handle, WM_NCLBUTTONDOWN, HT_CAPTION, 0);
            }
        }
    }
}
