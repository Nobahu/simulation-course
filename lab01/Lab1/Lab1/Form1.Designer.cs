namespace Lab1
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            StartButton = new Button();
            HeightLabel = new Label();
            AngleLabel = new Label();
            SpeedLabel = new Label();
            HeightTextBox = new TextBox();
            AngleTextBox = new TextBox();
            SpeedTextBox = new TextBox();
            backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            timer1 = new System.Windows.Forms.Timer(components);
            WeightLabel = new Label();
            SizeLabel = new Label();
            WeightTextBox = new TextBox();
            SizeTextBox = new TextBox();
            DtLabel = new Label();
            DtTextBox = new TextBox();
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            ((System.ComponentModel.ISupportInitialize)chart1).BeginInit();
            SuspendLayout();
            // 
            // StartButton
            // 
            StartButton.Location = new Point(770, 50);
            StartButton.Name = "StartButton";
            StartButton.Size = new Size(75, 23);
            StartButton.TabIndex = 0;
            StartButton.Text = "Запуск";
            StartButton.UseVisualStyleBackColor = true;
            // 
            // HeightLabel
            // 
            HeightLabel.AutoSize = true;
            HeightLabel.Location = new Point(36, 31);
            HeightLabel.Name = "HeightLabel";
            HeightLabel.Size = new Size(129, 15);
            HeightLabel.TabIndex = 1;
            HeightLabel.Text = "Начальная высота (м)";
            // 
            // AngleLabel
            // 
            AngleLabel.AutoSize = true;
            AngleLabel.Location = new Point(36, 73);
            AngleLabel.Name = "AngleLabel";
            AngleLabel.Size = new Size(110, 15);
            AngleLabel.TabIndex = 2;
            AngleLabel.Text = "Угол броска (град)";
            // 
            // SpeedLabel
            // 
            SpeedLabel.AutoSize = true;
            SpeedLabel.Location = new Point(36, 114);
            SpeedLabel.Name = "SpeedLabel";
            SpeedLabel.Size = new Size(151, 15);
            SpeedLabel.TabIndex = 3;
            SpeedLabel.Text = "Начальная скорость (м/с)";
            // 
            // HeightTextBox
            // 
            HeightTextBox.Location = new Point(189, 28);
            HeightTextBox.Name = "HeightTextBox";
            HeightTextBox.Size = new Size(100, 23);
            HeightTextBox.TabIndex = 4;
            // 
            // AngleTextBox
            // 
            AngleTextBox.Location = new Point(189, 70);
            AngleTextBox.Name = "AngleTextBox";
            AngleTextBox.Size = new Size(100, 23);
            AngleTextBox.TabIndex = 5;
            // 
            // SpeedTextBox
            // 
            SpeedTextBox.Location = new Point(189, 111);
            SpeedTextBox.Name = "SpeedTextBox";
            SpeedTextBox.Size = new Size(100, 23);
            SpeedTextBox.TabIndex = 6;
            // 
            // chart1
            // 
            chartArea1.Name = "ChartArea1";
            chart1.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            chart1.Legends.Add(legend1);
            chart1.Location = new Point(1, 151);
            chart1.Name = "chart1";
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series1.Legend = "Legend1";
            series1.Name = "Series1";
            chart1.Series.Add(series1);
            chart1.Size = new Size(1060, 490);
            chart1.TabIndex = 7;
            chart1.Text = "chart1";
            // 
            // WeightLabel
            // 
            WeightLabel.AutoSize = true;
            WeightLabel.Location = new Point(346, 31);
            WeightLabel.Name = "WeightLabel";
            WeightLabel.Size = new Size(91, 15);
            WeightLabel.TabIndex = 8;
            WeightLabel.Text = "Масса тела (кг)";
            // 
            // SizeLabel
            // 
            SizeLabel.AutoSize = true;
            SizeLabel.Location = new Point(346, 73);
            SizeLabel.Name = "SizeLabel";
            SizeLabel.Size = new Size(141, 15);
            SizeLabel.TabIndex = 9;
            SizeLabel.Text = "Площадь сечения (м^2)";
            // 
            // WeightTextBox
            // 
            WeightTextBox.Location = new Point(521, 28);
            WeightTextBox.Name = "WeightTextBox";
            WeightTextBox.Size = new Size(100, 23);
            WeightTextBox.TabIndex = 10;
            // 
            // SizeTextBox
            // 
            SizeTextBox.Location = new Point(521, 70);
            SizeTextBox.Name = "SizeTextBox";
            SizeTextBox.Size = new Size(100, 23);
            SizeTextBox.TabIndex = 11;
            // 
            // DtLabel
            // 
            DtLabel.AutoSize = true;
            DtLabel.Location = new Point(346, 114);
            DtLabel.Name = "DtLabel";
            DtLabel.Size = new Size(154, 15);
            DtLabel.TabIndex = 12;
            DtLabel.Text = "Шаг моделирования (dt, c)";
            // 
            // DtTextBox
            // 
            DtTextBox.Location = new Point(521, 111);
            DtTextBox.Name = "DtTextBox";
            DtTextBox.Size = new Size(100, 23);
            DtTextBox.TabIndex = 13;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(111, 644);
            label1.Name = "label1";
            label1.Size = new Size(0, 15);
            label1.TabIndex = 17;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(288, 644);
            label2.Name = "label2";
            label2.Size = new Size(0, 15);
            label2.TabIndex = 18;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(500, 644);
            label3.Name = "label3";
            label3.Size = new Size(0, 15);
            label3.TabIndex = 19;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1061, 668);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(DtTextBox);
            Controls.Add(DtLabel);
            Controls.Add(SizeTextBox);
            Controls.Add(WeightTextBox);
            Controls.Add(SizeLabel);
            Controls.Add(WeightLabel);
            Controls.Add(chart1);
            Controls.Add(SpeedTextBox);
            Controls.Add(AngleTextBox);
            Controls.Add(HeightTextBox);
            Controls.Add(SpeedLabel);
            Controls.Add(AngleLabel);
            Controls.Add(HeightLabel);
            Controls.Add(StartButton);
            Name = "Form1";
            Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)chart1).EndInit();
            ResumeLayout(false);
            PerformLayout();

        }

        #endregion

        private Button StartButton;
        private Label HeightLabel;
        private Label AngleLabel;
        private Label SpeedLabel;
        private TextBox HeightTextBox;
        private TextBox AngleTextBox;
        private TextBox SpeedTextBox;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.Timer timer1;
        private Label WeightLabel;
        private Label SizeLabel;
        private TextBox WeightTextBox;
        private TextBox SizeTextBox;
        private Label DtLabel;
        private TextBox DtTextBox;
        private Label label1;
        private Label label2;
        private Label label3;
    }
}
