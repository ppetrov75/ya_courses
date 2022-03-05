#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <functional>
#include <iomanip>

std::vector<int> generate_random_values(int max_value = 1, int min_value = 0, int range = 1) {

    std::vector<int> v;
    v.resize(range);

    // Seed with a real random value, if available
    std::random_device r;

    // Choose a random mean between 1 and 6
    std::default_random_engine gen(r());
    std::uniform_int_distribution<int> dist(min_value, max_value);
    auto rand = std::bind(dist, std::ref(gen));

    std::generate(v.begin(), v.end(), rand);

    return v;
}

int main() {
    // long in linux - 8 bytes
    std::vector<int> temps;
    int range = std::pow(10, 6);

    temps = generate_random_values(std::pow(10, 8), -std::pow(10, 8), range);

    // check vector
    std::cout << temps.at(0) << ' ' << temps.at(range - 1) << '\n';

    long avg_temp = std::accumulate(temps.begin(), temps.end(), long(0));
    std::cout << avg_temp << ' ' << (int) avg_temp << '\n';

    double t =  (long double)avg_temp / range;
    std::cout << std::setprecision(8) << t;
}