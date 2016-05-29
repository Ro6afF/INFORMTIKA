#include <iostream>
#include <vector>
#include <queue>

using namespace std;

long long n, m;
vector<vector<pair<long long, long long>>> v;
priority_queue<pair<long long, long long>> q;
vector<long long> dist;

long long dji(long long first_, long long last_)
{
	dist.clear();
	dist.resize(n);
	q.push({0, first_});
	while(!q.empty())
	{
		auto sq = q.top();
		q.pop();
		for(auto &x: v[sq.second])
		{
			if(dist[x.first] == 0 || dist[x.first] > dist[sq.second] + x.second)
			{
				q.push({dist[sq.second] + x.second, x.first});
				dist[x.first] = dist[sq.second] + x.second;
			}

		}
	}
	return dist[last_];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	long long start_, mid1, mid2, end_;
	cin >> start_ >> end_;
	cin >> mid1 >> mid2;
	start_ --;
	end_ --;
	mid1 --;
	mid2 --;
	v.resize(n);
	dist.resize(n);
	for(long long i = 0; i< m; i++)
	{
		long long a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		v[a].push_back({b, c});
		v[b].push_back({a, c});
	}
	long long res = 0;
	long long d1 = dji(start_, mid1);
	long long d2 = dji(start_, mid2);
	if(d1 < d2)
	{
		res += d1;
		res += dji(mid1, mid2);
		res += dji(mid2, end_);
	}
	else if(d1 == d2)
	{
		long long d11 = dji(mid2, end_), d22 = dji(mid1, end_);
		res += dji(mid2, mid1);
		if(d11 < d22)
		{
			res += d11;
		}
		else
		{
			res += d22;
		}
	}
	else
	{
		res += d2;
		res += dji(mid2, mid1);
		res += dji(mid1, end_);
	}
	cout<<res <<endl;
	return 0;
}
