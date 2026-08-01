#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e4 + 5;
const LL MOD = 1e9 + 9;
const LL inv2 = (MOD + 1) / 2;

int n, m, K;
int *a[N];

int *up[N], *dn[N];
int *pre[N], *nxt[N];

std::vector<std::pair<int, LL>> vct;

struct BIT {
	LL t[N];
	void clear() { for(int i = 1; i <= m; i++) t[i] = 0; }
	void add(int x, LL v) { while(x <= m) (t[x] += v) %= MOD, x += x & -x; }
	LL query(int r) { LL ret = 0; while(r) (ret += t[r]) %= MOD, r -= r & -r; return ret; }
} bit0, bit1, bit2;

LL tmp[N];
void clear() {
	bit0.clear(), bit1.clear(), bit2.clear();
}

void add(int x, LL v) {
	bit0.add(1, v), bit0.add(x + 1, MOD - v);
	bit1.add(1, v), bit1.add(x + 1, (MOD - v) * (x + 1) % MOD);
	bit2.add(1, v), bit2.add(x + 1, (MOD - v) * (x + 1) % MOD * (x + 1) % MOD);
}

LL query(int x) {
	if(x < 0) return 0;
	LL sum = bit0.query(x) * (x + 1) % MOD * (x + 2) % MOD;
	sum += bit1.query(x) * (3 * MOD - 3 - 2 * x) % MOD;
	sum += bit2.query(x);
	return sum * inv2 % MOD;
}

// LL tmp[N];
// void clear() {
// 	for(int i = 1; i <= m; i++) tmp[i] = 0;
// }

// void add(int x, LL v) {
// 	(tmp[1] += v) %= MOD, (tmp[x + 1] += MOD - v) %= MOD;
// 	// for(int i = 1; i <= x; i++) (tmp[i] += v) %= MOD;
// }

// LL query(int x) {
// 	LL sum = 0;
// 	for(int i = 1; i <= x; i++) for(int j = 1; j <= i; j++) for(int k = 1; k <= j; k++) (sum += tmp[k]) %= MOD;
// 	return sum;
// }

int main() {
	scanf("%d%d%d", &n, &m, &K);
	for(int i = 0; i <= n + 1; i++) {
		a[i] = new int[m + 2]();
		pre[i] = new int[m + 2]();
		nxt[i] = new int[m + 2]();
		up[i] = new int[m + 2]();
		dn[i] = new int[m + 2]();
	}
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[i][j] = 1;
	while(K--) { int x, y; scanf("%d%d", &x, &y); a[x][y] = 0; }
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) pre[i][j] = (a[i][j - 1] ? pre[i][j - 1] : j);
		for(int j = m; j >= 1; j--) nxt[i][j] = (a[i][j + 1] ? nxt[i][j + 1] : j);
	}
	for(int j = 1; j <= m; j++) {
		for(int i = 1; i <= n; i++) up[i][j] = (a[i - 1][j] ? up[i - 1][j] : i);
		for(int i = n; i >= 1; i--) dn[i][j] = (a[i + 1][j] ? dn[i + 1][j] : i);
	}
	LL ans = 0;
	for(int j = 1; j <= m; j++) {
		clear(), vct.clear();
		for(int i = 1; i <= n; i++) {
			if(a[i][j] == 0) {
				for(int k = 0; k < (int)vct.size() - 2; k++) add(vct[k].first, (MOD - 1) * vct[k].second % MOD);
				vct.clear();
			} else {
				int len = std::min(j - pre[i][j], nxt[i][j] - j);
				// printf("i = %d, j = %d, len = %d\n", i, j, len);
				if(vct.size() >= 2) add(vct.end()[-2].first, vct.end()[-2].second);
				(ans += query(len - 1) * (dn[i][j] - i) % MOD) %= MOD;
				// if(query(len - 1) * (dn[i][j] - i) != 0) printf("i = %d, j = %d, ans += %lld\n", i, j, query(len - 1) * (dn[i][j] - i));
				vct.emplace_back(len, i - up[i][j]);
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
} /*
6 8
12
1 2
1 3
1 4
1 6
2 2
3 2
3 3
3 4
3 7
6 4
6 6
4 8
*/