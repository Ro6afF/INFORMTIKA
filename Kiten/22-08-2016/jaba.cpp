#include <iostream>
#include <vector>

#define MOD 1000000007

int n, k, a, b;
std::vector<bool> zab;
std::vector<uint64_t> maxx;

int main()
{
    std::cin >> n >> k;
    zab.resize(n + 1);
    maxx.resize(n + 1);
    for (int i = 0; i < k; i++)
    {
        int x;
        std::cin >> x;
        zab[x] = true;
    }
    maxx[0] = 1;
    std::cin >> a >> b;
    if (!zab[a])
        maxx[a] = 1;

    for (int i = a + 1; i <= n; i++)
    {
        if (!zab[i])
        {
            for (int j = a; j <= b && i - j >= 0; j++)
            {
                maxx[i] += maxx[i - j];
                maxx[i] %= MOD;
            }
        }
    }
    std::cout << maxx[n] % MOD << " ";

    return 0;
}
