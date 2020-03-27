namespace Net_Launcher
{
    partial class Form1
    {
        /// <summary>
        /// Variable del diseñador requerida.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén utilizando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido del método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel_progressbar1 = new System.Windows.Forms.Panel();
            this.panel_progressbar2 = new System.Windows.Forms.Panel();
            this.btn_jugar = new System.Windows.Forms.Button();
            this.btn_cerrar = new System.Windows.Forms.Button();
            this.btn_minimizar = new System.Windows.Forms.Button();
            this.tm_test = new System.Windows.Forms.Timer(this.components);
            this.lbl_mensajes = new System.Windows.Forms.Label();
            this.lbl_progresoArchivo = new System.Windows.Forms.Label();
            this.lbl_progresoTotal = new System.Windows.Forms.Label();
            this.btn_configs = new System.Windows.Forms.Button();
            this.lbl_infoArchivos = new System.Windows.Forms.Label();
            this.WebBrowserSlider = new System.Windows.Forms.WebBrowser();
            this.lbl_nombreMuOnline = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.Red;
            this.label2.Location = new System.Drawing.Point(33, 501);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(66, 18);
            this.label2.TabIndex = 2;
            this.label2.Text = "Arquivo";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BackColor = System.Drawing.Color.Transparent;
            this.label3.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.Color.Red;
            this.label3.Location = new System.Drawing.Point(33, 530);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(46, 18);
            this.label3.TabIndex = 3;
            this.label3.Text = "Total";
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(109)))), ((int)(((byte)(131)))));
            this.panel1.Location = new System.Drawing.Point(112, 496);
            this.panel1.Margin = new System.Windows.Forms.Padding(4);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(747, 22);
            this.panel1.TabIndex = 4;
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(235)))), ((int)(((byte)(157)))), ((int)(((byte)(148)))));
            this.panel2.Location = new System.Drawing.Point(112, 526);
            this.panel2.Margin = new System.Windows.Forms.Padding(4);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(747, 22);
            this.panel2.TabIndex = 5;
            // 
            // panel_progressbar1
            // 
            this.panel_progressbar1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(169)))), ((int)(((byte)(72)))), ((int)(((byte)(97)))));
            this.panel_progressbar1.Location = new System.Drawing.Point(112, 496);
            this.panel_progressbar1.Margin = new System.Windows.Forms.Padding(4);
            this.panel_progressbar1.MaximumSize = new System.Drawing.Size(747, 22);
            this.panel_progressbar1.MinimumSize = new System.Drawing.Size(0, 22);
            this.panel_progressbar1.Name = "panel_progressbar1";
            this.panel_progressbar1.Size = new System.Drawing.Size(0, 22);
            this.panel_progressbar1.TabIndex = 6;
            // 
            // panel_progressbar2
            // 
            this.panel_progressbar2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(221)))), ((int)(((byte)(106)))), ((int)(((byte)(94)))));
            this.panel_progressbar2.Location = new System.Drawing.Point(112, 526);
            this.panel_progressbar2.Margin = new System.Windows.Forms.Padding(4);
            this.panel_progressbar2.MaximumSize = new System.Drawing.Size(747, 22);
            this.panel_progressbar2.MinimumSize = new System.Drawing.Size(0, 22);
            this.panel_progressbar2.Name = "panel_progressbar2";
            this.panel_progressbar2.Size = new System.Drawing.Size(0, 22);
            this.panel_progressbar2.TabIndex = 7;
            // 
            // btn_jugar
            // 
            this.btn_jugar.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(27)))), ((int)(((byte)(28)))), ((int)(((byte)(34)))));
            this.btn_jugar.Cursor = System.Windows.Forms.Cursors.Default;
            this.btn_jugar.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(16)))), ((int)(((byte)(17)))), ((int)(((byte)(20)))));
            this.btn_jugar.FlatAppearance.MouseDownBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(27)))), ((int)(((byte)(28)))), ((int)(((byte)(34)))));
            this.btn_jugar.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_jugar.Font = new System.Drawing.Font("Tahoma", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_jugar.ForeColor = System.Drawing.Color.White;
            this.btn_jugar.Location = new System.Drawing.Point(920, 485);
            this.btn_jugar.Margin = new System.Windows.Forms.Padding(4);
            this.btn_jugar.Name = "btn_jugar";
            this.btn_jugar.Size = new System.Drawing.Size(160, 74);
            this.btn_jugar.TabIndex = 8;
            this.btn_jugar.Text = "Jogar";
            this.btn_jugar.UseVisualStyleBackColor = false;
            this.btn_jugar.Click += new System.EventHandler(this.btn_jugar_Click);
            // 
            // btn_cerrar
            // 
            this.btn_cerrar.BackColor = System.Drawing.Color.Transparent;
            this.btn_cerrar.FlatAppearance.BorderSize = 0;
            this.btn_cerrar.FlatAppearance.MouseDownBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(212)))), ((int)(((byte)(46)))), ((int)(((byte)(46)))));
            this.btn_cerrar.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(67)))), ((int)(((byte)(67)))));
            this.btn_cerrar.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_cerrar.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_cerrar.ForeColor = System.Drawing.Color.White;
            this.btn_cerrar.Location = new System.Drawing.Point(1073, 0);
            this.btn_cerrar.Margin = new System.Windows.Forms.Padding(4);
            this.btn_cerrar.Name = "btn_cerrar";
            this.btn_cerrar.Size = new System.Drawing.Size(40, 37);
            this.btn_cerrar.TabIndex = 9;
            this.btn_cerrar.Text = "X";
            this.btn_cerrar.UseVisualStyleBackColor = false;
            this.btn_cerrar.Click += new System.EventHandler(this.btn_cerrar_Click);
            // 
            // btn_minimizar
            // 
            this.btn_minimizar.BackColor = System.Drawing.Color.Transparent;
            this.btn_minimizar.FlatAppearance.BorderSize = 0;
            this.btn_minimizar.FlatAppearance.MouseDownBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(45)))), ((int)(((byte)(89)))), ((int)(((byte)(161)))));
            this.btn_minimizar.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(54)))), ((int)(((byte)(101)))), ((int)(((byte)(179)))));
            this.btn_minimizar.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_minimizar.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_minimizar.ForeColor = System.Drawing.Color.White;
            this.btn_minimizar.Location = new System.Drawing.Point(1033, 0);
            this.btn_minimizar.Margin = new System.Windows.Forms.Padding(4);
            this.btn_minimizar.Name = "btn_minimizar";
            this.btn_minimizar.Size = new System.Drawing.Size(40, 37);
            this.btn_minimizar.TabIndex = 10;
            this.btn_minimizar.Text = "--";
            this.btn_minimizar.UseVisualStyleBackColor = false;
            this.btn_minimizar.Click += new System.EventHandler(this.btn_minimizar_Click);
            // 
            // tm_test
            // 
            this.tm_test.Interval = 10;
            this.tm_test.Tick += new System.EventHandler(this.tm_test_Tick);
            // 
            // lbl_mensajes
            // 
            this.lbl_mensajes.AutoSize = true;
            this.lbl_mensajes.BackColor = System.Drawing.Color.Transparent;
            this.lbl_mensajes.Font = new System.Drawing.Font("Tahoma", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_mensajes.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(205)))), ((int)(((byte)(50)))), ((int)(((byte)(90)))));
            this.lbl_mensajes.Location = new System.Drawing.Point(108, 562);
            this.lbl_mensajes.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lbl_mensajes.Name = "lbl_mensajes";
            this.lbl_mensajes.Size = new System.Drawing.Size(0, 24);
            this.lbl_mensajes.TabIndex = 11;
            // 
            // lbl_progresoArchivo
            // 
            this.lbl_progresoArchivo.BackColor = System.Drawing.Color.Transparent;
            this.lbl_progresoArchivo.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_progresoArchivo.ForeColor = System.Drawing.Color.Red;
            this.lbl_progresoArchivo.Location = new System.Drawing.Point(867, 502);
            this.lbl_progresoArchivo.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lbl_progresoArchivo.MaximumSize = new System.Drawing.Size(44, 16);
            this.lbl_progresoArchivo.MinimumSize = new System.Drawing.Size(44, 16);
            this.lbl_progresoArchivo.Name = "lbl_progresoArchivo";
            this.lbl_progresoArchivo.Size = new System.Drawing.Size(44, 16);
            this.lbl_progresoArchivo.TabIndex = 12;
            this.lbl_progresoArchivo.Text = "100%";
            // 
            // lbl_progresoTotal
            // 
            this.lbl_progresoTotal.BackColor = System.Drawing.Color.Transparent;
            this.lbl_progresoTotal.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_progresoTotal.ForeColor = System.Drawing.Color.Red;
            this.lbl_progresoTotal.Location = new System.Drawing.Point(867, 532);
            this.lbl_progresoTotal.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lbl_progresoTotal.MaximumSize = new System.Drawing.Size(44, 16);
            this.lbl_progresoTotal.MinimumSize = new System.Drawing.Size(44, 16);
            this.lbl_progresoTotal.Name = "lbl_progresoTotal";
            this.lbl_progresoTotal.Size = new System.Drawing.Size(44, 16);
            this.lbl_progresoTotal.TabIndex = 13;
            this.lbl_progresoTotal.Text = "100%";
            // 
            // btn_configs
            // 
            this.btn_configs.BackColor = System.Drawing.Color.Transparent;
            this.btn_configs.FlatAppearance.BorderSize = 0;
            this.btn_configs.FlatAppearance.MouseDownBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(71)))), ((int)(((byte)(42)))), ((int)(((byte)(157)))));
            this.btn_configs.FlatAppearance.MouseOverBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(81)))), ((int)(((byte)(51)))), ((int)(((byte)(171)))));
            this.btn_configs.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_configs.Image = global::Launcher.Properties.Resources.icon_configs;
            this.btn_configs.Location = new System.Drawing.Point(993, 0);
            this.btn_configs.Margin = new System.Windows.Forms.Padding(4);
            this.btn_configs.Name = "btn_configs";
            this.btn_configs.Size = new System.Drawing.Size(40, 37);
            this.btn_configs.TabIndex = 14;
            this.btn_configs.UseVisualStyleBackColor = false;
            this.btn_configs.Click += new System.EventHandler(this.btn_configs_Click);
            // 
            // lbl_infoArchivos
            // 
            this.lbl_infoArchivos.BackColor = System.Drawing.Color.Transparent;
            this.lbl_infoArchivos.Font = new System.Drawing.Font("Tahoma", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_infoArchivos.ForeColor = System.Drawing.Color.LightCoral;
            this.lbl_infoArchivos.Location = new System.Drawing.Point(108, 562);
            this.lbl_infoArchivos.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lbl_infoArchivos.MaximumSize = new System.Drawing.Size(880, 23);
            this.lbl_infoArchivos.MinimumSize = new System.Drawing.Size(880, 23);
            this.lbl_infoArchivos.Name = "lbl_infoArchivos";
            this.lbl_infoArchivos.Size = new System.Drawing.Size(880, 23);
            this.lbl_infoArchivos.TabIndex = 16;
            // 
            // WebBrowserSlider
            // 
            this.WebBrowserSlider.AllowNavigation = true;
            this.WebBrowserSlider.Location = new System.Drawing.Point(16, 37);
            this.WebBrowserSlider.Margin = new System.Windows.Forms.Padding(4);
            this.WebBrowserSlider.MaximumSize = new System.Drawing.Size(1092, 418);
            this.WebBrowserSlider.MinimumSize = new System.Drawing.Size(27, 25);
            this.WebBrowserSlider.Name = "WebBrowserSlider";
            this.WebBrowserSlider.ScriptErrorsSuppressed = true;
            this.WebBrowserSlider.Size = new System.Drawing.Size(1081, 418);
            this.WebBrowserSlider.TabIndex = 18;
            this.WebBrowserSlider.Navigating += new System.Windows.Forms.WebBrowserNavigatingEventHandler(this.WebBrowserSlider_Navigating);
            // 
            // lbl_nombreMuOnline
            // 
            this.lbl_nombreMuOnline.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lbl_nombreMuOnline.AutoSize = true;
            this.lbl_nombreMuOnline.BackColor = System.Drawing.Color.Black;
            this.lbl_nombreMuOnline.Font = new System.Drawing.Font("Yu Gothic", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbl_nombreMuOnline.ForeColor = System.Drawing.Color.OrangeRed;
            this.lbl_nombreMuOnline.Location = new System.Drawing.Point(0, 0);
            this.lbl_nombreMuOnline.Margin = new System.Windows.Forms.Padding(0);
            this.lbl_nombreMuOnline.MaximumSize = new System.Drawing.Size(1365, 37);
            this.lbl_nombreMuOnline.MinimumSize = new System.Drawing.Size(1100, 37);
            this.lbl_nombreMuOnline.Name = "lbl_nombreMuOnline";
            this.lbl_nombreMuOnline.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.lbl_nombreMuOnline.Size = new System.Drawing.Size(1100, 37);
            this.lbl_nombreMuOnline.TabIndex = 0;
            this.lbl_nombreMuOnline.Text = "LC Mu Online Launcher";
            this.lbl_nombreMuOnline.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lbl_nombreMuOnline.MouseDown += new System.Windows.Forms.MouseEventHandler(this.lbl_nombreMuOnline_MouseDown);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.BackgroundImage = global::Launcher.Properties.Resources.banner1;
            this.ClientSize = new System.Drawing.Size(1113, 608);
            this.Controls.Add(this.WebBrowserSlider);
            this.Controls.Add(this.btn_configs);
            this.Controls.Add(this.lbl_progresoTotal);
            this.Controls.Add(this.lbl_progresoArchivo);
            this.Controls.Add(this.lbl_mensajes);
            this.Controls.Add(this.btn_minimizar);
            this.Controls.Add(this.btn_cerrar);
            this.Controls.Add(this.btn_jugar);
            this.Controls.Add(this.panel_progressbar2);
            this.Controls.Add(this.panel_progressbar1);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.lbl_nombreMuOnline);
            this.Controls.Add(this.lbl_infoArchivos);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Launcher";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Button btn_cerrar;
        private System.Windows.Forms.Button btn_minimizar;
        private System.Windows.Forms.Timer tm_test;
        public System.Windows.Forms.Panel panel_progressbar1;
        public System.Windows.Forms.Panel panel_progressbar2;
        public System.Windows.Forms.Label lbl_progresoArchivo;
        public System.Windows.Forms.Label lbl_mensajes;
        public System.Windows.Forms.Label lbl_infoArchivos;
        public System.Windows.Forms.Button btn_jugar;
        public System.Windows.Forms.Label lbl_progresoTotal;
        private System.Windows.Forms.WebBrowser WebBrowserSlider;
        public System.Windows.Forms.Label label2;
        public System.Windows.Forms.Label label3;
        public System.Windows.Forms.Button btn_configs;
        private System.Windows.Forms.Label lbl_nombreMuOnline;
    }
}

