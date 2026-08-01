#include <cstdio>
#include <algorithm>

int main() {
	int t1, t2, a1, a2;
	scanf("%d%d%d%d", &t1, &t2, &a1, &a2);
	for(int i = t1; i <= t2; i++) {
		bool flag = false;
		for(int j = a1; j <= a2; j++) {
			bool prime = true;
			int sum = i + j;
			for(int k = 2; k * k <= sum; k++) prime &= (sum % k != 0);
			flag |= prime;
		}
		if(!flag) { puts("Takahashi"); return 0; }
	}
	puts("Aoki");
	return 0;
}