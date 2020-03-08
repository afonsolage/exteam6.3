using System.Collections.Generic;

namespace Net_Launcher.Class
{
    class Globals
    {
        public static string PatchlistName = "patchlist.dat";
        public static string BinaryName = "main.exe";

        public static Form1 pForm;
        public static Configuraciones pConfigs;

        public static List<File> Files = new List<File>();
        public static List<File> OldFiles = new List<File>();

        public static long fullSize;
        public static long completeSize;

        public struct File
        {
            public int Version;
            public string Name;
            public string Hash;
            public long Size;
        }
    }
}
