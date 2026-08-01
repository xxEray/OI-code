#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n, m;
int c[N], a[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret *= x; if(!(y >>= 1)) return ret; x *= x; } }

int main() {
#ifndef DEBUGz
	freopen("div.in", "r", stdin);
	freopen("div.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%d%d", &c[i], &a[i]);
		std::vector<int> ans;
		for(int x = 1; x <= 1000000; x++) {
			LL val = 0;
			for(int i = 1; i <= n; i++) val += c[i] * qpow(x, a[i]);
			LL val2 = 0;
			for(int i = 0; i < m; i++) val2 += qpow(x, i);
			if(val % val2 == 0) ans.emplace_back(x);
		}
		if((int)ans.size() == 1000000) puts("-1");
		else {
			printf("%d\n", (int)ans.size());
			for(int x : ans) printf("%d ", x);
			puts("");
		}
	}
	return 0;
}