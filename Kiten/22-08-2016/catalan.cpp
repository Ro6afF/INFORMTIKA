#include <iostream>

int n;

uint64_t mas[31][31];
bool mass[31][31];

uint64_t brum(int ot, int zt)
{
    if (mass[ot][zt])
    {
        return mas[ot][zt];
    }

    if (ot == n && zt == n)
    {
        mass[ot][zt] = true;
        mas[ot][zt] = 1;
        return 1;
    }
    if (zt > ot)
    {
        mass[ot][zt] = true;
        mas[ot][zt] = 0;
        return 0;
    }
    uint64_t x = 0;
    if (ot + 1 <= n)
    {
        x += brum(ot + 1, zt);
    }
    if (zt + 1 <= n)
    {
        x += brum(ot, zt + 1);
    }
    mass[ot][zt] = true;
    mas[ot][zt] = x;
    return x;
}

int main()
{
    std::cin >> n;

    std::cout << brum(0, 0) << std::endl;

    return 0;
}
