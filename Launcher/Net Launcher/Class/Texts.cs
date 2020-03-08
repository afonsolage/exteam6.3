using System;
using System.Collections.Generic;

namespace Net_Launcher.Class
{
    class Texts
    {
        private static Dictionary<string, string> Text = new Dictionary<string, string>
        {
            {"UNKNOWNERROR",                    "Se ha producido un error desconocido, pero crítico. Mensaje de error que puede ayudar a resolver el problema: \n{0}"},
            {"MISSINGBINARY",                   "El juego no se puede iniciar, porque falta {0}."},
            {"CANNOTSTART",                     "No se puede iniciar el juego, probablemente sea tu antivirus, por favor apágalo."},
            {"NONETWORK",                       "No se puede conectar al servidor, compruebe la configuración de red y vuelva a intentarlo."},
            {"CONNECTING",                      "Conectando al servidor..."},
            {"LISTDOWNLOAD",                    "Checkeando actualizacion."},
            {"CHECKFILE",                       "Checkeando archivos: {0} revisando ..."},
            {"DOWNLOADFILE",                    "Descargando archivos: {0} [{1}/{2}]"},
            {"COMPLETEPROGRESS",                "{0}%"},
            {"CURRENTPROGRESS",                 "{0}%"},
            {"CHECKCOMPLETE",                   "Todos los archivos han sido verificados correctamente."},
            {"DOWNLOADCOMPLETE",                "Actualizacion completada."},
            {"DOWNLOADSPEED",                   "{0} kb/s"}
        };

        private static Dictionary<string, string> Text2 = new Dictionary<string, string>
        {
            {"UNKNOWNERROR",                    "An unknown but critical error has occurred. Error message that can help solve the problem: \n{0}"},
            {"MISSINGBINARY",                   "The game cannot be started, because it is missing {0}."},
            {"CANNOTSTART",                     "Cannot start the game, probably your antivirus, please turn it off."},
            {"NONETWORK",                       "Unable to connect to the server, check the network settings and try again."},
            {"CONNECTING",                      "Connecting to the server..."},
            {"LISTDOWNLOAD",                    "Checking update."},
            {"CHECKFILE",                       "Checking files: {0} checking ..."},
            {"DOWNLOADFILE",                    "Downloading files: {0} [{1}/{2}]"},
            {"COMPLETEPROGRESS",                "{0}%"},
            {"CURRENTPROGRESS",                 "{0}%"},
            {"CHECKCOMPLETE",                   "All files have been verified correctly."},
            {"DOWNLOADCOMPLETE",                "Update completed."},
            {"DOWNLOADSPEED",                   "{0} kb/s"}
        };

        private static Dictionary<string, string> Text3 = new Dictionary<string, string>
        {
            {"UNKNOWNERROR",                    "Ocorreu um erro desconhecido, mas crítico. Mensagem de erro que pode ajudar a resolver o problema: \n{0}"},
            {"MISSINGBINARY",                   "O jogo não pode ser iniciado, porque está faltando {0}."},
            {"CANNOTSTART",                     "Não é possível iniciar o jogo, provavelmente o seu antivírus, por favor, desligue-o."},
            {"NONETWORK",                       "Não foi possível conectar-se ao servidor, verifique as configurações de rede e tente novamente."},
            {"CONNECTING",                      "Conectando ao servidor..."},
            {"LISTDOWNLOAD",                    "Verificando atualização."},
            {"CHECKFILE",                       "Verificando arquivos: {0} verificando..."},
            {"DOWNLOADFILE",                    "Download de arquivos: {0} [{1}/{2}]"},
            {"COMPLETEPROGRESS",                "{0}%"},
            {"CURRENTPROGRESS",                 "{0}%"},
            {"CHECKCOMPLETE",                   "Todos os arquivos foram verificados corretamente."},
            {"DOWNLOADCOMPLETE",                "Atualização concluída."},
            {"DOWNLOADSPEED",                   "{0} kb/s"}
        };

        public static string GetText(string Key, params object[] Arguments)
        {
            
            if (Common.getIdioma().ToLower() == "Spn".ToLower())
            {
                foreach (var currentItem in Text)
                {
                    if (currentItem.Key == Key)
                    {
                        return string.Format(currentItem.Value, Arguments);
                    }
                }
            }
            else if (Common.getIdioma().ToLower() == "Eng".ToLower())
            {
                foreach (var currentItem in Text2)
                {
                    if (currentItem.Key == Key)
                    {
                        return string.Format(currentItem.Value, Arguments);
                    }
                }
            }
            else if (Common.getIdioma().ToLower() == "Por".ToLower())
            {
                foreach (var currentItem in Text3)
                {
                    if (currentItem.Key == Key)
                    {
                        return string.Format(currentItem.Value, Arguments);
                    }
                }
            }

            return "Por";
        }
    }
}
