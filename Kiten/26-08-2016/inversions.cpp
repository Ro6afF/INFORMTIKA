#include <algorithm>
#include <iostream>
#include <vector>

std::vector<uint64_t> nums;
std::vector<uint64_t> numss;

uint64_t inversions;

void merge(uint64_t s, uint64_t mid, uint64_t e)
{
    uint64_t tmp = s;
    uint64_t i1 = s;
    uint64_t i2 = mid + 1;

    while (i1 <= mid && i2 <= e)
    {
        if (nums[i1] <= nums[i2])
        {
            numss[tmp] = nums[i1];
            i1++;
            tmp++;
        }
        else
        {
            numss[tmp] = nums[i2];
            inversions += (mid - i1 + 1);
            i2++;
            tmp++;
        }
    }
    while (i1 <= mid)
    {
        numss[tmp] = nums[i1];
        i1++;
        tmp++;
    }
    while (i2 <= e)
    {
        numss[tmp] = nums[i2];
        i2++;
        tmp++;
    }
    for (uint64_t i = s; i <= e; i++)
    {
        nums[i] = numss[i];
    }
}

void mergeSort(uint64_t s, uint64_t e)
{
    if (e - s == 0)
        return;
    uint64_t mid = (s + e) / 2;
    mergeSort(s, mid);
    mergeSort(mid + 1, e);
    merge(s, mid, e);
}

int main()
{
    uint64_t n;
    std::cin >> n;
    nums.reserve(n);
    numss.reserve(n);
    for (uint64_t i = 0; i < n; i++)
    {
        uint64_t q;
        std::cin >> q;
        nums.push_back(q);
        numss.push_back(0);
    }
    mergeSort(0, n - 1);
    std::cout << inversions << std::endl;

    return 0;
}
