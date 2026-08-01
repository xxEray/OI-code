#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

char s[N];
int n, m, Q;

LL a[50];
std::pair<LL, LL> b[50];

char get_answer(LL x) {
	// printf("get_answer(%d)\n", x);
	if(x <= n) return s[x];
	int i = std::lower_bound(a, a + m + 1, x) - a - 1;
	return get_answer(x - a[i] + b[i].first - 1);
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &m, &Q);
		scanf("%s", s + 1);
		a[0] = 0, b[0] = {1, n};
		for(int i = 1; i <= m; i++) {
			LL l, r;
			scanf("%lld%lld", &l, &r);
			a[i] = a[i - 1] + b[i - 1].second - b[i - 1].first + 1;
			b[i] = {l, r};
		}
		while(Q--) {
			LL x;
			scanf("%lld", &x);
			printf("%c\n", get_answer(x));
		}
	}
	return 0;
} /*
1
3 4 1
abc
1 3
1 6
1 12
1 24
49
*/