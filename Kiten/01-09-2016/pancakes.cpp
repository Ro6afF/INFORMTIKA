#include <iostream>

void flip(int arr[], int i)
{
    int temp, start = 0;
    while (start < i)
    {
        temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}

int findMax(int arr[], int n)
{
    int mi, i;
    for (mi = 0, i = 0; i < n; ++i)
        if (arr[i] > arr[mi])
            mi = i;
    return mi;
}

void pancakeSort(int *arr, int n)
{
    for (int curr_size = n; curr_size > 1; --curr_size)
    {
        int mi = findMax(arr, curr_size);

        if (mi != curr_size - 1)
        {
            flip(arr, mi);
            std::cout << mi + 1<< " ";
            std::cout << curr_size << " ";
            flip(arr, curr_size - 1);
        }
    }
    std::cout << std::endl;
}

int main()
{
    int n;
    std::cin >> n;

    int *arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    pancakeSort(arr, n);
    return 0;
}
