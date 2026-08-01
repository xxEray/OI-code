#include <cstdio>

typedef long long LL;

LL n, t;

#define print(x) printf("%lld\n", (x) == 0 ? n : (x))

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%lld%lld", &n, &t);
		LL n_ = n / 2 * 2;
		LL stA = n + 1 - t / n_ * n_ % n;
		LL stB = 1;
		t %= n_;
		if(t > (stA - stB + 1) / 2) print(t + 1);
		else print(t);
	}
	return 0;
}