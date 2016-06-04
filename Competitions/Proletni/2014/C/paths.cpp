#include <iostream>
#include <vector>
#include <queue>

std::vector<std::vector<int> > v;
std::queue<int> qu;
std::vector<int>p;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    v.resize(n);
    p.reserve(n);
    for(int i = 0; i < n; i++)
    {
        p.push_back(-1);
    }
    for(int i = 0; i < m; i++)
    {
        int a, b;
        std::cin >> a >> b;
        a--;
        b--;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    int q;
    std::cin >> q;
    for(int i = 0; i < q; i++)
    {
        p.clear();
        p.reserve(n);
        for(int i = 0; i < n; i++)
        {
            p.push_back(-1);
        }
        int a, b;
        std::cin >> a >> b;
        a--;
        b--;
        p[a] = 0;
        qu.push(a);

        while(!qu.empty())
        {
            int cur = qu.front();
            qu.pop();
            for(int i = 0; i < v[cur].size(); i++)
            {
                int x = v[cur][i];
                if(p[x] == -1)
                {
                    p[x] = p[cur] + 1;
                    qu.push(x);
                }
            }
        }
        int cnt = 0;
        qu.push(b);
        while(!qu.empty())
        {
            int cur = qu.front();
            qu.pop();

            for(int i = 0; i < v[cur].size(); i++)
            {
                int x = v[cur][i];

                if(p[x] == p[cur] - 1)
                {
                    qu.push(x);
                    cnt++;
                }
            }
        }
        std::cout << cnt << " ";
    }
    std::cout<<"\b"<<std::endl;
    return 0;
}
