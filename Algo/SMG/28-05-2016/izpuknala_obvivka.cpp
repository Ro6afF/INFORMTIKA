#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>

#define x first
#define y second

int area (int dX0, int dY0, int dX1, int dY1, int dX2, int dY2)
{
    int dArea = (dX0 + dX1) * (dY0 - dY1) + (dX1 + dX2) * (dY1 - dY2) + (dX0 + dX2) * (dY2 - dY0);
    return dArea;
}

std::vector<std::pair<int, int>> v;
std::set<int> shell;

int main()
{
    int n;
    std::cin >> n;
    for(int i = 0; i < n; i++)
    {
        int a, b;
        std::cin >> a >> b;
        v.push_back({a, b});
    }

    std::sort(std::begin(v), std::end(v));

    int cur = 0;
    int cur_cand = 1;

    shell.insert(cur);
    std::cout << "( " << v[cur_cand].x << ", " << v[0].y << " )\n";

    while(true)
    {
        for(int i = 0; i < n; i++)
        {
            if(area(v[i].x, v[i].y, v[cur].x, v[cur].y, v[cur_cand].x, v[cur_cand].y) < 0)
            {
                cur_cand = i;
            }
        }
        if(shell.insert(cur_cand).second == true)
        {
            std::cout << "( " << v[cur_cand].x << ", " << v[cur_cand].y << " )\n";
            cur = cur_cand;
            cur_cand++;
        }
        else
        {
            break;
        }
    }
    return 0;
}
