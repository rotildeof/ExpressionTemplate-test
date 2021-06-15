#include "Lazy1.hh"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <valarray>
#include <vector>

int main() {
    std::vector<double> a1(100000, 1);
    std::vector<double> a2(100000, 2);
    std::vector<double> a3(100000, 3);
    std::vector<double> a4(100000);
    double count = 0;
    auto t0 = std::chrono::system_clock::now();
    for (int n = 0; n < 1000; ++n) {
        for (int i = 0; i < 100000; ++i) {
            a4[i] = a1[i] + a2[i] + a3[i];
        }
        count += a4[0];
    }
    auto t1 = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() << " [us]  total = " << count
              << std::endl;

    count = 0;
    lazy::Vect b1(100000, 1);
    lazy::Vect b2(100000, 2);
    lazy::Vect b3(100000, 3);
    lazy::Vect b4(100000);
    t0 = std::chrono::system_clock::now();
    for (int i = 0; i < 1000; ++i) {
        b4 = b1 + (b2 + b3);
        count += b4[0];
    }
    t1 = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() << " [us]  total = " << count
              << std::endl;

    count = 0;
    std::valarray<double> c1(1, 100000);
    std::valarray<double> c2(2, 100000);
    std::valarray<double> c3(3, 100000);
    t0 = std::chrono::system_clock::now();
    for (int i = 0; i < 1000; ++i) {
        auto c4 = c1 + c2 + c3;
        count += c4[i];
    }
    t1 = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() << " [us]  total = " << count
              << std::endl;
}