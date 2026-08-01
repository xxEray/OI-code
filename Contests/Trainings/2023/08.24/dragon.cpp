#include <bits/stdc++.h>

typedef long long LL;
typedef unsigned long long ull;

const int N = 1e5 + 5;
const int SQRTN = 500;
const ull HSH = 23333;

int n, m, K;
int a[N];

int blk[N];
struct Query { int l, r, id; } q[N];

LL out[N];

ull val[N], pre[N];
int last[N], cnt[N];
LL ans;
void add(int i) {
	ans -= (LL)cnt[pre[i]] * (cnt[pre[i]] - 1) / 2;
	cnt[pre[i]]++;
	ans += (LL)cnt[pre[i]] * (cnt[pre[i]] - 1) / 2;
}
void del(int i) {
	ans -= (LL)cnt[pre[i]] * (cnt[pre[i]] - 1) / 2;
	cnt[pre[i]]--;
	ans += (LL)cnt[pre[i]] * (cnt[pre[i]] - 1) / 2;
}

ull tmp[N];
void discrete() {
	int c = 0;
	for(int i = 0; i <= n; i++) tmp[++c] = pre[i];
	std::sort(tmp + 1, tmp + c + 1);
	c = std::unique(tmp + 1, tmp + c + 1) - tmp - 1;
	for(int i = 0; i <= n; i++) pre[i] = std::lower_bound(tmp + 1, tmp + c + 1, pre[i]) - tmp;
}

int main() {
#ifndef DEBUG
	freopen("dragon.in", "r", stdin);
	freopen("dragon.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &K, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++) scanf("%d%d", &q[i].l, &q[i].r), q[i].l--, q[i].id = i;
	int sqrtn = round(sqrt(n));
	val[0] = 1;
	for(int i = 1; i <= n; i++) val[i] = val[i - 1] * HSH;
	for(int i = 1; i <= n; i++) {
		last[a[i]]++;
		if(last[a[i]] < K) pre[i] = pre[i - 1] + val[a[i]];
		else pre[i] = pre[i - 1] - (K - 1) * val[a[i]], last[a[i]] = 0;
	}
	discrete();
	for(int i = 1; i <= n; i++) blk[i] = (i - 1) / sqrtn + 1;
	std::sort(q + 1, q + m + 1, [&](Query x, Query y) { return blk[x.l] == blk[y.l] ? x.r < y.r : blk[x.l] < blk[y.l]; });
	int l = 1, r = 0;
	for(int i = 1; i <= m; i++) {
		while(r < q[i].r) add(++r);
		while(l > q[i].l) add(--l);
		while(r > q[i].r) del(r--);
		while(l < q[i].l) del(l++);
		out[q[i].id] = ans;
	}
	for(int i = 1; i <= m; i++) printf("%lld\n", out[i]);
	return 0;
}