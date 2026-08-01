#include <bits/stdc++.h>

const int N = 1e6 + 5;

int n;
int a[N];

int tmp[N];
void discrete() {
	for(int i = 1; i <= n; i++) tmp[i] = a[i];
	std::sort(tmp + 1, tmp + n + 1);
	int c = std::unique(tmp + 1, tmp + n + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i] = std::lower_bound(tmp + 1, tmp + c + 1, a[i]) - tmp;
}

struct BIT {
	int t[N];
	void modify(int x, int v) { while(x <= n) t[x] = std::max(t[x], v), x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret = std::max(ret, t[r]), r -= r & -r; return ret; }
} bit;

int f[N];
int mxf;

std::vector<int> vct[N];

bool dfs(int u, int d) {
	if(d == mxf) return true;
	while(!vct[d + 1].empty()) {
		if(vct[d + 1].back() <= u) vct[d + 1].pop_back();
		else if(a[vct[d + 1].back()] <= a[u]) break;
		else if(dfs(vct[d + 1].back(), d + 1)) { vct[d + 1].pop_back(); return true; }
		else vct[d + 1].pop_back();
	}
	return false;
}

int main() {
#ifndef DEBUG
	freopen("lis.in", "r", stdin);
	freopen("lis.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	discrete();
	for(int i = 1; i <= n; i++) f[i] = bit.query(a[i] - 1) + 1, bit.modify(a[i], f[i]), mxf = std::max(mxf, f[i]);
	// printf("f: "); for(int i = 1; i <= n; i++) printf("%d ", f[i]); puts("");
	for(int i = n; i >= 1; i--) vct[f[i]].emplace_back(i);
	int ans = 0;
	for(int i = 1; i <= n; i++) if(f[i] == 1) {
		if(dfs(i, 1)) ans++;
		vct[1].pop_back();
	}
	printf("%d\n", n - ans);
	return 0;
} /*
6
4 6 5 2 1 3
*/