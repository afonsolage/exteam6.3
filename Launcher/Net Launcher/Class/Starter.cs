using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

namespace Net_Launcher.Class
{
    class Starter
    {
        public static void Start()
        {
            if (!File.Exists(Globals.BinaryName))
            {
                MessageBox.Show(Texts.GetText("MISSINGBINARY", Globals.BinaryName));

                return;
            }

            try
            {
                Common.SaveVersion();

                if (Common.UpdateLauncher)
                {
                    Process.Start(Globals.BinaryName, "UPD4T3");
                }
                else
                {
                    Process.Start(Globals.BinaryName, "e49696f06ce684e3d7d6");
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(Texts.GetText("UNKNOWNERROR", exception.Message));
                Application.Exit();
            }
        }
    }
}
