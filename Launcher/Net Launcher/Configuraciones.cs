/*
    Code by cristian antunez - kitty
    Bajo licencia de KittySoft.
    tuservermu.com.ve/
*/
using Net_Launcher.Class;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace Net_Launcher
{
    public partial class Configuraciones : Form
    {
        public const int WM_NCLBUTTONDOWN = 0xA1;
        public const int HT_CAPTION = 0x2;

        [DllImportAttribute("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd,
                         int Msg, int wParam, int lParam);
        [DllImportAttribute("user32.dll")]
        public static extern bool ReleaseCapture();

        public Configuraciones()
        {
            InitializeComponent();

            Globals.pConfigs = this;

            //Obtenemos el idioma
            Idioma idiomas = new Idioma();

            txt_idUsuario.Text = Common.getIdUser();
            cmb_resolucion.SelectedIndex = Common.getResolucion();
            //Obtenemos el checked del Modo ventana
            if (Common.getVentana() > 0) 
            {
                chk_modoVentana.Checked = true;
            }
            cmb_maxColor.SelectedIndex = Common.getColorBit();
            //Obtenemos el sonido
            if (Common.getSonido() > 0) 
            {
                chk_sonido.Checked = true;
            }
            //Obtenemos la musica
            if (Common.getMusica() > 0) 
            {
                chk_musica.Checked = true;
            }
        }

        private void btn_cancelar_Click(object sender, EventArgs e)
        {
            this.Close(); //Cerramos la ventana
        }

        private void ptb_moverForm_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                ReleaseCapture();
                SendMessage(Handle, WM_NCLBUTTONDOWN, HT_CAPTION, 0);
            }
        }

        private void btn_guardar_Click(object sender, EventArgs e)
        {

            //Obtenemos el idioma
            Idioma idiomas = new Idioma();

            int Ventana = 0, Musica = 0, Sonido = 0;

            if (chk_modoVentana.Checked == true) 
            {
                Ventana = 1;
            }
            if (chk_sonido.Checked == true) 
            {
                Sonido = 1;
            }
            if (chk_musica.Checked == true) 
            {
                Musica = 1;
            }

                idiomas.Eng();

            Globals.pForm.btn_configs.Enabled = true;
            Common.setConfiguracion(txt_idUsuario.Text, Ventana, cmb_resolucion.SelectedIndex, cmb_maxColor.SelectedIndex, Sonido, Musica);

            this.Close(); //Cerramos la ventana
        }

    }
}
