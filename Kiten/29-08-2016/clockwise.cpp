#include <iostream>
#include <utility>

#define x first
#define y second

int main()
{
    std::pair<int, int> t1, t2, t3;
    std::cin >> t1.x >> t1.y;
    std::cin >> t2.x >> t2.y;
    std::cin >> t3.x >> t3.y;

    double face = ((t1.x - t3.x) * (t2.y - t3.y) - (t1.y - t3.y) * (t2.x - t3.x)) / 2;

    if (face < 0)
    {
        std::cout << "Clockwise" << std::endl;
    }
    else if (face > 0)
    {
        std::cout << "Counter Clockwise" << std::endl;
    }
    else
    {
        std::cout << "One line" << std::endl;
    }

    return 0;
}
