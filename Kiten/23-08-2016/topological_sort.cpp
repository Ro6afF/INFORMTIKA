#include <iostream>
#include <queue>
#include <vector>

std::vector<std::vector<int>> v;
std::vector<int> s;
std::queue<int> q;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    v.resize(n + 1);
    s.resize(n + 1);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        std::cin >> a >> b;
        v[a].push_back(b);
        s[b]++;
    }
    for (int i = 1; i < n; i++)
    {
        if (s[i] == 0)
        {
            q.push(i);
        }
    }
    while (!q.empty())
    {
        auto sq = q.front();
        q.pop();
        std::cout << sq << " ";
        for (size_t i = 0; i < v[sq].size(); i++)
        {
            s[v[sq][i]]--;
            if (s[v[sq][i]] == 0)
            {
                q.push(v[sq][i]);
            }
        }
    }
}
