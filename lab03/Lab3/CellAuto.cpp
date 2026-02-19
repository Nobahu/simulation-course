#include "Rules.h"
#include <vector>
#include <random>
#include <iostream>

using namespace Rules;

class Simulation
{
public:

  Simulation(const unsigned int size) : mapSize(size)
  {
    curr_map.resize(size, std::vector<CellCondition>(size));
    next_map.resize(size, std::vector<CellCondition>(size));

  }

  void mapCreation()
  {
    unsigned int SEED = 52;
    std::mt19937_64 gen(SEED);
    std::uniform_int_distribution<> dist(0, 10);
    for (size_t col = 0; col < mapSize; col++) {
      for (size_t row = 0; row < mapSize; row++) {
        if (dist(gen) < 4) {
          curr_map[col][row] = CellCondition::Water;
        }
        else {
          curr_map[col][row] = CellCondition::Land;
        }
      }
    }
    std::cout << "Starting map creation:" << '\n';
    for (size_t col = 0; col < mapSize; col++) {
    
      for (size_t row = 0; row < mapSize; row++) {
        std::cout << curr_map[col][row];
      }
      std::cout << '\n';
    }
    NDMapChange();
    std::cout << '\n';
    
    std::cout <<"Fully maded one:" << '\n';
    for (size_t col = 0; col < mapSize; col++) {
    
      for (size_t row = 0; row < mapSize; row++) {
        std::cout << curr_map[col][row];
      }
      std::cout << '\n';
    }
  }

  void run()
  {
    for (int col = 0; col < mapSize; col++) {
      for (int row = 0; row < mapSize; row++) {
        CellCondition type = curr_map[col][row];
        next_map[col][row] = changeCellCondition(col,row,type);
      }
    }
    curr_map = next_map;
    std::cout << "\nAfter iteration:" << '\n';
    for (size_t col = 0; col < mapSize; col++) {

      for (size_t row = 0; row < mapSize; row++) {
        std::cout << curr_map[col][row];
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  }


private:

  ///////////////////////////// ФУНКЦИИ СИМУЛЯЦИИ АВТОМАТА ///////////////////////////

  CellCondition changeCellCondition(int& col, int& row, CellCondition type)
  {
    unsigned int SEED = 52;
    static std::mt19937_64 gen(SEED);
    static std::uniform_real_distribution<> dist(0, 1);

    switch (type)
    {
    case CellCondition::Land:
    {
      if (dist(gen) <= Rules::SPAWN_PROBABILITY) {
        return CellCondition::Tree;
      }
      return CellCondition::Land;
    }

    case CellCondition::Tree:
    {
      int fire_counter = countNeighbors(col, row, CellCondition::Fire);

      if (fire_counter > 0 || (dist(gen) <= Rules::FIRE_PROBABILITY)) {
        return CellCondition::Fire;
      }
      return CellCondition::Tree;
    }

    case CellCondition::Fire:
    {

      int tree_counter = countNeighbors(col, row, CellCondition::Tree);
      if (tree_counter > 0) {
        return CellCondition::Fire;
      }
      return CellCondition::Land;
    }

    default:
      return CellCondition::Water;
    }
  }

  ////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////// ФУНКЦИИ ГЕНЕРАЦИИ КАРТЫ //////////////////////////////

  //Лучше не надо))
  int countNeighbors(int& x, int& y, CellCondition type)
  {
    int counter = 0;

    if (x > 0) {
      if (y > 0) {
        if (curr_map[x - 1][y - 1] == type) counter++;
      }

      if (curr_map[x - 1][y] == type) counter++;

      if (y < mapSize - 1) {
        if (curr_map[x - 1][y + 1] == type) counter++;
      }
    }

    if (y > 0) {
      if (curr_map[x][y - 1] == type) counter++;
    }

    if (y < mapSize - 1) {
      if (curr_map[x][y + 1] == type) counter++;
    }

    if (x < mapSize - 1) {
      if (y > 0) {
        if (curr_map[x + 1][y - 1] == type) counter++;
      }

      if (curr_map[x + 1][y] == type) counter++;

      if (y < mapSize - 1) {
        if (curr_map[x + 1][y + 1] == type) counter++;
      }
    }
    return counter;
  }

  // Функция для генерации карты по правилам дня и ночи
  void NDMapChange()
  {
    for (int col = 0; col < mapSize; col++) {
      for (int row = 0; row < mapSize; row++) {
        int land_counter = countNeighbors(col,row,CellCondition::Land);

        if (curr_map[col][row] == CellCondition::Water &&
          (land_counter == 3 || land_counter == 6 || land_counter == 7 || land_counter == 8)) {
          next_map[col][row] = CellCondition::Land;
        }
        else if (curr_map[col][row] == CellCondition::Land &&
          !(land_counter == 3 || land_counter == 4 ||
            land_counter == 6 || land_counter == 7 || land_counter == 8)) {
          next_map[col][row] = CellCondition::Water;
        }
      }
    }
    std::swap(curr_map, next_map);
  }

  ////////////////////////////////////////////////////////////////////////////////////

  void oneIteration()
  {
    next_map = curr_map;

  }

  unsigned int mapSize;
  std::vector<std::vector<CellCondition>> curr_map;
  std::vector<std::vector<CellCondition>> next_map;

};

int main()
{
  Simulation sim(10);
  sim.mapCreation();

  for (size_t i = 0; i < 100; i++) {
    sim.run();
  }
}

