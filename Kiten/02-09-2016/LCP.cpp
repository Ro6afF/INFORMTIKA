#include <iostream>
#include <string>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s;
    std::cin >> s;
    int q;
    std::cin >> q;
    for (int i = 0; i < q; i++)
    {
        int a, b;
        std::cin >> a >> b;
        a--;
        b--;
        int cnt = 0;
        while (s[a] == s[b])
        {
            a++;
            b++;
            cnt++;
        }
        std::cout << cnt << '\n';
    }
}
