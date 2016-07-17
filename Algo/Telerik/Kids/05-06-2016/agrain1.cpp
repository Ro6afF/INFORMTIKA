#include <iostream>
#include <map>
#include <utility>

std::map<std::pair<int, int>, int> m;

int main()
{
    int n, l, d, x, a, b;
    std::cin >> n >> l >> d >> x >> a >> b;
    for (int i = 0; i <= l + 1 - d; i += d)
    {
        m[std::make_pair(i, i + d)] = 0;
    }

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i <= l + 1 - d; i += d)
        {
            if (i < x && i + d > x)
            {
                m[std::make_pair(i, i + d)]++;
            }
        }
        for (int i = 0; i <= l + 1 - d; i += d)
        {
            if (!m[std::make_pair(i, i + d)])
            {
                goto go;
            }
        }
        std::cout << j + 1 << std::endl;
        return 0;
    go:
        j++;
        j--;
        x = (x * a + b) % (l + 1);
    }
    std::cout << -1 << std::endl;
    return 0;
}
