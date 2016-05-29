#include <iostream>
#include <vector>
#include <set>

std::vector<int> tatko;
std::set<int> asdf;

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	tatko.resize(10);
	std::string asd;
	for(int i = 1; i <= 9; i++)
	{
		tatko[i] = i;
	}
	for(int i = 0; i < n; i++)
	{
		std::string s2, s3;
		int s1, s4;
		std::cin >> s1 >> s2 >> s3 >> s4;
		asdf.insert(s1);
		asdf.insert(s4);
		if(s3 == "before")
		{
			tatko[s4] = s1;	
		}
		else
		{
			tatko[s1] = s4;
		}
	}

	for(auto x: asdf)
	{
		asd+=x + '0';
	}

	for(int i = 0; i < asd.size(); i++)
	{
		if(tatko[asd[i] - '0'] != asd[i] - '0')
		{
			for(int j = i; j < asd.size(); j++)
			{
				if(asd[j] == tatko[asd[i]-'0']+'0')
				{
					std::swap(asd[i], asd[j]);
					break;
				}
			}
		}
	}
	std::cout<< asd<<std::endl;
	return 0;
}
