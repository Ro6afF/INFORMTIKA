#include <iostream>
#include <vector>
#include <utility>
#include <queue>

int n, m;
std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> q;
std::vector<std::vector<std::pair<int, int>>> sys;
std::vector<bool> used;

bool asd()
{
	for(int i = 0; i<n; i++)
	{
		if(used[i]==false)
		{
			return true;
		}
	}
	return false;
}

int main()
{
	std::cin>>n>>m;
	sys.resize(n);
	used.resize(n);
	for(int i = 0; i<m; i++)
	{
		int a, b, c;
		std::cin>>a>>b>>c;
		sys[a].push_back({b, c});
		sys[b].push_back({a, c});
	}
	for(auto &x:sys[0])
	{
		q.push({x.second, {0, x.first}});
	}
	used[0]=true;
	while(asd())
	{
		auto sq = q.top();
		q.pop();
		std::cout<<sq.second.first<<" "<<sq.second.second<<std::endl;
		for(auto &x:sys[sq.second.second])
		{
			if(!used[x.first])
			{
				q.push({x.second, {sq.second.second, x.first}});
			}
		}
		used[sq.second.first]=true;
		used[sq.second.second]=true;
	}
	return 0;
}
