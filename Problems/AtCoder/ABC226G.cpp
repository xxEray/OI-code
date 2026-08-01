#include <cstdio>
#include <algorithm>

typedef long long LL;

LL a[6], b[6];

void carry(int x, int y) {
	LL t = std::min(a[x], b[y]);
	a[x] -= t, a[x - y] += t;
	b[y] -= t;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		a[0] = b[0] = 0;
		scanf("%lld%lld%lld%lld%lld", &b[1], &b[2], &b[3], &b[4], &b[5]);
		scanf("%lld%lld%lld%lld%lld", &a[1], &a[2], &a[3], &a[4], &a[5]);
		carry(5, 5);
		carry(4, 4);
		carry(5, 4);
		carry(3, 3);
		carry(5, 3);
		carry(4, 3);
		carry(5, 2), carry(3, 2);
		carry(4, 2), carry(2, 2);
		carry(3, 2);
		carry(2, 2);
		carry(5, 1);
		carry(4, 1);
		carry(3, 1);
		carry(2, 1);
		carry(1, 1);
		puts(!b[1] && !b[2] && !b[3] && !b[4] && !b[5] ? "Yes" : "No");
	}
	return 0;
}