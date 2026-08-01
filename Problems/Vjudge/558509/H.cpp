#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;

int n;
int a[N];

struct Node { int v, sc, id; } tmp[N];
void discrete() {
	a[0] = 1, a[n + 1] = n + 2;
	for(int i = 1; i <= n; i++) tmp[i] = {a[i], -i, i};
	std::sort(tmp + 1, tmp + n + 1, [&](Node x, Node y) { return x.v == y.v ? x.sc < y.sc : x.v < y.v; });
	for(int i = 1; i <= n; i++) a[tmp[i].id] = i + 1;
}

struct BIT {
	LL t[N];
	void init() { for(int i = 1; i <= n + 2; i++) t[i] = 0; }
	void add(int x, LL v) { while(x <= n + 2) t[x] += v, t[x] >= MOD ? t[x] -= MOD : 0, x += x & -x; }
	LL query(int r) { LL ret = 0; while(r) ret += t[r], r -= r & -r; return ret % MOD; }
	LL query(int l, int r) { return query(r) - query(l - 1); }
} bit;

LL f[N], rf[N], h[N];
std::vector<int> g[N], vct;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		discrete();
		for(int i = 2; i <= n + 1; i++) g[i].clear();
		for(int i = 1; i <= n; i++) g[a[i]].push_back(i);
		bit.init(), f[0] = 1, bit.add(a[0], f[0]);
		for(int i = 1; i <= n; i++) f[i] = bit.query(1, a[i] - 1), bit.add(a[i], f[i]);
		bit.init(), f[n + 1] = 1, bit.add(a[n + 1], f[n + 1]);
		for(int i = n; i >= 1; i--) rf[i] = bit.query(a[i] + 1, n + 2), bit.add(a[i], rf[i]);
		LL ans = 0;
		for(int i = 1; i <= n; i++) (ans += f[i] * rf[i] % MOD) %= MOD;
		vct.clear();
		for(int i = n; i >= 1; i--) if(vct.empty() || a[i] > a[vct.back()]) vct.push_back(i);
		// printf("vct: "); for(int x : vct) printf("%d ", x); puts("");
		bit.init();
		for(int i = 0; i < (int)vct.size(); i++) {
			std::vector<int> seq;
			for(int j = (i ? a[vct[i - 1]] : 1); j < a[vct[i]]; j++) seq.insert(seq.end(), g[j].begin(), g[j].end());
			std::sort(seq.begin(), seq.end());
			while(!seq.empty() && seq.back() > vct[i]) seq.pop_back();
			// printf("%d: seq = ", i); for(int x : seq) printf("%d ", x); puts("");
			int sz = seq.size();
			for(int j = sz; j >= 0; j--) h[j] = 0;
			h[sz] = 1, bit.add(n + 2, 1);
			for(int j = sz - 1; j >= 0; j--) h[j] = bit.query(a[seq[j]] + 1, n + 2), bit.add(a[seq[j]], h[j]);
			(ans += MOD - f[vct[i]]) %= MOD;
			for(int j = 0; j < sz; j++) (ans += MOD - f[seq[j]] * h[j] % MOD) %= MOD;
			for(int j = 0; j <= sz - 1; j++) bit.add(a[seq[j]], -h[j]);
			bit.add(n + 2, -1);
			// printf("    ans = %lld\n", ans);
		}
		printf("%lld\n", ans);
	}
	return 0;
} /*
4
5
6 4 8 6 5
4
1 2 3 4
3
3 2 2
4
4 5 6 5
*/