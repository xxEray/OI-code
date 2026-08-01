#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const int M = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;
int seq[N];
LL a[N], b[N], cpa[N];

LL f[M];
LL calc() {
	LL ret = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= seq[i]; j++) a[j] += seq[i] * b[j];
		ret += *std::max_element(a + 1, a + seq[i] + 1);
	}
	for(int i = 1; i <= n; i++) a[i] = cpa[i];
	return ret;
}

int trie[2][N * 70], ctrie = 1;
LL dfs(int p, int q, int d) {
	if(!p || !q || d == -1) return 0;
	if((trie[0][p] && trie[1][q]) || (trie[1][p] && trie[0][q])) return std::max(dfs(trie[0][p], trie[1][q], d - 1), dfs(trie[1][p], trie[0][q], d - 1)) | (1 << d);
	else return std::max(dfs(trie[0][p], trie[0][q], d - 1), dfs(trie[1][p], trie[1][q], d - 1));
}

int main() {
// #ifndef DEBUG
	freopen("d.in", "r", stdin);
	freopen("d.out", "w", stdout);
// #endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), cpa[i] = a[i];
	for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	for(int j = 1; j <= m; j++) {
		for(int i = 1; i <= n; i++) scanf("%d", &seq[i]);
		f[j] = calc();
		// printf("%lld\n", f[j]);
	}
	LL mx = -LLINF;
	for(int i = 1; i <= m; i++) mx = std::max(mx, f[i]);
	for(int i = 1; i <= m; i++) {
		int now = 1;
		for(int j = 63; j >= 0; j--) {
			if(!trie[f[i] >> j & 1][now]) trie[f[i] >> j & 1][now] = ++ctrie;
			now = trie[f[i] >> j & 1][now];
		}
	}
	LL val = dfs(1, 1, 63);
	printf("%lld\n", mx + val);
	return 0;
}