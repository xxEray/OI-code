#include <bits/stdc++.h>

typedef long long LL;

const int N = 5000 + 5;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;
struct Node { int l, r; } a[N];

std::vector<LL> extra;

void preprocess() {
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.l == y.l ? x.r < y.r : x.l > y.l; });
	int j = 0, mnr = INF;
	for(int i = 1; i <= n; i++)
		if(mnr > a[i].r) a[++j] = a[i], mnr = std::min(mnr, a[i].r);
		else extra.push_back(a[i].r - a[i].l);
	n = j;
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.l < y.l; });
	std::sort(extra.begin(), extra.end(), std::greater<LL>());
	for(int i = 1; i < (int)extra.size(); i++) extra[i] += extra[i - 1];
}

LL f[N][N], g[N][N];

int main() {
// #ifndef DEBUG
// 	freopen("se.in", "r", stdin);
// 	freopen("se.out", "w", stdout);
// #endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].l, &a[i].r);
	preprocess();
	// printf("a: "); for(int i = 1; i <= n; i++) printf("(%d, %d) ", a[i].l, a[i].r); puts("");
	// printf("extra: "); for(LL x : extra) printf("%lld ", x); puts("");
	for(int i = 0; i <= m; i++) for(int j = 1; j <= n; j++) f[i][j] = -LLINF;
	for(int k = 1; k <= m; k++) {
		LL mx1 = -LLINF, mx2 = -LLINF;
		for(int i = 1; i <= n; i++) {
			mx1 = std::max(mx1, f[k - 1][i - 1]);
			mx2 = std::max(mx2, f[k - 1][i - 1] + a[i].r);
			f[k][i] = std::max(mx1, mx2 - a[i].l);
		}
		// printf("f[%d]: ", k); for(int i = 1; i <= n; i++) printf("%lld ", f[k][i]); puts("");
	}
	for(int k = 1; k <= m; k++) {
		LL mx1 = -LLINF, mx2 = -LLINF;
		for(int i = 1; i <= n; i++) {
			mx1 = std::max(mx1, g[k][i - 1]);
			mx2 = std::max(mx2, g[k - 1][i - 1] + a[i].r);
			g[k][i] = std::max(mx1, mx2 - a[i].l);
		}
		// printf("g[%d]: ", k); for(int i = 1; i <= n; i++) printf("%lld ", f[k][i]); puts("");
	}
	LL ans = -LLINF;
	for(int i = std::max(m - (int)extra.size(), 1); i <= m; i++) ans = std::max(ans, std::max(f[i][n], g[i - 1][n]) + (i == m ? 0 : extra[m - i - 1]));
	printf("%lld\n", ans);
	return 0;
}