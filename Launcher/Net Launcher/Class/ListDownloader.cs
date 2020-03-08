using System;
using System.ComponentModel;
using System.IO;
using System.Net;
using System.Windows.Forms;

namespace Net_Launcher.Class
{
    class ListDownloader
    {
        public static void DownloadList()
        {
            BackgroundWorker backgroundWorker = new BackgroundWorker();

            Common.ChangeStatus("LISTDOWNLOAD");

            backgroundWorker.DoWork += backgroundWorker_DoWork;
            backgroundWorker.RunWorkerCompleted += backgroundWorker_RunWorkerCompleted;

            if (backgroundWorker.IsBusy)
            {
                MessageBox.Show(Texts.GetText("UNKNOWNERROR", "DownloadList isBusy"));
                Application.Exit();
            }
            else
            {
                backgroundWorker.RunWorkerAsync();
            }
        }

        private static void backgroundWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            WebClient webClient = new WebClient();

            int version = Common.CurrentVersion();
            bool success = true;
            while (success)
            {
                try
                {
                    var url = Common.URL_UPDATE + string.Format("{0}/", version) + Globals.PatchlistName;
                    Stream stream = webClient.OpenRead(url);

                    StreamReader streamReader = new StreamReader(stream);

                    while (!streamReader.EndOfStream)
                    {
                        ListProcessor.AddFile(streamReader.ReadLine(), version);
                    }

                    version++;
                }
                catch (Exception)
                {
                    success = false;
                    version--;
                }
            }
            ListProcessor.KeepLastestVersions();
            Common.Version = version;
        }

        private static void backgroundWorker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            FileChecker.CheckFiles();
        }
    }
}
