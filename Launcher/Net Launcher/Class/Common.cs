using Cyclic.Redundancy.Check;
using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;
using System.Linq;
using Microsoft.Win32;

namespace Net_Launcher.Class
{
    class Common
    {
        private static string rutaWebzen = @"HKEY_CURRENT_USER\Software\LCMU\Config";

        public static readonly string URL_MU = @"https://lcmu.online/";
        public static readonly string URL_SLIDER = @"https://lcmu.online/?launcher_mode=1";
        public static readonly string SERVER_NAME = "LC Mu Online";
        public static readonly string URL_UPDATE = @"http://cdn.lcmu.online/update/";

        public static int Version = 0;
        public static bool UpdateLauncher = false;
        public static void ChangeStatus(string Key, params string[] Arguments)
        {
            Globals.pForm.lbl_infoArchivos.Visible = true;
            Globals.pForm.lbl_infoArchivos.Text = Texts.GetText(Key, Arguments);
        }

        public static void UpdateCompleteProgress(long Value)
        {
            if (Value < 0 || Value > 100)
                return;

            int result = Convert.ToInt32(Value * Math.Round(5.6, 0));
            Globals.pForm.panel_progressbar2.Width = result - 40;
            Globals.pForm.lbl_progresoTotal.Text = Texts.GetText("COMPLETEPROGRESS", Value);
            if (Value == 100)
            {
                Globals.pForm.panel_progressbar1.Width = 560;
            }
        }

        public static void UpdateCurrentProgress(long Value, double Speed)
        {
            if (Value < 0 || Value > 100)
                return;

            int result = Convert.ToInt32(Value * Math.Round(5.6, 0));
            Globals.pForm.panel_progressbar1.Width = result - 40;
            Globals.pForm.lbl_progresoArchivo.Text = Texts.GetText("CURRENTPROGRESS", Value, Speed.ToString("0.00"));
        }

        public static string GetHash(string Name)
        {
            if (Name == string.Empty)
                return string.Empty;

            try
            {
                CRC crc = new CRC();

                string Hash = string.Empty;

                using (FileStream fileStream = File.OpenRead(Name))
                {
                    foreach (byte b in crc.ComputeHash(fileStream))
                    {
                        Hash += b.ToString("x2").ToLower();
                    }
                }

                return Hash;
            }
            catch (Exception)
            {
                MessageBox.Show("Falha ao verificar os arquivos. Verifique o LC Mu Online já está aberto.", "Falha");
                Environment.Exit(1);
                return null;
            }
        }

        public static int CurrentVersion()
        {
            if (Version == 0 && File.Exists("Version.dat"))
            {
                try
                {
                    var buffer = File.ReadAllBytes("Version.dat");
                    Version = BitConverter.ToInt32(buffer, 0);
                } catch (Exception)
                {

                }
            }

            if (Version < 1)
            {
                Version = 1;
                SaveVersion();
            }

            return Version;
        }

        public static void SaveVersion()
        {
            File.WriteAllBytes("Version.dat", BitConverter.GetBytes(Version));
        }

        public static void EnableStart()
        {
            //Globals.pForm.btn_jugar.Enabled = true;
        }

        public static void StartGame()
        {
            Starter.Start();
            //Cerramos la aplicacion
            Application.Exit();
        }

        public static bool IsGameRunning()
        {
            return Process.GetProcessesByName(Globals.BinaryName).FirstOrDefault(p => p.MainModule.FileName.StartsWith("")) != default(Process);
        }

        public static string getIdUser()
        {
            object IdUser = Registry.GetValue(rutaWebzen, "ID", null);
            if (null != IdUser)
            {
                return IdUser.ToString();
            }
            else { return ""; }
        }

        //Metodo encargado de obtener la resolucion de pantalla
        public static int getResolucion()
        {
            object Resolucion = Registry.GetValue(rutaWebzen, "Resolution", null);
            if (null != Resolucion)
            {
                return (int)Resolucion;
            }
            else { return 0; }
        }

        //Metodo encargado de obtener la musica
        public static int getMusica()
        {
            object Musica = Registry.GetValue(rutaWebzen, "MusicOnOff", null);
            if (null != Musica)
            {
                return (int)Musica;
            }
            else { return 0; }
        }

        //Metodo encargado de obtener el sonido
        public static int getSonido()
        {
            object Sonido = Registry.GetValue(rutaWebzen, "SoundOnOff", null);
            if (null != Sonido)
            {
                return (int)Sonido;
            }
            else { return 0; }
        }

        //Metodo encargado de obtener el Modo Ventana
        public static int getVentana()
        {
            object Ventana = Registry.GetValue(rutaWebzen, "WindowMode", null);
            if (null != Ventana)
            {
                return (int)Ventana;
            }
            else { return 0; }
        }

        //Método encargado de obtener el ColorBit
        public static int getColorBit()
        {
            object ColorBit = Registry.GetValue(rutaWebzen, "DisplayColorBit", null);
            if (null != ColorBit)
            {
                return (int)ColorBit;
            }
            else { return 0; }
        }

        //*=======================================================================*//

        //Método encargado de guardar todas las configuraciones
        public static void setConfiguracion(string IdUser, int Ventana, int Resolucion, int ColorBit, int Sonido, int Musica)
        {

            Registry.SetValue(rutaWebzen, "ID", IdUser);
            Registry.SetValue(rutaWebzen, "WindowMode", Ventana);
            Registry.SetValue(rutaWebzen, "Resolution", Resolucion);
            Registry.SetValue(rutaWebzen, "DisplayColorBit", ColorBit);
            Registry.SetValue(rutaWebzen, "SoundOnOff", Sonido);
            Registry.SetValue(rutaWebzen, "MusicOnOff", Musica);
        }
    }
}
