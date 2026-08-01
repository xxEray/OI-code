#include <bits/stdc++.h>

typedef long long LL;

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D;
	char gc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char ch = gc();
		while(ch < '0' || ch > '9') ch = gc();
		for(x = 0; '0' <= ch && ch <= '9'; ch = gc()) x = x * 10 + ch - '0';
	}
}
using FIO::read;

const int N = 3000 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
int a[N][N];

std::vector<int> order, update[N];
int lcp[N], pos[N], tmp[N];

int fa[N], size[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) {
	x = find(x), y = find(y);
	if(x != y) fa[x] = y, size[y] += size[x], size[x] = 0;
}
LL calc(int x) { x = find(x); return (LL)size[x] * (size[x] - 1) / 2; }

int main() {
#ifndef DEBUG
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
#endif
	scanf("%*d%d%d", &n, &m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &a[i][j]), a[i][j] &= 1, a[i][j] ^= a[i][j - 1];
	// for(int i = 1; i <= n; i++) for(int j = 0; j <= m; j++) printf("%d%c", a[i][j], j == m ? '\n' : ' ');
	for(int i = 0; i <= m; i++) order.push_back(i), pos[i] = i, lcp[i] = 0;
	LL ans = 0;
	for(int i = n; i >= 1; i--) {
		std::vector<int> vct;
		for(int j : order) if(a[i][j] == 0) vct.push_back(j);
		for(int j : order) if(a[i][j] == 1) vct.push_back(j);
		for(int j = 0; j < m; j++) {
			if(a[i][vct[j]] != a[i][vct[j + 1]]) { tmp[j] = 0; continue; }
			tmp[j] = INF;
			for(int k = pos[vct[j]]; k < pos[vct[j + 1]]; k++) tmp[j] = std::min(tmp[j], lcp[k] + 1);
		}
		for(int j = 0; j <= m; j++) lcp[j] = tmp[j], pos[vct[j]] = j;
		for(int j = i; j <= n; j++) update[j].clear();
		for(int j = 0; j < m; j++) update[i + lcp[j] - 1].push_back(j);
		order = vct;
		for(int j = 0; j <= m; j++) fa[j] = j, size[j] = 1;
		LL ret = 0;
		for(int j = n; j >= i; j--) {
			for(int k : update[j]) {
				int x = order[k], y = order[k + 1];
				ret -= calc(x) + calc(y);
				merge(x, y);
				ret += calc(x);
			}
			ans += ret;
		}
	}
	printf("%lld\n", (LL)n * (n + 1) / 2 * m * (m + 1) / 2 - ans);
	return 0;
}
