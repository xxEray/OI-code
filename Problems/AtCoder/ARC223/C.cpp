#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n;
int a[N];

int cnt[N];

LL qpow(LL x, LL y, LL mod) {
	LL ret = 1;
	for(; y; (x *= x) %= mod, y >>= 1) if(y & 1) (ret *= x) %= mod;
	return ret;
}

struct BIT {
	static const int MX = 2e5;
	int t[N];
	void add(int x, int v) { while(x < MX) t[x] += v, x += x & -x; }
	int query(int x) { int ret = 0; while(x) ret += t[x], x -= x & -x; return ret; }
	int query(int l, int r) { return query(r) - (l ? query(l - 1) : 0); }
} bit;

int tmp[N];
void discrete() {
	for(int i = 1; i <= n; i++) tmp[i] = a[i];
	std::sort(tmp + 1, tmp + n + 1);
	int mx = std::unique(tmp + 1, tmp + n + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i] = std::lower_bound(tmp + 1, tmp + mx + 1, a[i]) - tmp;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) cnt[i] = 0;
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			cnt[a[i] % n]++;
		}
		bool flag = false;
		for(int i = 0; i < n; i++) flag |= (cnt[i] >= 2);
		if(flag) puts("0");
		else {
			LL ans = 1;
			for(int i = 1; i <= n - 1; i++) (ans *= qpow(i, n - i, n)) %= n;
			std::sort(a + 1, a + n + 1, [&](int x, int y) { return x % n < y % n; });
			discrete();
			int rev = 0;
			for(int i = 1; i <= n; i++) {
				rev ^=  bit.query(a[i] + 1, BIT::MX) & 1;
				bit.add(a[i], 1);
			}
			if(rev) ans = (n - ans) % n;
			printf("%lld\n", ans);
			for(int i = 1; i <= n; i++) bit.add(a[i], -1);
		}
	}
	return 0;
}