#include <iostream>
#include <vector>

std::vector<uint64_t> a;
std::vector<uint64_t> plok;

uint64_t n;

void update(uint64_t x, uint64_t b)
{
    while (x <= n)
    {
        a[x] += b;
        x += x & (-x);
    }
}

uint64_t get(uint64_t x)
{
    uint64_t sum = 0;
    while (x > 0)
    {
        sum += a[x];
        x -= (x & (-x));
    }
    return sum;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n;
    a.resize(n + 2);
    plok.resize(n + 2);
    for (uint64_t i = 1; i <= n; i++)
    {
        uint64_t b;
        std::cin >> b;
        plok[i] = b;
        update(i, b);
    }
    uint64_t q;
    std::cin >> q;
    for (uint64_t i = 0; i < q; i++)
    {
        char ch;
        std::cin >> ch;
        if (ch == 'u')
        {
            uint64_t b, c;
            std::cin >> b >> c;
            update(b, c - plok[b]);
            plok[b] = c;
        }
        else
        {
            uint64_t b, c;
            std::cin >> b >> c;
            std::cout << get(c) - get(b - 1) << std::endl;
        }
    }
    return 0;
}
