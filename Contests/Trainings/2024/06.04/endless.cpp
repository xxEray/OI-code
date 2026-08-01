#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;

int n;
int a[N];
LL w[N];

int order[N];

int fa[N * 21];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

int hash(int x, int k) { return k * n + x; }
int merge(int x, int y, int k) {
	assert(x + (1 << k) - 1 <= n && y + (1 << k) - 1 <= n);
	if(k == 0) {
		if(find(x) == find(y)) return 0;
		else return merge(x, y), 1;
	}
	if(find(hash(x, k)) == find(hash(y, k))) return 0;
	else return merge(hash(x, k), hash(y, k)), merge(x, y, k - 1) + merge(x + (1 << (k - 1)), y + (1 << (k - 1)), k - 1);
}

int merge_split(int x, int y, int l) {
	int ret = 0;
	for(int k = 0; k < 20; k++) if(l >> k & 1) ret += merge(x, y, k), x += (1 << k), y += (1 << k);
	return ret;
}

struct SuffixArray {
	int s[N];
	int sa[N * 2], rk[N * 2], tot[N * 2], tp[N * 2], ht[N * 2];
	int go[21][N];
	void init() {
		for(int i = n + 1; i <= 2 * n; i++) s[i] = 0;
		for(int i = 1; i <= 2 * n; i++) sa[i] = rk[i] = 0;
		for(int i = 1; i <= 2 * n; i++) tot[i] = tp[i] = ht[i] = 0;
		int m = n;
		auto basic_sort = [&]() {
			for(int i = 0; i <= m; i++) tot[i] = 0;
			for(int i = 1; i <= n; i++) tot[rk[i]]++;
			for(int i = 1; i <= m; i++) tot[i] += tot[i - 1];
			for(int i = n; i >= 1; i--) sa[tot[rk[tp[i]]]--] = tp[i];
		};
		for(int i = 1; i <= n; i++) rk[i] = s[i], tp[i] = i;
		basic_sort();
		for(int i = 1, p; i < n; i <<= 1, m = p) {
			p = 0;
			for(int j = n - i + 1; j <= n; j++) tp[++p] = j;
			for(int j = 1; j <= n; j++) if(sa[j] > i) tp[++p] = sa[j] - i;
			basic_sort();
			for(int j = 1; j <= n; j++) tp[j] = rk[j];
			rk[sa[1]] = p = 1;
			for(int j = 2; j <= n; j++) rk[sa[j]] = (tp[sa[j]] == tp[sa[j - 1]] && tp[sa[j] + i] == tp[sa[j - 1] + i] ? p : ++p);
		}
		for(int i = 1, k = 0; i <= n; i++) {
			if(rk[i] == 1) { ht[rk[i]] = 0; continue; }
			if(k) k--;
			int j = sa[rk[i] - 1];
			while(i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
			ht[rk[i]] = k;
		}
		// if(type) for(int i = 1; i <= n; i++) printf("%d: sa=%d, rk=%d, ht=%d\n", i, sa[i], rk[i], ht[i]);
		for(int i = 1; i <= n; i++) go[0][i] = ht[i];
		for(int j = 1; j < 20; j++)
			for(int i = 1; i + (1 << j) - 1 <= n; i++)
				go[j][i] = std::min(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
	}
	int lcp(int x, int y) {
		assert(x != y);
		x = rk[x], y = rk[y];
		if(x > y) std::swap(x, y);
		int k = 31 ^ __builtin_clz(y - x);
		// if(type) printf("x = %d, y = %d, k = %d\n", x, y, k);
		return std::min(go[k][x + 1], go[k][y - (1 << k) + 1]);
	}
} SA, rSA;

int main() {
#ifndef DEBUG
	freopen("endless.in", "r", stdin);
	freopen("endless.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n / 2; i++) scanf("%lld", &w[i]), order[i] = i;
		for(int i = 1; i <= n * 20; i++) fa[i] = i;
		for(int i = 1; i <= n; i++) SA.s[i] = a[i], rSA.s[i] = a[n - i + 1];
		SA.init(), rSA.init();
		std::sort(order + 1, order + n / 2 + 1, [&](int x, int y) { return w[x] < w[y]; });
		LL ans = 0;
		for(int o = 1; o <= n / 2; o++) {
			int i = order[o];
			for(int j = 1; j + i - 1 <= n; j += i) {
				int l = (j == 1 ? j : std::max(j - rSA.lcp(n - (j + i - 1) + 1, n - (j - 1) + 1), j - i + 1));
				int r = (j + i - 1 == n ? j + i - 1 : std::min(j + i - 1 + SA.lcp(j, j + i), j + 2 * i - 1));
				if(r - l + 1 >= 2 * i) {
					// printf("i = %d, j = %d, l = %d, r = %d\n", i, j, l, r);
					ans += w[i] * merge_split(l, l + i, i);
					ans += w[i] * merge_split(r - 2 * i + 1, r - i + 1, i);
					// printf("ans = %lld\n", ans);
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
} /*
1
8
2 2 5 6 2 5 6 2
5 1 4 4

1
2
1 1
1
*/