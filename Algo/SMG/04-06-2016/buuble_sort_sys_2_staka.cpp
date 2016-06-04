#include <iostream>
#include <stack>

std::stack<int> s1, s2;

int main()
{
    int n;
    std::cin >> n;
    for(int i = 0; i < n; i++)
    {
        int a;
        std::cin >> a;
        while( !s1.empty() && a > s1.top() )
        {
            s2.push(s1.top());
            s1.pop();
        }
        s1.push(a);
        while(!s2.empty())
        {
            s1.push(s2.top());
            s2.pop();
        }
    }
    while(!s1.empty())
    {
        std::cout<<s1.top() << "\t";
        s1.pop();
    }
    return 0;
}
