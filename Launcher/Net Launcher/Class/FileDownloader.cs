using System;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Net;

namespace Net_Launcher.Class
{
    class FileDownloader
    {
        private static int curFile;
        private static long lastBytes;
        private static long currentBytes;

        private static Stopwatch stopWatch = new Stopwatch();

        public static void DownloadFile()
        {
            if (Globals.OldFiles.Count <= 0)
            {
                Common.ChangeStatus("CHECKCOMPLETE");

                Common.UpdateCompleteProgress(100);
                Common.StartGame();
                return;
            }

            if (curFile >= Globals.OldFiles.Count)
            {
                Common.ChangeStatus("DOWNLOADCOMPLETE");
                Common.StartGame();

                return;
            }


            var oldFile = Globals.OldFiles[curFile];
            if (oldFile.Name.Contains("/"))
            {
                Directory.CreateDirectory(Path.GetDirectoryName(Globals.OldFiles[curFile].Name));
            }

            WebClient webClient = new WebClient();

            webClient.DownloadProgressChanged += new DownloadProgressChangedEventHandler(webClient_DownloadProgressChanged);

            webClient.DownloadFileCompleted += new AsyncCompletedEventHandler(webClient_DownloadFileCompleted);

            stopWatch.Start();

            webClient.DownloadFileAsync(new Uri(Common.URL_UPDATE + string.Format("{0}/", oldFile.Version) + oldFile.Name), oldFile.Name);
        }

        private static void webClient_DownloadProgressChanged(object sender, DownloadProgressChangedEventArgs e)
        {
            currentBytes = lastBytes + e.BytesReceived;

            Common.ChangeStatus("DOWNLOADFILE", Globals.OldFiles[curFile].Name, curFile.ToString(), Globals.OldFiles.Count.ToString());

            Common.UpdateCompleteProgress(Computer.Compute(Globals.completeSize + currentBytes));

            Common.UpdateCurrentProgress(e.ProgressPercentage, Computer.ComputeDownloadSpeed(e.BytesReceived, stopWatch));

        }

        private static void webClient_DownloadFileCompleted(object sender, AsyncCompletedEventArgs e)
        {
            lastBytes = currentBytes;

            Common.UpdateCurrentProgress(100, 0);

            curFile++;

            stopWatch.Reset();

            DownloadFile();
        }
    }
}
