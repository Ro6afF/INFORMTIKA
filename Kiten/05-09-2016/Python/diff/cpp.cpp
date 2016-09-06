#include <iostream>

int main()
{
	unsigned long long a;
	for(unsigned long long i = 0; i < 1000000; i++)
	{
		a+=i;
	}
	std::cout << a << "\n";
}
