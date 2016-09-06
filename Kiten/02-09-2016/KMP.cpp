#include <iostream>
#include <string>
#include <vector>

void ComputeLPSArray(std::string pat, int m, int *lps)
{
    int len = 0;
    int i = 1;

    lps[0] = 0;

    while (i < m)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

static std::vector<int> SearchString(std::string str, std::string pat)
{
    std::vector<int> retVal;
    int M = pat.length();
    int N = str.length();
    int i = 0;
    int j = 0;
    int *lps = new int[M];

    ComputeLPSArray(pat, M, lps);

    while (i < N)
    {
        if (pat[j] == str[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            retVal.push_back(i - j);
            j = lps[j - 1];
        }

        else if (i < N && pat[j] != str[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }

    delete[] lps;

    return retVal;
}

int main()
{
    std::string data, pattern;
    std::cin >> data >> pattern;
    for (auto &x : SearchString(data, pattern))
    {
        std::cout << x + 1 << std::endl;
    }
}
