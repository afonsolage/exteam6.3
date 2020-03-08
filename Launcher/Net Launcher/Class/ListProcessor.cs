using System;
using System.Collections.Generic;
using System.Linq;

namespace Net_Launcher.Class
{
    class ListProcessor
    {
        public static void AddFile(string File, int Version)
        {
            Globals.File file = new Globals.File();

            file.Version = Version;
            file.Name = File.Split(' ')[0];
            file.Hash = File.Split(' ')[1];
            file.Size = Convert.ToInt64(File.Split(' ')[2]);

            Globals.Files.Add(file);
        }

        internal static void KeepLastestVersions()
        {
            var files = new List<Globals.File>(Globals.Files);
            var finalFiles = new List<Globals.File>(Globals.Files.Count);
            var readFiles = new List<string>();
            foreach(var f in files)
            {
                if (readFiles.Contains(f.Name))
                    continue;

                var maxVersion = files.Where(fl => fl.Name == f.Name).Max(fl => fl.Version);
                var latestFile = files.Where(fl => fl.Name == f.Name && fl.Version == maxVersion).First();
                finalFiles.Add(latestFile);
                readFiles.Add(latestFile.Name);
            }

            Globals.Files.Clear();
            Globals.Files.AddRange(finalFiles);
        }
    }
}
