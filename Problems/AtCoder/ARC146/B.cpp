#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

int n;
int K;
LL m;
LL a[N], b[N];

#define bit(x, y) ((x) >> (y) & 1)

bool check(LL x) {
	for(int i = 1; i <= n; i++) {
		b[i] = 0;
		bool flag = false;
		for(int j = 35; j >= 0; j--)
			if(bit(a[i], j) == bit(x, j)) b[i] |= bit(a[i], j) << j;
			else if(bit(x, j) == 1) b[i] |= 1LL << j, flag = true;
			else flag ? 0 : b[i] |= 1LL << j;
		// printf("b[%d] = %d\n", i, b[i]);
		b[i] -= a[i];
	}
	std::sort(b + 1, b + n + 1);
	LL sum = 0;
	for(int i = 1; i <= K; i++) sum += b[i];
	return sum <= m;
}

int main() {
	scanf("%d%lld%d", &n, &m, &K);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	// check(10);
	LL l = 1, r = (1LL << 35);
	while(l < r) {
		LL mid = l + ((r - l) >> 1);
		if(check(mid)) l = mid + 1;
		else r = mid;
	}
	printf("%lld\n", l - 1);
	return 0;
}