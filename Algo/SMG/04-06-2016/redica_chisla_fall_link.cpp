#include <iostream>
#include <vector>

std::vector<int> v;
std::vector<int> fl;

int main()
{
    int n;
    std::cin >> n;
    v.resize(n);
    fl.resize(n);
    for(int i = 0; i < n; i++)
    {
        std::cin >> v[i];
        fl[i] = -1;
    }
    for(int i = 1; i < n; i++)
    {
        int curr = i - 1;
        if(v[i] <= v[curr])
        {
            while(v[i] <= v[curr])
            {
                curr = fl[curr];
                if(curr < 0)
                {
                    break;
                }
            }
        }
        fl[i] = curr;
    }
    for(int i = 0; i < n; i++)
    {
        if(fl[i]==-1)
        {
            std::cout << "A\t";
            continue;
        }
        std::cout << v[fl[i]] << "\t";
    }
    std::cout << "\b" << std::endl;
    return 0;
}
