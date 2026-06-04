#pragma once

#include <cmath>

class LCG {
public:
    static LCG& get() {
        static LCG instance;
        return instance;
    }

    void setSeed(unsigned int seed) {
        x = seed;
    }

    unsigned int next() {
        x = (a * x + c) % m;
        return static_cast<unsigned int>(x);
    }

    double nextDouble() {
        return static_cast<double>(next()) / m;
    }

    double generate(double lambda) {
        double u = nextDouble();
        u = (u < 1e-10) ? 1e-10 : u;
        return -std::log(1.0 - u) / lambda;
    }

private:
    LCG() : x(52) {}  // seed по умолчанию = 52

    /// Параметры взяты их borland c/c++
    unsigned long long x;
    static constexpr unsigned long long a = 22695477; // множитель
    static constexpr unsigned long long c = 1; // смещение
    static constexpr unsigned long long m = 1ULL << 32; // 2^32
};
