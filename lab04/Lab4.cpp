#include <vector>
#include <random>
#include <iostream>
#include <cmath>

class LCG
{
public:

  LCG(long long m = std::pow(2, 31) - 1, long long a = 48271, long long c = 0, long long seed = 52) : _modulus(m), _a(a), _c(c), _seed(seed) 
  {
    nums.resize(size + 1); 
  }

  void generate()
  {
    long long current = _seed;

    nums[0] = static_cast<double>(current) / _modulus;

    for (size_t i = 1; i < size + 1; i++) {
      // Генерируем следующее целое число
      current = (current * _a + _c) % _modulus;
      nums[i] = static_cast<double>(current) / _modulus;
    }
    nums.pop_back();
  }

  void calculateStatistics()
  {
    // Сначала вычисляем среднее
    double sum = 0;
    for (double val : nums) {
      sum += val;
    }
    double mean = sum / size;

    // Вычисляем дисперсию
    double sumSquaredDiff = 0;
    for (double val : nums) {
      double diff = val - mean;
      sumSquaredDiff += diff * diff;  // квадрат отклонения
    }

    double variance = sumSquaredDiff / size;
    double theor_variance = 1.0 / 12.0;

    std::cout << "  Среднее: " << mean << " (теор: 0.5)\n";
    std::cout << "  Дисперсия: " << variance << " (теор: 1/12)\n";

  }

  void showNums()
  {
    for (auto& el : nums) {
      std::cout << el << '\n';
    }
    std::cout << '\n';
  }

private:

  int size = 1000000;
  std::vector<double> nums;
  long long _seed;
  long long _modulus;
  long long _a;
  long long _c;
};

class MtGenerator
{
public:

  MtGenerator()
  {
    nums.resize(size);
  }

  void generate()
  {
    std::mt19937_64 gen(seed);
    std::uniform_real_distribution<>distr(0, 1);

    for (size_t i = 0; i < size; i++) {
      nums[i] = distr(gen);
    }
  }

  void calculateStatistics()
  {
    // Сначала вычисляем среднее
    double sum = 0;
    for (double val : nums) {
      sum += val;
    }
    double mean = sum / size;

    // Вычисляем дисперсию
    double sumSquaredDiff = 0;
    for (double val : nums) {
      double diff = val - mean;
      sumSquaredDiff += diff * diff;
    }

    double variance_population = sumSquaredDiff / size;

    double theor_variance = 1.0 / 12.0;

    std::cout << "  Среднее: " << mean << " (теор: 0.5)\n";
    std::cout << "  Дисперсия: " << variance_population << " (теор: 1/12)\n";


  }

  void showNums()
  {
    for (auto& el : nums) {
      std::cout << el << '\n';
    }
  }

private:
  int size = 1000000;
  long long seed = 52;
  std::vector<double> nums;
};

int main()
{
  setlocale(LC_ALL, "RU");

  std::cout << "LCG stats:" << '\n';
  LCG lcg_nums;
  lcg_nums.generate();
  lcg_nums.calculateStatistics();
  std::cout << '\n';

  std::cout << "Mt19937_64 stats:" << '\n';
  MtGenerator mt_nums;
  mt_nums.generate();
  mt_nums.calculateStatistics();
}