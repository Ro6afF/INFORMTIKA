#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

std::vector<bool> a;

int main()
{
    srand(time(NULL));
    int n, p, q;
    std::cin >> n >> q >> p;
    a.resize(n);
    a[0] = 1;
    for (int i = 0; i < 10000; i++)
    {
        auto a2 = a;
        int p1 = 1, q1 = 0;
        for (int j = 0; j < n; j++)
        {
            if (a[j])
            {
                p1 *= j + 1;
            }
            else
            {
                q1 += j + 1;
            }
        }
        int o = abs(q1 - q) + abs(p1 - p);
        for (int j = 0; j < 100; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (rand() % 100 == 0)
                    a[k] = !a[k];
            }
            int p2 = 1, q2 = 0;
            for (int x = 0; x < n; x++)
            {
                if (a[x])
                {
                    p2 *= x + 1;
                }
                else
                {
                    q2 += x + 1;
                }
            }
            if (abs(q2 - q) + abs(p2 - p) < o)
            {
                a2 = a;
                o = abs(q2 - q) + abs(p2 - p);
                if (o == 0)
                {
                    goto Go;
                }
            }
        }
        a = a2;
    }
Go:
    std::cout << "( ";
    for (int l = 0; l < n; l++)
    {
        if (!a[l])
        {
            std::cout << l + 1 << ", ";
        }
    }
    std::cout << "\b\b ) ( ";
    for (int l = 0; l < n; l++)
    {
        if (a[l])
        {
            std::cout << l + 1 << ", ";
        }
    }
    std::cout << "\b\b )" << std::endl;
    return 0;
}
