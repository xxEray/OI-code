#include <bits/stdc++.h>

typedef long long LL;

const int N = 60000 + 5;
const int MAXA = 40000 + 5;
const int MAXK = 40 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, K, coeficient;
LL a[N];

LL sum[N];

LL f[N], g[N];
int cnt[MAXA];

int pl, pr;
LL val;
void add(int i) { val -= cnt[a[i]] * cnt[a[i]]; cnt[a[i]]++; val += cnt[a[i]] * cnt[a[i]]; }
void del(int i) { val -= cnt[a[i]] * cnt[a[i]]; cnt[a[i]]--; val += cnt[a[i]] * cnt[a[i]]; }
void cdq(int l, int r, int vl, int vr) {
	if(l > r) return;
	// printf("cdq(%d, %d, %d, %d)\n", l, r, vl, vr);
	int mid = (l + r) >> 1;
	int ovr = vr;
	vr = std::min(mid - 1, vr);
	while(pr < mid) add(++pr);
	while(pl > vl + 1) add(--pl);
	while(pr > mid) del(pr--);
	while(pl < vl + 1) del(pl++);
	// printf("mid = %d, pl = %d, pr = %d, val = %lld\n", mid, pl, pr, val);
	int pos = -1;
	for(int i = vl; i <= vr; i++) {
		while(pl < i + 1) del(pl++);
		// printf("   i = %d, value = %lld\n", i, g[i] + (sum[mid] - sum[i + 1]) * val);
		if(f[mid] > g[i] + (sum[mid] - sum[i + 1]) * val)
			f[mid] = g[i] + (sum[mid] - sum[i + 1]) * val, pos = i;
	}
	// printf("f[%d] = %lld\n", mid, f[mid]);
	assert(pos != -1);
	cdq(l, mid - 1, vl, pos), cdq(mid + 1, r, pos, ovr);
}

int main() {
#ifndef DEBUG
	freopen("on.in", "r", stdin);
	freopen("on.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &K, &coeficient);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	LL base = std::accumulate(a + 1, a + n + 1, 0LL);
	base *= base;
	for(int i = 1; i <= n; i++) base -= a[i] * a[i];
	base /= 2;
	if(!coeficient) { printf("%lld\n", base); return 0; }
	for(int i = 1; i <= n; i++) sum[i] = sum[i - 1] + std::abs(a[i] - a[i - 1]) + (a[i] ^ a[i - 1]);
	for(int i = 0; i <= n; i++) f[i] = g[i] = LLINF;
	g[0] = 0;
	for(int _ = 1; _ <= K; _++) {
		for(int i = 0; i <= n; i++) cnt[a[i]] = 0;
		pl = 1, pr = 0, val = 0;
		cdq(_, n, 0, n);
		// printf("f[%d]: ", _); for(int i = 0; i <= n; i++) printf("%lld ", f[i]); puts("");
		for(int i = 0; i <= n; i++) g[i] = f[i], f[i] = LLINF;
	}
	printf("%lld\n", g[n] + base);
	return 0;
}