#include <algorithm>
#include <iostream>
#include <random>

int main()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 100);

    int *best = new int[dist(mt)];
    std::cout << best[0] << std::endl;
    delete[] best;
}
