#include <iostream>
#include <set>
#include <utility>
#include <vector>

std::set<std::pair<unsigned long long, unsigned long long>> s;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    unsigned long long n, l, d, x1, a, b;
    std::cin >> n >> l >> d >> x1 >> a >> b;
    unsigned long long cur = x1;
    s.insert({0, l});
    for (unsigned long long i = 0; i < n; i++)
    {
        for (std::set<std::pair<unsigned long long, unsigned long long>>::iterator j = s.begin(), e = s.end(); j != e; j++)
        {
            if (j->first < cur && j->second > cur)
            {
                unsigned long long p = j->first, q = j->second;
                s.erase(j);
                s.insert({p, cur});
                s.insert({cur, q});
            }
        }
        for (std::set<std::pair<unsigned long long, unsigned long long>>::iterator j = s.begin(), e = s.end(); j != e; j++)
        {
            if (j->second - j->first >= d)
            {
                goto Go;
            }
        }
        std::cout << i + 1 << std::endl;
        return 0;
    Go:
        cur = (cur * a + b) % (l + 1);
    }
    std::cout << -1 << std::endl;
    return 0;
}
