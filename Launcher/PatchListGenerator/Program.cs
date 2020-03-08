using Cyclic.Redundancy.Check;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PatchListGenerator
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length < 1)
            {
                Console.WriteLine("Invalid usage. Just drag a folder containing all files to generate the patch list.");
                Console.Read();
                return;
            }

            var rootFolder = args[0];
            Console.WriteLine("Gererating patch list on {0}", rootFolder);

            File.Delete(rootFolder + "/patchlist.dat");
            using (var stream = File.OpenWrite(rootFolder + "/patchlist.dat"))
            {
                var files = Directory.EnumerateFiles(rootFolder, "*", SearchOption.AllDirectories);
                float cnt = 0f;
                float total = files.Count();
                int lastPrint = -1;
                foreach (string filePath in files)
                {
                    if (filePath.EndsWith("patchlist.dat"))
                        continue;

                    float perc = (cnt++ / total) * 100;
                    if ((int)perc > lastPrint)
                    {
                        lastPrint = (int)perc;
                        Console.WriteLine("{0}%", lastPrint);
                    }
                    var localName = filePath.Replace(rootFolder, "");
                    if (localName[0] == '\\')
                        localName = localName.Substring(1);

                    var line = string.Format("{0} {1} {2}\r\n", localName, GetHash(filePath), new FileInfo(filePath).Length);
                    var buffer = Encoding.ASCII.GetBytes(line);
                    stream.Write(buffer, 0, buffer.Length);
                }
            }
        }

        public static string GetHash(string Name)
        {
            if (Name == string.Empty)
                return string.Empty;

            CRC crc = new CRC();

            string Hash = string.Empty;

            using (FileStream fileStream = File.Open(Name, FileMode.Open))
            {
                foreach (byte b in crc.ComputeHash(fileStream))
                {
                    Hash += b.ToString("x2").ToLower();
                }
            }

            return Hash;
        }
    }
}
