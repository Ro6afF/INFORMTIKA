#include <iostream>
#include <vector>
#include <set>
std::vector<std::set<int>> v;
std::vector<int> out;
int main()
{
	int p, m;
	std::cin >> p >> m;
	v.resize(m);
	for(int i = 0; i < m; i++)
	{
		int a, b;
		std::cin >> a >> b;
		v[a].insert(b);
		v[b].insert(a);
	}
	int k;
	std::cin >> k;
	
	for(int i = 0; i < p; i++)
	{
		if((int)v[i].size() >= k)
		{
			out.push_back(i);
		}
	}

	std::cout<<out.size()<<'\n';
	for(int i = 0; i < out.size() - 1; i++)
	{
		std::cout<< out[i] << " ";
	}

	if(out.size() > 1)
	{
		std::cout<<out[out.size() - 1]<<std::endl;
	}

	return 0;
}
