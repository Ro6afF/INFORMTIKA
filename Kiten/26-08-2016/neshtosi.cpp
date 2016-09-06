#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> v;

int main()
{
    int n;
    std::cin >> n;
    v.reserve(n);
    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        v.push_back(x);
    }

    int start = 0, end = n - 1;
    while (end - start > 1)
    {
        int mid = (start + end) / 2;
        if (v[mid] <= v[end])
        {
            end = mid;
        }
        else
        {
            start = mid;
        }
    }
    std::cout << std::min(v[end], v[start]) << std::endl;

    return 0;
}
