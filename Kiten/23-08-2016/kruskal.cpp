#include <iostream>
#include <queue>
#include <utility>
#include <vector>

std::vector<uint64_t> tatko;
std::priority_queue<std::pair<uint64_t, std::pair<uint64_t, uint64_t>>, std::vector<std::pair<uint64_t, std::pair<uint64_t, uint64_t>>>, std::greater<std::pair<uint64_t, std::pair<uint64_t, uint64_t>>>> q;

bool v1mnls(uint64_t a, uint64_t b)
{
    while (tatko[a] != a)
    {
        a = tatko[a];
    }
    while (tatko[b] != b)
    {
        b = tatko[b];
    }
    return a == b;
}

int fp(uint64_t a)
{
    if (a == tatko[a])
        return a;
    return tatko[a]=fp(tatko[a]);
}

void add(uint64_t a, uint64_t b)
{
    tatko[fp(a)] = fp(b);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    uint64_t n, m;
    std::cin >> n >> m;
    tatko.resize(n + 1);
    for (uint64_t i = 0; i < n; i++)
    {
        tatko[i] = i;
    }
    for (uint64_t i = 0; i < m; i++)
    {
        uint64_t a, b, c;
        std::cin >> a >> b >> c;
        q.push({c, {a, b}});
    }

    uint64_t sum = 0;

    uint64_t iter = 0;
    while (iter < n - 1)
    {
        auto sq = q.top();
        q.pop();
        if (!v1mnls(sq.second.first, sq.second.second))
        {
            sum += sq.first;
            add(sq.second.first, sq.second.second);
            iter++;
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
