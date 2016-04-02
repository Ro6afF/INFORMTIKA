#include <iostream>
#include <deque>
#include <vector>
#include <utility>

std::deque<int> q;
std::vector<std::vector<std::pair<int, int>>> sys;
std::vector<int> res;
std::vector<bool> obh;

int main()
{
	int n, m;
	std::cin>>n>>m;
	sys.resize(n);
	res.resize(n);
	obh.resize(n);
	for(int i = 0; i<m; i++)
	{
		int a, b;
		std::cin>>a>>b;
		sys[a].push_back({b, 0});
		sys[b].push_back({a, 1});
	}
	int start, end;
	std::cin>>start>>end;
	q.push_back(start);
	obh[start] = true;
	while(!q.empty())
	{
		auto sq = q.front();
		q.pop_front();
		for(auto &x:sys[sq])
		{
			if(!obh[x.first])
			{
				if(x.second==0)
				{
					q.push_front(x.first);
					res[x.first] = res[sq];
					obh[x.first] = true;
				}
				else
				{
					q.push_back(x.first);
					res[x.first] = res[sq] + 1;
					obh[x.first] = true;
				}
			}
		}
	}
	std::cout<<res[end]<<std::endl;
	return 0;
}
