#include <iostream>
#include <vector>
#include <queue>
#include <utility>

std::vector<int> tatko;
std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> q;

bool v1mnls(int a, int b)
{
	while(tatko[a]!=a)
	{
		a=tatko[a];
	}
	while(tatko[b]!=b)
	{
		b=tatko[b];
	}
	return a==b;
}

void add(int a, int b)
{
	tatko[a]=tatko[b];
}

int main()
{
	int n, m;
	std::cin>>n>>m;
	tatko.resize(n);
	for(int i = 0; i<n; i++)
	{
		tatko[i] = i;
	}
	for(int i = 0; i<m; i++)
	{
		int a, b, c;
		std::cin>>a>>b>>c;
		q.push({c, {a, b}});
	}

	int iter = 0;
	while(iter<n-1)
	{
		auto sq = q.top();
		q.pop();
		if(!v1mnls(sq.second.first, sq.second.second))
		{
			std::cout<<sq.second.first<<" "<<sq.second.second<<std::endl;
			add(sq.second.first, sq.second.second);
		}
		iter++;
	}
		
	return 0;
}
