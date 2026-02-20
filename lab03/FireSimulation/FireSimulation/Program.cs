using System;
using System.Drawing;
using System.Windows.Forms;


namespace FireSimulation
{
    public class SimulationForm : Form
    {
        private Simulation sim;
        private System.Windows.Forms.Timer timer;
        private Panel drawPanel;
        private int iteration = 0;
        private NumericUpDown nudSize, nudTemp, nudHumid, nudSpawnProb, nudFireProb, nudIterFreq;
        private Button btnCreate, btnStart;

        public SimulationForm()
        {
            this.Text = "Лабораторная работа 3";
            this.Size = new Size(1280, 720);
            this.StartPosition = FormStartPosition.CenterScreen;

            CreateControls();
        }

        private void CreateControls()
        {
            // Панель управления
            var panel = new Panel { Dock = DockStyle.Top, Height = 120, BackColor = Color.LightGray }; // Высоту увеличил до 120

            // Размер карты
            var lblSize = new Label { Text = "Размер:", Location = new Point(10, 15), AutoSize = true };
            nudSize = new NumericUpDown { Location = new Point(70, 13), Width = 50, Minimum = 5, Maximum = 500, Value = 10 };

            // Температура
            var lblTemp = new Label { Text = "Температура:", Location = new Point(140, 15), AutoSize = true };
            nudTemp = new NumericUpDown { Location = new Point(220, 13), Width = 50, Minimum = -30, Maximum = 50, Value = 20 };

            // Влажность
            var lblHumid = new Label { Text = "Влажность:", Location = new Point(290, 15), AutoSize = true };
            nudHumid = new NumericUpDown { Location = new Point(360, 13), Width = 50, Minimum = 0, Maximum = 100, Value = 30 };

            // ВЕРОЯТНОСТЬ РОЖДЕНИЯ ДЕРЕВА
            var lblSpawnProb = new Label { Text = "Рождение дерева:", Location = new Point(10, 45), AutoSize = true };
            nudSpawnProb = new NumericUpDown
            {
                Location = new Point(120, 43),
                Width = 60,
                Minimum = 0,
                Maximum = 1,
                Value = 0.1M,
                DecimalPlaces = 2,
                Increment = 0.01M
            };

            // ВЕРОЯТНОСТЬ ПОЯВЛЕНИЯ ОГНЯ (МОЛНИИ)
            var lblFireProb = new Label { Text = "Появление огня:", Location = new Point(200, 45), AutoSize = true };
            nudFireProb = new NumericUpDown
            {
                Location = new Point(310, 43),
                Width = 60,
                Minimum = 0,
                Maximum = 1,
                Value = 0.1M,
                DecimalPlaces = 2,
                Increment = 0.01M
            };

            // Кнопки
            btnCreate = new Button { Text = "Создать карту", Location = new Point(430, 10), Width = 100 };
            btnCreate.Click += BtnCreate_Click;

            btnStart = new Button { Text = "Старт", Location = new Point(540, 10), Width = 80, Enabled = false };
            btnStart.Click += BtnStart_Click;

            var lblIterFreq = new Label { Text = "Частота обновления кадра (мс):", Location = new Point(10, 85), AutoSize = true };
            nudIterFreq = new NumericUpDown
            {
                Location = new Point(210, 83),
                Width = 60,
                Minimum = 0,
                Maximum = 3000,
                Value = 1000,
                DecimalPlaces = 2,
                Increment = 10
            };

            // Добавляем все элементы на панель
            panel.Controls.AddRange(new Control[] {
                lblSize, nudSize,
                lblTemp, nudTemp,
                lblHumid, nudHumid,
                lblSpawnProb, nudSpawnProb,
                lblFireProb, nudFireProb,
                lblIterFreq, nudIterFreq,
                btnCreate, btnStart
            });

            // Панель для рисования
            drawPanel = new Panel
            {
                Dock = DockStyle.Fill,
                BackColor = Color.White,
                BorderStyle = BorderStyle.FixedSingle
            };
            drawPanel.Paint += DrawPanel_Paint;

            this.Controls.Add(drawPanel);
            this.Controls.Add(panel);

            // Таймер
            timer = new System.Windows.Forms.Timer();
            timer.Interval = (int)nudIterFreq.Value;
            timer.Tick += Timer_Tick;
        }

        private void BtnCreate_Click(object sender, EventArgs e)
        {
            int size = (int)nudSize.Value;
            int temp = (int)nudTemp.Value;
            int humid = (int)nudHumid.Value;
            double spawn_p = (double)nudSpawnProb.Value;
            double fire_p = (double) nudFireProb.Value;

            sim = new Simulation((uint)size, (uint)Math.Max(0, temp), (uint)humid,spawn_p,fire_p);
            sim.MapCreation();

            btnStart.Enabled = true;
            iteration = 0;
            drawPanel.Invalidate();
        }

        private void BtnStart_Click(object sender, EventArgs e)
        {
            timer.Interval = (int)nudIterFreq.Value;
            timer.Enabled = !timer.Enabled;
            btnStart.Text = timer.Enabled ? "Стоп" : "Старт";
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            if (sim != null)
            {
                sim.Run();
                iteration++;
                this.Text = $"Симуляция огня - Итерация {iteration}";
                drawPanel.Invalidate();
            }
        }

        private void DrawPanel_Paint(object sender, PaintEventArgs e)
        {
            if (sim == null) return;

            var map = sim.GetCurrentMap();
            int size = (int)sim.GetMapSize();  // количество клеток (например, 10)

            // Размер одной клетки = 700px / количество клеток
            float cellSize = 800f / size;

            // Убедимся, что клетки целые
            if (cellSize < 1) cellSize = 1;

            for (int col = 0; col < size; col++)
            {
                for (int row = 0; row < size; row++)
                {
                    Color color = GetCellColor(map[col][row]);

                    e.Graphics.FillRectangle(new SolidBrush(color),
                        row * cellSize, col * cellSize, cellSize - 1, cellSize - 1);
                }
            }
        }

        private Color GetCellColor(CellCondition cell)
        {
            switch (cell)
            {
                case CellCondition.Land: return Color.SandyBrown;
                case CellCondition.Tree: return Color.Green;
                case CellCondition.Fire: return Color.OrangeRed;
                case CellCondition.Water: return Color.Blue;
                default: return Color.Black;
            }
        }

        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new SimulationForm());
        }
    }
}