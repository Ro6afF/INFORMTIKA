//Nai-malkoto po-golqmo ot n chislo, koeto nqma 2 posledovatelni edinici v dvoi4niq zapis
#include <iostream>

bool arr[32];

int main() {
	long long a, acpy;
	std::cin >> a;
	acpy=a;
	arr[31] = a%2;
	a >>= 1;
	int i = 30;
	int neshtoto = -1;
	while(a != 0) {
		arr[i] = a % 2;
		if(arr[i] == 1 && 1 == arr[i+1]) {
			neshtoto = i;
		}
		a >>= 1;
		i--;
	}
	if(neshtoto == -1)
		std::cout << acpy;
	else {
		int ans = 0;
		for(int j = neshtoto - 2; j > 0; j--){
			if(arr[j] == 0 && arr[j+1] == 0) {
				for(int q = 0; q <= j; q++) {
					ans += arr[q] * (1 << (31 - q));
				}
				ans += 1 << (31 - (j+1));
				break;
			}
		}
		std::cout << ans << std::endl;
	}
	return 0;
}
