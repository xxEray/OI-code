#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 500 + 5;
const LL MOD = 998244353;

int n, m, Q;
struct Constraint { int l, r, v; } q[N];

int a[N];
int ans = 0;
void dfs(int x) {
	if(x == n + 1) {
		bool flag = true;
		for(int i = 1; i <= Q; i++) {
			int mx = 0;
			for(int j = q[i].l; j <= q[i].r; j++) mx = std::max(mx, a[j]);
			flag &= (mx == q[i].v);
		}
		ans += flag;
		return;
	}
	for(int i = 1; i <= m; i++) a[x] = i, dfs(x + 1);
}

int main() {
#ifndef DEBUG
	freopen("seq.in", "r", stdin);
	freopen("seq.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &Q, &m);
		for(int i = 1; i <= Q; i++) scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].v);
		dfs(1);
		printf("%d\n", ans);
	}
	return 0;
}
