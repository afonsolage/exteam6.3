using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Net_Launcher.Class
{
    public class Idioma
    {
        //Atributos

        //Metodos
        public void Spn() 
        {

            try
            {
                //Idioma Main
                Globals.pForm.label2.Text = "Archivo";
                Globals.pForm.label3.Text = "Total";
                Globals.pForm.btn_jugar.Text = "Jugar";
                Globals.pForm.lbl_mensajes.Text = "Actualizacion completada.";

                //Idioma Configuraciones
                Globals.pConfigs.label1.Text = "Configuraciones";
                Globals.pConfigs.label2.Text = "ID por defecto";
                Globals.pConfigs.label3.Text = "Resolucion";
                Globals.pConfigs.label4.Text = "Opciones";
                ///////////////////////////////////
                Globals.pConfigs.chk_modoVentana.Text = "Modo Ventana";
                Globals.pConfigs.chk_sonido.Text = "Efectos de sonido";
                Globals.pConfigs.chk_musica.Text = "Musica";
                ///////////////////////////////////
                Globals.pConfigs.cmb_resolucion.Text = "- Resolucion";
                ///////////////////////////////////
                Globals.pConfigs.btn_cancelar.Text = "Cancelar";
                Globals.pConfigs.btn_guardar.Text = "Guardar";
            }
            catch (Exception)
            {
                
                throw;
            }
        }

        public void Eng()
        {

            try
            {
                //Idioma Main
                Globals.pForm.label2.Text = "Archive";
                Globals.pForm.label3.Text = "Total";
                Globals.pForm.btn_jugar.Text = "To Play";
                Globals.pForm.lbl_mensajes.Text = "Update completed.";

                //Idioma Configuraciones
                Globals.pConfigs.label1.Text = "Configurations";
                Globals.pConfigs.label2.Text = "Default ID";
                Globals.pConfigs.label3.Text = "Resolution";
                Globals.pConfigs.label4.Text = "Options";
                ///////////////////////////////////
                Globals.pConfigs.chk_modoVentana.Text = "Window Mode";
                Globals.pConfigs.chk_sonido.Text = "Sound effects";
                Globals.pConfigs.chk_musica.Text = "Music";
                ///////////////////////////////////
                Globals.pConfigs.cmb_resolucion.Text = "- Resolution";
                ///////////////////////////////////
                Globals.pConfigs.btn_cancelar.Text = "Cancel";
                Globals.pConfigs.btn_guardar.Text = "Save";
            }
            catch (Exception)
            {

                throw;
            }
        }

        public void Por()
        {

            try
            {
                //Idioma Main
                Globals.pForm.label2.Text = "Arquivo";
                Globals.pForm.label3.Text = "Total";
                Globals.pForm.btn_jugar.Text = "Reproduzir";
                Globals.pForm.lbl_mensajes.Text = "Atualização concluída.";

                //Idioma Configuraciones
                Globals.pConfigs.label1.Text = "Configurações";
                Globals.pConfigs.label2.Text = "ID padrão";
                Globals.pConfigs.label3.Text = "Resolução";
                Globals.pConfigs.label4.Text = "Opções";
                ///////////////////////////////////
                Globals.pConfigs.chk_modoVentana.Text = "Modo de janela";
                Globals.pConfigs.chk_sonido.Text = "Efeitos sonoros";
                Globals.pConfigs.chk_musica.Text = "Música";
                ///////////////////////////////////
                Globals.pConfigs.cmb_resolucion.Text = "- Resolução";
                ///////////////////////////////////
                Globals.pConfigs.btn_cancelar.Text = "Cancelar";
                Globals.pConfigs.btn_guardar.Text = "Salvar";
            }
            catch (Exception)
            {
                
                throw;
            }
        }

    }
}
