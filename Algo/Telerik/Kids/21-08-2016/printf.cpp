#include <iostream>

template<typename T, typename... Args>
void printf(const char* s, T val, Args... args)
{
	while(*s)
	{
		if(*s == '%')
		{
			if(*(s + 1) == '%')
			{
				s++;
			}
			else
			{
				std::cout<<val;
				s+=2;
				printf(s, args...);
				return;
			}
		}
		std::cout<<*s++;
	}
}

int main()
{
	printf("asdasd%b%a%a", "nesho", "si", "tam");
	return 0;
}
