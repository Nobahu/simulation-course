using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FireSimulation
{
    public class Simulation
    {
        private uint temperature;
        private uint humidity;
        private uint mapSize;
        private double SPAWN_PROBABILITY;    // Вероятность появления дерева
        private double FIRE_PROBABILITY;    // Базовая вероятность возгорания
        private CellCondition[][] curr_map;
        private CellCondition[][] next_map;

        // Генератор случайных чисел
        private Random random = new Random(52);

        public Simulation(uint size, uint temp, uint humid, double spawn_p, double fire_p)
        {
            mapSize = size;
            temperature = temp;
            humidity = humid;
            SPAWN_PROBABILITY = spawn_p;
            FIRE_PROBABILITY = fire_p;

            curr_map = new CellCondition[size][];
            next_map = new CellCondition[size][];

            for (int i = 0; i < size; i++)
            {
                curr_map[i] = new CellCondition[size];
                next_map[i] = new CellCondition[size];
            }
        }

        public void MapCreation()
        {
            random = new Random();
            // Начальная случайная генерация
            for (int col = 0; col < mapSize; col++)
            {
                for (int row = 0; row < mapSize; row++)
                {
                    int random_value = random.Next(0, 100);
                    if (random_value <= 40)
                    {
                        curr_map[col][row] = CellCondition.Water;
                    }
                    else
                    {
                        curr_map[col][row] = CellCondition.Land;
                    }
                }
            }

            Console.WriteLine("Starting map creation:");
            PrintMap(curr_map);

            int generations;

            if (mapSize <= 30)
            {
                generations = 20;
            }
            else
            {
                generations = 100;
            }

            for(int i = 0;i < generations;i++)
            {
                NDMapChange();
            }

            for (int col = 0; col < mapSize; col++)
            {
                for (int row = 0; row < mapSize; row++)
                {
                    int random_value = random.Next(0, 100);
                    if(random_value <= 10 && curr_map[col][row] == CellCondition.Land)
                    {
                        curr_map[col][row] = CellCondition.Tree;
                    }
                }
            }

            Console.WriteLine("\nFully maded one:");
            PrintMap(curr_map);
        }

        public void Run()
        {
            for (int col = 0; col < mapSize; col++)
            {
                for (int row = 0; row < mapSize; row++)
                {
                    CellCondition type = curr_map[col][row];
                    next_map[col][row] = ChangeCellCondition(col, row, type);
                }
            }

            // Меняем карты местами
            var temp = curr_map;
            curr_map = next_map;
            next_map = temp;

            Console.WriteLine("\nAfter iteration:");

            PrintMap(curr_map);
        }

        private CellCondition ChangeCellCondition(int col, int row, CellCondition type)
        {
            int tree_counter = CountNeighbors(col, row, CellCondition.Tree);
            switch (type)
            {
                case CellCondition.Land:

                    if (random.NextDouble() <= SPAWN_PROBABILITY)
                    {
                        return CellCondition.Tree;
                    }
                    return CellCondition.Land;

                case CellCondition.Tree:

                    int fire_counter = CountNeighbors(col, row, CellCondition.Fire);

                    double temp_factor = Math.Max(temperature / 20.0, 0.0);
                    double humidity_factor = Math.Max(1.0 - humidity / 100.0, 0.0);

                    double fire_probability = FIRE_PROBABILITY * temp_factor * humidity_factor;
                    if (fire_probability > 1.0) fire_probability = 1.0;

                    if (fire_counter > 0 || random.NextDouble() <= fire_probability)
                    {
                        return CellCondition.Fire;
                    }
                    return CellCondition.Tree;

                case CellCondition.Fire:
                    if (tree_counter > 0)
                    {
                        return CellCondition.Fire;
                    }
                    return CellCondition.Land;

                default:
                    return CellCondition.Water;
            }
        }

        private int CountNeighbors(int x, int y, CellCondition type)
        {
            int counter = 0;

            if (x > 0)
            {
                if (y > 0 && curr_map[x - 1][y - 1] == type) counter++;
                if (curr_map[x - 1][y] == type) counter++;
                if (y < mapSize - 1 && curr_map[x - 1][y + 1] == type) counter++;
            }

            if (y > 0 && curr_map[x][y - 1] == type) counter++;
            if (y < mapSize - 1 && curr_map[x][y + 1] == type) counter++;

            if (x < mapSize - 1)
            {
                if (y > 0 && curr_map[x + 1][y - 1] == type) counter++;
                if (curr_map[x + 1][y] == type) counter++;
                if (y < mapSize - 1 && curr_map[x + 1][y + 1] == type) counter++;
            }

            return counter;
        }

        private void NDMapChange()
        {
            // Копируем текущую карту в next_map
            for (int col = 0; col < mapSize; col++)
            {
                for (int row = 0; row < mapSize; row++)
                {
                    next_map[col][row] = curr_map[col][row];
                }
            }

            for (int col = 0; col < mapSize; col++)
            {
                for (int row = 0; row < mapSize; row++)
                {
                    int land_counter = CountNeighbors(col, row, CellCondition.Land);

                    if (curr_map[col][row] == CellCondition.Water &&
                        (land_counter == 3 || land_counter == 6 ||
                         land_counter == 7 || land_counter == 8))
                    {
                        next_map[col][row] = CellCondition.Land;
                    }
                    else if (curr_map[col][row] == CellCondition.Land &&
                             !(land_counter == 3 || land_counter == 4 ||
                               land_counter == 6 || land_counter == 7 || land_counter == 8))
                    {
                        next_map[col][row] = CellCondition.Water;
                    }
                }
            }

            // Меняем карты местами
            var temp = curr_map;
            curr_map = next_map;
            next_map = temp;
        }

        private void PrintMap(CellCondition[][] map)
        {
            for (int col = 0; col < mapSize; col++)
            {
                for (int row = 0; row < mapSize; row++)
                {
                    Console.Write((int)map[col][row]);
                }
                Console.WriteLine();
            }
        }

        // Методы для доступа к данным
        public CellCondition[][] GetCurrentMap()
        {
            return curr_map;
        }

        public uint GetMapSize() => mapSize;
    }
}
