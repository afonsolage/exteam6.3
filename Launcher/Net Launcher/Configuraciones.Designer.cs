namespace Net_Launcher
{
    partial class Configuraciones
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Configuraciones));
            this.btn_guardar = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.btn_cancelar = new System.Windows.Forms.Button();
            this.txt_idUsuario = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.cmb_resolucion = new System.Windows.Forms.ComboBox();
            this.cmb_maxColor = new System.Windows.Forms.ComboBox();
            this.chk_modoVentana = new System.Windows.Forms.CheckBox();
            this.chk_sonido = new System.Windows.Forms.CheckBox();
            this.chk_musica = new System.Windows.Forms.CheckBox();
            this.cmb_idioma = new System.Windows.Forms.ComboBox();
            this.chk_autoStart = new System.Windows.Forms.CheckBox();
            this.ptb_moverForm = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.ptb_moverForm)).BeginInit();
            this.SuspendLayout();
            // 
            // btn_guardar
            // 
            this.btn_guardar.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(246)))), ((int)(((byte)(46)))), ((int)(((byte)(46)))));
            this.btn_guardar.FlatAppearance.BorderSize = 0;
            this.btn_guardar.FlatAppearance.MouseDownBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(246)))), ((int)(((byte)(46)))), ((int)(((byte)(46)))));
            this.btn_guardar.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_guardar.Font = new System.Drawing.Font("Tahoma", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_guardar.ForeColor = System.Drawing.Color.White;
            this.btn_guardar.Location = new System.Drawing.Point(150, 297);
            this.btn_guardar.Name = "btn_guardar";
            this.btn_guardar.Size = new System.Drawing.Size(147, 50);
            this.btn_guardar.TabIndex = 0;
            this.btn_guardar.Text = "Salvar";
            this.btn_guardar.UseVisualStyleBackColor = false;
            this.btn_guardar.Click += new System.EventHandler(this.btn_guardar_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Font = new System.Drawing.Font("Tahoma", 12F, System.Drawing.FontStyle.Bold);
            this.label1.ForeColor = System.Drawing.Color.Black;
            this.label1.Location = new System.Drawing.Point(30, 6);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(124, 19);
            this.label1.TabIndex = 1;
            this.label1.Text = "Configurações";
            // 
            // btn_cancelar
            // 
            this.btn_cancelar.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(30)))), ((int)(((byte)(29)))), ((int)(((byte)(47)))));
            this.btn_cancelar.FlatAppearance.BorderSize = 0;
            this.btn_cancelar.FlatAppearance.MouseDownBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(30)))), ((int)(((byte)(29)))), ((int)(((byte)(47)))));
            this.btn_cancelar.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btn_cancelar.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_cancelar.ForeColor = System.Drawing.Color.White;
            this.btn_cancelar.Location = new System.Drawing.Point(3, 297);
            this.btn_cancelar.Name = "btn_cancelar";
            this.btn_cancelar.Size = new System.Drawing.Size(147, 50);
            this.btn_cancelar.TabIndex = 2;
            this.btn_cancelar.Text = "Cancelar";
            this.btn_cancelar.UseVisualStyleBackColor = false;
            this.btn_cancelar.Click += new System.EventHandler(this.btn_cancelar_Click);
            // 
            // txt_idUsuario
            // 
            this.txt_idUsuario.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(121)))), ((int)(((byte)(155)))), ((int)(((byte)(171)))));
            this.txt_idUsuario.Location = new System.Drawing.Point(150, 72);
            this.txt_idUsuario.Name = "txt_idUsuario";
            this.txt_idUsuario.Size = new System.Drawing.Size(119, 20);
            this.txt_idUsuario.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.Font = new System.Drawing.Font("Tahoma", 10F, System.Drawing.FontStyle.Bold);
            this.label2.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(246)))), ((int)(((byte)(46)))), ((int)(((byte)(46)))));
            this.label2.Location = new System.Drawing.Point(31, 48);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(113, 17);
            this.label2.TabIndex = 4;
            this.label2.Text = "Usuário Padrão";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BackColor = System.Drawing.Color.Transparent;
            this.label3.Font = new System.Drawing.Font("Tahoma", 10F, System.Drawing.FontStyle.Bold);
            this.label3.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(246)))), ((int)(((byte)(46)))), ((int)(((byte)(46)))));
            this.label3.Location = new System.Drawing.Point(31, 102);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(78, 17);
            this.label3.TabIndex = 5;
            this.label3.Text = "Resolução";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.BackColor = System.Drawing.Color.Transparent;
            this.label4.Font = new System.Drawing.Font("Tahoma", 10F, System.Drawing.FontStyle.Bold);
            this.label4.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(246)))), ((int)(((byte)(46)))), ((int)(((byte)(46)))));
            this.label4.Location = new System.Drawing.Point(31, 156);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(59, 17);
            this.label4.TabIndex = 6;
            this.label4.Text = "Opções";
            // 
            // cmb_resolucion
            // 
            this.cmb_resolucion.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(121)))), ((int)(((byte)(155)))), ((int)(((byte)(171)))));
            this.cmb_resolucion.FormattingEnabled = true;
            this.cmb_resolucion.Items.AddRange(new object[] {
            "- 600 x 480",
            "- 800 x 600",
            "- 1024 x 768",
            "- 1280 x 1024",
            "- 1366 x 768",
            "- 1600 x 1280"});
            this.cmb_resolucion.Location = new System.Drawing.Point(150, 126);
            this.cmb_resolucion.Name = "cmb_resolucion";
            this.cmb_resolucion.Size = new System.Drawing.Size(119, 21);
            this.cmb_resolucion.TabIndex = 7;
            this.cmb_resolucion.Text = "- Resolução";
            // 
            // cmb_maxColor
            // 
            this.cmb_maxColor.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(121)))), ((int)(((byte)(155)))), ((int)(((byte)(171)))));
            this.cmb_maxColor.FormattingEnabled = true;
            this.cmb_maxColor.Items.AddRange(new object[] {
            "- Max Color (16 bit)",
            "- Max Color (32 bit)"});
            this.cmb_maxColor.Location = new System.Drawing.Point(150, 180);
            this.cmb_maxColor.Name = "cmb_maxColor";
            this.cmb_maxColor.Size = new System.Drawing.Size(119, 21);
            this.cmb_maxColor.TabIndex = 8;
            this.cmb_maxColor.Text = "- Max Color";
            // 
            // chk_modoVentana
            // 
            this.chk_modoVentana.AutoSize = true;
            this.chk_modoVentana.BackColor = System.Drawing.Color.Transparent;
            this.chk_modoVentana.FlatAppearance.CheckedBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(121)))), ((int)(((byte)(155)))), ((int)(((byte)(171)))));
            this.chk_modoVentana.ForeColor = System.Drawing.Color.Black;
            this.chk_modoVentana.Location = new System.Drawing.Point(34, 127);
            this.chk_modoVentana.Name = "chk_modoVentana";
            this.chk_modoVentana.Size = new System.Drawing.Size(87, 17);
            this.chk_modoVentana.TabIndex = 9;
            this.chk_modoVentana.Text = "Modo Janela";
            this.chk_modoVentana.UseVisualStyleBackColor = false;
            // 
            // chk_sonido
            // 
            this.chk_sonido.AutoSize = true;
            this.chk_sonido.BackColor = System.Drawing.Color.Transparent;
            this.chk_sonido.FlatAppearance.CheckedBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(121)))), ((int)(((byte)(155)))), ((int)(((byte)(171)))));
            this.chk_sonido.ForeColor = System.Drawing.Color.Black;
            this.chk_sonido.Location = new System.Drawing.Point(34, 212);
            this.chk_sonido.Name = "chk_sonido";
            this.chk_sonido.Size = new System.Drawing.Size(90, 17);
            this.chk_sonido.TabIndex = 12;
            this.chk_sonido.Text = "Efeito Sonoro";
            this.chk_sonido.UseVisualStyleBackColor = false;
            // 
            // chk_musica
            // 
            this.chk_musica.AutoSize = true;
            this.chk_musica.BackColor = System.Drawing.Color.Transparent;
            this.chk_musica.FlatAppearance.CheckedBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(121)))), ((int)(((byte)(155)))), ((int)(((byte)(171)))));
            this.chk_musica.ForeColor = System.Drawing.Color.Black;
            this.chk_musica.Location = new System.Drawing.Point(150, 212);
            this.chk_musica.Name = "chk_musica";
            this.chk_musica.Size = new System.Drawing.Size(60, 17);
            this.chk_musica.TabIndex = 13;
            this.chk_musica.Text = "Música";
            this.chk_musica.UseVisualStyleBackColor = false;
            // 
            // cmb_idioma
            // 
            this.cmb_idioma.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(121)))), ((int)(((byte)(155)))), ((int)(((byte)(171)))));
            this.cmb_idioma.FormattingEnabled = true;
            this.cmb_idioma.Items.AddRange(new object[] {
            "- English",
            "- Portuguese",
            "- Spanish"});
            this.cmb_idioma.Location = new System.Drawing.Point(150, 241);
            this.cmb_idioma.Name = "cmb_idioma";
            this.cmb_idioma.Size = new System.Drawing.Size(119, 21);
            this.cmb_idioma.TabIndex = 14;
            this.cmb_idioma.Text = "- Idioma";
            // 
            // chk_autoStart
            // 
            this.chk_autoStart.AutoSize = true;
            this.chk_autoStart.BackColor = System.Drawing.Color.Transparent;
            this.chk_autoStart.FlatAppearance.CheckedBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(121)))), ((int)(((byte)(155)))), ((int)(((byte)(171)))));
            this.chk_autoStart.ForeColor = System.Drawing.Color.Black;
            this.chk_autoStart.Location = new System.Drawing.Point(34, 242);
            this.chk_autoStart.Name = "chk_autoStart";
            this.chk_autoStart.Size = new System.Drawing.Size(91, 17);
            this.chk_autoStart.TabIndex = 15;
            this.chk_autoStart.Text = "Inicar ao Abrir";
            this.chk_autoStart.UseVisualStyleBackColor = false;
            // 
            // ptb_moverForm
            // 
            this.ptb_moverForm.BackColor = System.Drawing.Color.Transparent;
            this.ptb_moverForm.Location = new System.Drawing.Point(0, 0);
            this.ptb_moverForm.Name = "ptb_moverForm";
            this.ptb_moverForm.Size = new System.Drawing.Size(300, 30);
            this.ptb_moverForm.TabIndex = 16;
            this.ptb_moverForm.TabStop = false;
            this.ptb_moverForm.MouseDown += new System.Windows.Forms.MouseEventHandler(this.ptb_moverForm_MouseDown);
            // 
            // Configuraciones
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Silver;
            this.ClientSize = new System.Drawing.Size(300, 350);
            this.Controls.Add(this.chk_autoStart);
            this.Controls.Add(this.cmb_idioma);
            this.Controls.Add(this.chk_musica);
            this.Controls.Add(this.chk_sonido);
            this.Controls.Add(this.chk_modoVentana);
            this.Controls.Add(this.cmb_maxColor);
            this.Controls.Add(this.cmb_resolucion);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txt_idUsuario);
            this.Controls.Add(this.btn_cancelar);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btn_guardar);
            this.Controls.Add(this.ptb_moverForm);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Configuraciones";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Configuraciones Launcher";
            ((System.ComponentModel.ISupportInitialize)(this.ptb_moverForm)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txt_idUsuario;
        private System.Windows.Forms.ComboBox cmb_maxColor;
        private System.Windows.Forms.PictureBox ptb_moverForm;
        public System.Windows.Forms.Button btn_guardar;
        public System.Windows.Forms.Label label1;
        public System.Windows.Forms.Button btn_cancelar;
        public System.Windows.Forms.Label label2;
        public System.Windows.Forms.Label label3;
        public System.Windows.Forms.Label label4;
        public System.Windows.Forms.ComboBox cmb_resolucion;
        public System.Windows.Forms.CheckBox chk_modoVentana;
        public System.Windows.Forms.CheckBox chk_sonido;
        public System.Windows.Forms.CheckBox chk_musica;
        public System.Windows.Forms.ComboBox cmb_idioma;
        public System.Windows.Forms.CheckBox chk_autoStart;
    }
}