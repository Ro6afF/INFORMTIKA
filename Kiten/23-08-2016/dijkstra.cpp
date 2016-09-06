#include <iostream>
#include <queue>
#include <utility>

#define INF (uint64_t) - 1

std::vector<std::vector<std::pair<uint64_t, uint64_t>>> v;
std::priority_queue<std::pair<uint64_t, uint64_t>, std::vector<std::pair<uint64_t, uint64_t>>, std::greater<std::pair<uint64_t, uint64_t>>> q;
std::vector<uint64_t> dist;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    uint64_t n, m;
    std::cin >> n >> m;

    v.resize(n + 1);
    dist.reserve(n + 1);

    for (uint64_t i = 0; i < m; i++)
    {
        uint64_t a, b, c;
        std::cin >> a >> b >> c;
        a--;
        b--;
        v[a].push_back({b, c});
    }

    for (uint64_t i = 0; i < n; i++)
    {
        dist.push_back(INF);
    }

    dist[0] = 0;
    q.push({0, 0});

    while (!q.empty())
    {
        auto sq = q.top();
        q.pop();
        if (dist[sq.second] >= sq.first)
        {
            for (auto &x : v[sq.second])
            {
                uint64_t alt;
                if (sq.first == INF)
                {
                    alt = x.second;
                }
                else
                {
                    alt = sq.first + x.second;
                }
                if (alt < dist[x.first])
                {
                    dist[x.first] = alt;
                    q.push({alt, x.first});
                }
            }
        }
    }

    for (size_t i = 0; i < dist.size(); i++)
    {
        std::cout << dist[i] << " ";
    }

    return 0;
}
