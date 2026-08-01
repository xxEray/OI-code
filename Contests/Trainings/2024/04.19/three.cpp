#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;

int a[N], a2[N];
int n;

int le[N], lg[N], lg2[N], lg3[N];
int re[N], rg[N], rg2[N], rg3[N];

int last[N];
struct Query { int x, v, id; } q[N];

int tmp[N];
void discrete() {
	for(int i = 1; i <= n; i++) tmp[i] = a2[i];
	std::sort(tmp + 1, tmp + n + 1);
	int c = std::unique(tmp + 1, tmp + n + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a2[i] = std::lower_bound(tmp + 1, tmp + c + 1, a2[i]) - tmp;
}

const int m = 1048576;
struct SegmentTree {
	int t[N << 2];
	void build() {
		for(int i = 1; i <= (m << 1); i++) t[i] = -INF;
	}
	void modify(int x, int v) {
		x += m, t[x] = std::max(t[x], v);
		for(x >>= 1; x; x >>= 1) t[x] = std::max(t[x << 1], t[x << 1 | 1]);
	}
	int query(int l, int r) {
		l--, r++;
		int ret = -INF;
		for(l += m, r += m; l ^ r ^ 1; l >>= 1, r >>= 1) {
			if(~l & 1) ret = std::max(ret, t[l ^ 1]);
			if(r & 1) ret = std::max(ret, t[r ^ 1]);
		}
		return ret;
	}
} seg;

int main() {
	// freopen("three.in", "r", stdin);
	// freopen("three.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), a2[i] = a[i];
	discrete();
	for(int i = 1; i <= n; i++) le[i] = last[a2[i]], last[a2[i]] = i;
	for(int i = 1; i <= 1000000; i++) last[i] = n + 1;
	for(int i = n; i >= 1; i--) re[i] = last[a2[i]], last[a2[i]] = i;
	std::vector<int> stk;
	for(int i = 1; i <= n; i++) {
		while(!stk.empty() && a[stk.back()] <= a[i]) stk.pop_back();
		lg[i] = (stk.empty() ? 0 : stk.back());
		stk.emplace_back(i);
	}
	stk.clear();
	for(int i = n; i >= 1; i--) {
		while(!stk.empty() && a[stk.back()] <= a[i]) stk.pop_back();
		rg[i] = (stk.empty() ? n + 1 : stk.back());
		stk.emplace_back(i);
	}
	seg.build();
	for(int i = 1; i <= n; i++) q[i].x = lg[i], q[i].v = a2[i], q[i].id = i;
	std::sort(q + 1, q + n + 1, [&](const Query &x, const Query &y) { return x.x < y.x; });
	for(int i = 0, j = 1; i <= n; i++) {
		while(j <= n && q[j].x == i) lg2[q[j].id] = seg.query(q[j].v + 1, 1000000), j++;
		if(i) seg.modify(a2[i], i);
	}
	for(int i = 1; i <= n; i++) if(lg2[i] == -INF) lg2[i] = 0;
	seg.build();
	for(int i = 1; i <= n; i++) q[i].x = lg2[i], q[i].v = a2[i], q[i].id = i;
	std::sort(q + 1, q + n + 1, [&](const Query &x, const Query &y) { return x.x < y.x; });
	for(int i = 0, j = 1; i <= n; i++) {
		while(j <= n && q[j].x == i) lg3[q[j].id] = seg.query(q[j].v + 1, 1000000), j++;
		if(i) seg.modify(a2[i], i);
	}
	for(int i = 1; i <= n; i++) if(lg3[i] == -INF) lg3[i] = 0;
	seg.build();
	for(int i = 1; i <= n; i++) q[i].x = rg[i], q[i].v = a2[i], q[i].id = i;
	std::sort(q + 1, q + n + 1, [&](const Query &x, const Query &y) { return x.x > y.x; });
	for(int i = n + 1, j = 1; i >= 1; i--) {
		while(j <= n && q[j].x == i) rg2[q[j].id] = -seg.query(q[j].v + 1, 1000000), j++;
		if(i) seg.modify(a2[i], -i);
	}
	for(int i = 1; i <= n; i++) if(rg2[i] == INF) rg2[i] = n + 1;
	seg.build();
	for(int i = 1; i <= n; i++) q[i].x = rg2[i], q[i].v = a2[i], q[i].id = i;
	std::sort(q + 1, q + n + 1, [&](const Query &x, const Query &y) { return x.x > y.x; });
	for(int i = n + 1, j = 1; i >= 1; i--) {
		while(j <= n && q[j].x == i) rg3[q[j].id] = -seg.query(q[j].v + 1, 1000000), j++;
		if(i) seg.modify(a2[i], -i);
	}
	for(int i = 1; i <= n; i++) if(rg3[i] == INF) rg3[i] = n + 1;
	// for(int i = 1; i <= n; i++)
	// 	printf("%d: ll=%d,le=%d,lg=%d,lg2=%d,lg3=%d,rl=%d,re=%d,rg=%d,rg2=%d,rg3=%d\n",
	// 		i, ll[i], le[i], lg[i], lg2[i], lg3[i], rl[i], re[i], rg[i], rg2[i], rg3[i]);
	LL ans = 0;
	for(int i = 1; i <= n; i++) {
		// abc
		if(rg[i] != n + 1 && rg2[i] != n + 1)
			(ans += (LL)(rg3[i] - rg2[i]) * (i - std::max(lg[i], le[i])) % MOD * a[rg[i]] % MOD * a[rg2[i]] % MOD * a[i]) %= MOD;
		// bca
		if(lg[i] && lg2[i] && lg2[i] > le[i])
			(ans += (LL)(lg2[i] - std::max(lg3[i], le[i])) * (rg[i] - i) % MOD * a[lg[i]] % MOD * a[lg2[i]] % MOD * a[i]) %= MOD;
		// bac
		if(lg[i] && rg[i] != n + 1 && lg[i] > le[i])
			(ans += (LL)(lg[i] - std::max(lg2[i], le[i])) * (rg2[i] - rg[i]) % MOD * a[lg[i]] % MOD * a[rg[i]] % MOD * a[i]) %= MOD;
		// ab (a)  => aab & aba V
		if(re[i] != n + 1 && rg[i] != n + 1 && re[i] < rg2[i])
			(ans += (LL)(i - std::max(lg[i], le[i])) * (rg2[i] - std::max(re[i], rg[i])) % MOD * a[rg[i]] % MOD * a[i] % MOD * a[i]) %= MOD;
		// baa V
		if(lg[i] && lg[i] > le[i] && re[i] != n + 1 && re[i] < rg[i])
			(ans += (LL)(lg[i] - std::max(lg2[i], le[i])) * (rg[i] - re[i]) % MOD * a[lg[i]] % MOD * a[i] % MOD * a[i]) %= MOD;
		// aaa V
		if(re[i] != n + 1 && re[re[i]] != n + 1 && rg[i] > re[re[i]])
			(ans += (LL)(i - std::max(lg[i], le[i])) * (rg[i] - re[re[i]]) * a[i] % MOD * a[i] % MOD * a[i]) %= MOD;
		// printf("i = %d, ans = %lld\n", i, ans);
	}
	printf("%lld\n", ans);
	return 0;
}