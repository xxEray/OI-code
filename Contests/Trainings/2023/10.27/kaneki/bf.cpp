#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 1e9 + 7;

int n, m;
LL a[N];
int b[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int t = 1; t <= m; t++) {
		int type, l, r;
		scanf("%d%d%d", &type, &l, &r);
		if(type == 1) {
			LL x;
			scanf("%lld", &x);
			for(int i = l; i <= r; i++) if(b[i] < t) (a[i] += x) %= MOD;
		} else if(type == 2) {
			LL x;
			scanf("%lld", &x);
			for(int i = l; i <= r; i++) if(b[i] < t) (a[i] *= x) %= MOD;
		} else if(type == 3) {
			int x;
			scanf("%d", &x);
			for(int i = l; i <= r; i++) b[i] = std::max(b[i], t + x);
		} else {
			LL ans = 0;
			for(int i = l; i <= r; i++) (ans += a[i]) %= MOD;
			printf("%lld\n", ans);
		}
	}
	return 0;
}