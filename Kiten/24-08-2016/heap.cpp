#include <iostream>
#include <vector>

std::vector<int> heap;
void add(int x)
{
    heap.push_back(x);
    int curr = heap.size() - 1;
    while (heap[curr / 2] > heap[curr] && curr != 0)
    {
        std::swap(heap[curr / 2], heap[curr]);
        curr /= 2;
    }
}

int pop()
{
    int kodaret = heap[1];
    heap[1] = heap[heap.size() - 1];
    heap.pop_back();
    int curr = 1;

    while (true)
    {
        int curr1 = curr * 2;
        int curr2 = curr1 + 1;
        if (curr >= (int)heap.size())
        {
            break;
        }
        if (curr1 >= (int)heap.size())
        {
            break;
        }
        if (curr2 >= (int)heap.size())
        {
            if (heap[curr] > heap[curr1])
            {
                std::swap(heap[curr], heap[curr1]);
                curr = curr1;
            }
            else
                break;
        }
        else
        {
            if (heap[curr1] < heap[curr2])
            {
                if (heap[curr] > heap[curr1])
                {
                    std::swap(heap[curr], heap[curr1]);
                    curr = curr1;
                }
                else
                    break;
            }
            else
            {
                if (heap[curr] > heap[curr2])
                {
                    std::swap(heap[curr], heap[curr2]);
                    curr = curr2;
                }
                else
                    break;
            }
        }
    }
    return kodaret;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    heap.push_back(-1);
    for (int i = 0; i < n; i++)
    {
        char ch;
        std::cin >> ch;
        if (ch == 'a')
        {
            int x;
            std::cin >> x;
            add(x);
        }
        else
        {
            std::cout << pop() << std::endl;
        }
    }
    return 0;
}
