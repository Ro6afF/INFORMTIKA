
#include <iostream>
#include <vector>

std::vector<bool> wheel;

int main() 
{
	int n;
	std::cin>>n;
	int blq = 2*3*5*7*11*13;
	wheel.resize(std::max(blq, n)+5, true);
	
	
	for(int i = 1; i <=blq; i++)
	{
		if(!((i%2 != 0 && i%3 != 0 && i%5 != 0 && i%7 != 0 && i%11 != 0 && i%13 != 0) || (i==2 || i==3 || i==5 || i==7 || i==11 || i==13)))
		{
			wheel[i] = false;
		}
	}
	for(int i = 1; i<=blq; i++)
	{
		if(!wheel[i] || i == 2 || i == 3 || i==5 || i==7 || i==11 || i==13)
		{
			int tmp = i;
			while(tmp+blq<=n)
			{
				tmp += blq;
				wheel[tmp] = false;
			}
		}
	}
	wheel[1]=false;
	for(int i = 1; i<n; i++)
	{
		if(wheel[i])
			std::cout<<i<<", ";
	}
	return 0;
}
