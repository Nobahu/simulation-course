using System;
using System.Windows.Forms.DataVisualization.Charting;
using System.Drawing;

namespace Lab1
{
    public partial class Form1 : Form
    {
        private void SetupChart()
        {
            // Названия осей
            chart1.ChartAreas[0].AxisX.Title = "Расстояние, м";
            chart1.ChartAreas[0].AxisY.Title = "Высота, м";

            // Начальные границы
            chart1.ChartAreas[0].AxisX.Minimum = 0;
            chart1.ChartAreas[0].AxisY.Minimum = 0;
            chart1.ChartAreas[0].AxisX.Maximum = 50;
            chart1.ChartAreas[0].AxisY.Maximum = 30;

            // Фикс шаг сетки
            chart1.ChartAreas[0].AxisX.Interval = 10;
            chart1.ChartAreas[0].AxisY.Interval = 5;
        }

        const decimal g = 9.81M;
        const decimal c = 0.15M;
        const decimal rho = 1.29M;
        decimal dt = 0;
        decimal t, x, y, v0, cosa, sina, S, m, k, vx, vy;

        // Переменные для хранения результатов текущего полета
        decimal maxHeight = 0;
        decimal finalX = 0;
        decimal finalVx = 0;
        decimal finalVy = 0;

        // Счетчик траекторий для разных цветов
        int trajectoryCount = 0;

        private Color[] colors = new Color[]
        {
            Color.Red,
            Color.Blue,
            Color.Green,
            Color.Orange,
            Color.Purple,
            Color.Brown,
            Color.Cyan,
            Color.Magenta,
            Color.DarkRed,
            Color.DarkBlue
        };

        double currentMaxX = 50;
        double currentMaxY = 30;

        private void StartButton_Click(object sender, EventArgs e)
        {
            if (decimal.TryParse(HeightTextBox.Text, out decimal height) &&
                decimal.TryParse(SpeedTextBox.Text, out decimal speed) &&
                decimal.TryParse(AngleTextBox.Text, out decimal angle) &&
                decimal.TryParse(WeightTextBox.Text, out decimal weight) &&
                decimal.TryParse(SizeTextBox.Text, out decimal size) &&
                decimal.TryParse(DtTextBox.Text, out decimal parsedDt))
            {
                dt = parsedDt;
                if (!timer1.Enabled)
                {
                    // Новая серия для новой траектории
                    string seriesName = $"dt = {parsedDt}";

                    Series trajectorySeries = new Series(seriesName);
                    trajectorySeries.ChartType = SeriesChartType.Line;
                    trajectorySeries.BorderWidth = 2;
                    trajectorySeries.Color = colors[trajectoryCount % colors.Length];
                    trajectorySeries.MarkerSize = 0;

                    chart1.Series.Add(trajectorySeries);

                    // Сбрасываем результаты текущего полета
                    maxHeight = 0;
                    finalX = 0;
                    finalVx = 0;
                    finalVy = 0;

                    t = 0;
                    x = 0;
                    y = height;
                    v0 = speed;
                    double a = (double)angle * Math.PI / 180;
                    cosa = (decimal)Math.Cos(a);
                    sina = (decimal)Math.Sin(a);
                    S = size;
                    m = weight;
                    k = 0.5M * c * rho * S / m;
                    vx = v0 * cosa;
                    vy = v0 * sina;

                    // Добавляем первую точку в НОВУЮ траекторию
                    chart1.Series[seriesName].Points.AddXY(x, y);

                    trajectoryCount++;

                    timer1.Start();
                }
                else
                {
                    timer1.Stop();


                }
            }
            else
            {
                MessageBox.Show("Пожалуйста, введите корректные числовые значения",
                     "Ошибка ввода", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            t += dt;
            decimal v = (decimal)Math.Sqrt((double)(vx * vx + vy * vy));
            vx -= k * vx * v * dt;
            vy -= (g + k * vy * v) * dt;
            x += vx * dt;
            y += vy * dt;

            // Отслеживаем максимальную высоту
            if (y > maxHeight)
            {
                maxHeight = y;
            }

            // Проверяем и расширяем границы если надо
            if ((double)x > currentMaxX)
            {
                currentMaxX = Math.Ceiling((double)x / 10) * 10 + 10;
                chart1.ChartAreas[0].AxisX.Maximum = currentMaxX;
                chart1.Invalidate();
            }

            if ((double)y > currentMaxY)
            {
                currentMaxY = Math.Ceiling((double)y / 10) * 10 + 10;
                chart1.ChartAreas[0].AxisY.Maximum = currentMaxY;
                chart1.Invalidate();
            }

            if (y <= 0)
            {
                timer1.Stop();

                finalX = x;
                finalVx = vx;
                finalVy = vy;

                decimal finalSpeed = (decimal)Math.Sqrt((double)(finalVx * finalVx + finalVy * finalVy));
                label1.Text = $"Высота: {maxHeight:F2} м";
                label2.Text = $"Дистанция: {finalX:F2} м";
                label3.Text = $"Скорость: {finalSpeed:F2} м/с";

                return;
            }

            chart1.Series[chart1.Series.Count - 1].Points.AddXY(x, y);
        }

        // Кнопка для очистки всех траекторий
        private void ClearButton_Click(object sender, EventArgs e)
        {
            while (chart1.Series.Count > 1)
            {
                chart1.Series.RemoveAt(1);
            }

            if (chart1.Series.Count > 0)
            {
                chart1.Series[0].Points.Clear();
            }

            trajectoryCount = 0;
            currentMaxX = 50;
            currentMaxY = 30;
            chart1.ChartAreas[0].AxisX.Maximum = currentMaxX;
            chart1.ChartAreas[0].AxisY.Maximum = currentMaxY;

            // Очищаем лейблы
            label1.Text = "Высота: --";
            label2.Text = "Дистанция: --";
            label3.Text = "Скорость: --";
        }

        public Form1()
        {
            InitializeComponent();
            SetupChart();

            timer1.Interval = 1;
            timer1.Tick += timer1_Tick;
            StartButton.Click += StartButton_Click;

            Button clearButton = new Button();
            clearButton.Text = "Очистить все";
            clearButton.Location = new System.Drawing.Point(770, 110);
            clearButton.Size = new System.Drawing.Size(100, 30);
            clearButton.Click += ClearButton_Click;
            this.Controls.Add(clearButton);
        }
    }
}