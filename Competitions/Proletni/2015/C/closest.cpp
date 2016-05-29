#include <iostream>
#include <vector>
#include <algorithm>


#define limit 1000000000000000000

int64_t ans = 1;
std::vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19};

void brum (int64_t n,int last, int64_t searched)
{
	if(searched <= n || last >= 8 || limit / primes[last] < n)
	{
		auto x = std::abs(searched - ans), y = std::abs(searched - n);  
		if( x >  y)
		{
			ans = n;
		}
		else if( x == y )
		{
			ans = std::min (ans, n);
		}
		return;
	}
	brum(n * primes[last], last, searched);
	brum(n , last + 1, searched);
}

int main()
{
	int64_t n, m;
	std::cin >> n >> m;
	brum(1, 0, n);
	std::cout << ans << " ";
	ans = 1;
	brum(1, 0, m);
	std::cout << ans << std::endl;
	
	return 0;
}
