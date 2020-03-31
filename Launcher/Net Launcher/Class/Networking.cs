using System;
using System.ComponentModel;
using System.Net;
using System.Windows.Forms;

namespace Net_Launcher.Class
{
    class Networking
    {
        public static void CheckNetwork()
        {
            Common.ChangeStatus("CONNECTING");

            BackgroundWorker backgroundWorker = new BackgroundWorker();

            backgroundWorker.DoWork += backgroundWorker_DoWork;
            backgroundWorker.RunWorkerCompleted += backgroundWorker_RunWorkerCompleted;

            if (backgroundWorker.IsBusy)
            {
                MessageBox.Show(Texts.GetText("UNKNOWNERROR", "CheckNetwork isBusy"));
                Application.Exit();
            }
            else
            {
                backgroundWorker.RunWorkerAsync();
            }
        }

        private static void backgroundWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            try
            {
                WebClient client = new WebClient();
                client.OpenRead(Common.URL_UPDATE);

                e.Result = true;
            }
            catch (Exception ex)
            {
                e.Result = false;
            }
        }

        private static void backgroundWorker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (!Convert.ToBoolean(e.Result))
            {
                MessageBox.Show(Texts.GetText("NONETWORK"));
                Application.Exit();
            }
            
            ListDownloader.DownloadList();
        }
    }
}
