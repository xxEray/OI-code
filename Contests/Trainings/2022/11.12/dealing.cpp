#include <bits/stdc++.h>

typedef long long LL;
const int N = 1e6 + 5;
const int LOG_N = 20 + 3;
const LL MOD = 1e9 + 7;

int n, Q;

int fa[N * LOG_N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

int lg[N];
int hash(int k, int i) { return k * n + i; }

int main() {
	// freopen("dealing.in", "r", stdin);
	// freopen("dealing.out", "w", stdout);
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n * 21; i++) fa[i] = i;
	lg[0] = -1;
	for(int i = 1; i <= n; i++) lg[i] = lg[i >> 1] + 1;
	while(Q--) {
		int len, l, r;
		scanf("%d%d%d", &len, &l, &r);
		// for(int i = 0; i <= 20; i++) if(len >> i & 1) {
		// 	merge(hash(i, l), hash(i, r));
		// 	l += 1 << i, r += 1 << i;
		// }
		int k = lg[len];
		merge(hash(k, l), hash(k, r));
		merge(hash(k, l + len - (1 << k)), hash(k, r + len - (1 << k)));
	}
	for(int j = 20; j >= 1; j--) for(int i = 1; i <= n; i++) {
		int x = i, y = find(hash(j, i)) % n;
		if(y == 0) y = n;
		if(x + (1 << j) - 1 > n || y + (1 << j) - 1 > n) continue;
		merge(hash(j - 1, x), hash(j - 1, y));
		merge(hash(j - 1, x + (1 << (j - 1))), hash(j - 1, y + (1 << (j - 1))));
	}
	int cnt = 0;
	for(int i = 1; i <= n; i++) cnt += find(hash(0, i)) == hash(0, i);
	printf("%lld\n", qpow(26, cnt));
	return 0;
}