/*
    Code by cristian antunez - kitty
    Bajo licencia de KittySoft.
    tuservermu.com.ve/
*/
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;

namespace KittySoft
{
    public class Kitty
    {
        private string rutaWebzen;
        public Kitty()
        {
            //Inicializamos las variables
            this.rutaWebzen = @"HKEY_CURRENT_USER\Software\Webzen\Mu\Config";
        }

        //METODOS

        //*CONFIGURACIONES*//

        //*=======================================================================*//
        //Metodo encargado de obtener el id 
        public string getIdUser() 
        {
            object IdUser = Registry.GetValue(this.rutaWebzen, "ID", null);
            if (null != IdUser)
            {    
                return IdUser.ToString();
            }
            else { return ""; }
        }

        //Metodo encargado de obtener la resolucion de pantalla
        public int getResolucion()
        {
            object Resolucion = Registry.GetValue(this.rutaWebzen, "Resolution", null);
            if (null != Resolucion)
            {
                return (int)Resolucion;
            }
            else { return 0; }
        }

        //Metodo encargado de obtener la musica
        public int getMusica() 
        {
            object Musica = Registry.GetValue(this.rutaWebzen, "MusicOnOff", null);
            if (null != Musica)
            {
                return (int)Musica;
            }
            else { return 0; }
        }

        //Metodo encargado de obtener el sonido
        public int getSonido() 
        {
            object Sonido = Registry.GetValue(this.rutaWebzen, "SoundOnOff", null);
            if (null != Sonido)
            {
                return (int)Sonido;
            }
            else { return 0; }
        }

        //Metodo encargado de obtener el Modo Ventana
        public int getVentana() 
        {
            object Ventana = Registry.GetValue(this.rutaWebzen, "WindowMode", null);
            if (null != Ventana)
            {
                return (int)Ventana;
            }
            else { return 0; }
        }

        //Método encargado de obtener el ColorBit
        public int getColorBit() 
        {
            object ColorBit = Registry.GetValue(this.rutaWebzen, "DisplayColorBit", null);
            if (null != ColorBit)
            {
                return (int)ColorBit;
            }
            else { return 0; }
        }

        //Metodo encargado de obtener el Lenguaje
        public string getIdioma() 
        { 
            object Idioma = Registry.GetValue(this.rutaWebzen, "LangSelection", null);
            if (null != Idioma)
            {
                return Idioma.ToString();
            }
            else { return "Spn"; }
        }

        //*=======================================================================*//

        //Método encargado de guardar todas las configuraciones
        public void setConfiguracion(string IdUser, int Ventana, int Resolucion, int ColorBit, int Sonido, int Musica, string Idioma) 
        {

            Registry.SetValue(this.rutaWebzen, "ID", IdUser);
            Registry.SetValue(this.rutaWebzen, "WindowMode", Ventana);
            Registry.SetValue(this.rutaWebzen, "Resolution", Resolucion);
            Registry.SetValue(this.rutaWebzen, "DisplayColorBit", ColorBit);
            Registry.SetValue(this.rutaWebzen, "SoundOnOff", Sonido);
            Registry.SetValue(this.rutaWebzen, "MusicOnOff", Musica);
            Registry.SetValue(this.rutaWebzen, "LangSelection", Idioma);
        }
        

    }

    public class LeerInis
    {
        //ATRIBUTOS
        string Path;
        string EXE = Assembly.GetExecutingAssembly().GetName().Name;

        [DllImport("kernel32", CharSet = CharSet.Unicode)]
        static extern long WritePrivateProfileString(string Section, string Key, string Value, string FilePath);

        [DllImport("kernel32", CharSet = CharSet.Unicode)]
        static extern int GetPrivateProfileString(string Section, string Key, string Default, StringBuilder RetVal, int Size, string FilePath);

        public LeerInis(string IniPath = null)
        {
            Path = new FileInfo(IniPath ?? EXE + ".ini").FullName.ToString();
        }

        public string Read(string Key, string Section = null)
        {
            var RetVal = new StringBuilder(255);
            GetPrivateProfileString(Section ?? EXE, Key, "", RetVal, 255, Path);
            return RetVal.ToString();
        }

        public void Write(string Key, string Value, string Section = null)
        {
            WritePrivateProfileString(Section ?? EXE, Key, Value, Path);
        }

        public void DeleteKey(string Key, string Section = null)
        {
            Write(Key, null, Section ?? EXE);
        }

        public void DeleteSection(string Section = null)
        {
            Write(null, null, Section ?? EXE);
        }

        public bool KeyExists(string Key, string Section = null)
        {
            return Read(Key, Section).Length > 0;
        }
    }

}
