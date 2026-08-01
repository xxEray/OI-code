#include <bits/stdc++.h>

const int N = 5000 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N], b[N];

int cnt[N];

int w[N][N], w2[N][N];
int f[N][N], g[N][N];
int h[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for(int i = 0; i <= n; i++) {
		for(int j = 1; j <= n; j++) cnt[j] = 0;
		int sum = 0;
		for(int j = 1; j < i; j++) (++cnt[a[j]]) %= 3, sum += (cnt[a[j]] % 3 ? 1 : -2);
		if(i) (++cnt[a[i]]) %= 3, sum += (cnt[a[i]] % 3 ? 1 : -2);
		w[i][0] = sum;
		for(int j = 1; j <= n; j++) (++cnt[b[j]]) %= 3, sum += (cnt[b[j]] % 3 ? 1 : -2), w[i][j] = sum;
	}
	for(int i = 1; i < n; i++) {
		for(int j = 1; j <= n; j++) cnt[j] = 0;
		int sum = 0;
		for(int j = 1; j < i; j++) (++cnt[a[j]]) %= 3, sum += (cnt[a[j]] % 3 ? 1 : -2);
		(++cnt[a[i + 1]]) %= 3, sum += (cnt[a[i + 1]] % 3 ? 1 : -2), w2[i][0] = sum;
		for(int j = 1; j <= n; j++) (++cnt[b[j]]) %= 3, sum += (cnt[b[j]] % 3 ? 1 : -2), w2[i][j] = sum;
	}
	// puts("w:"); for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) printf("%d%c", w[i][j], " \n"[j == n]);
	// puts("w2:"); for(int i = 1; i < n; i++) for(int j = 0; j <= n; j++) printf("%d%c", w2[i][j], " \n"[j == n]);
	memset(f, 0x3f, sizeof(f)), memset(g, 0x3f, sizeof(g));
	f[0][0] = w[0][0];
	for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) {
		if(i) f[i][j] = std::min(f[i][j], std::max(f[i - 1][j], w[i][j]));
		if(j) f[i][j] = std::min(f[i][j], std::max(f[i][j - 1], w[i][j]));
	}
	g[n][n] = w[n][n];
	for(int i = n; i >= 0; i--) for(int j = n; j >= 0; j--) {
		if(i < n) g[i][j] = std::min(g[i][j], std::max(g[i + 1][j], w[i][j]));
		if(j < n) g[i][j] = std::min(g[i][j], std::max(g[i][j + 1], w[i][j]));
	}
	for(int i = 1; i < n; i++) {
		for(int j = 0; j <= n; j++) h[j] = INF;
		for(int j = 0; j <= n; j++) {
			if(j) h[j] = std::min(h[j], std::max(h[j - 1], w2[i][j]));
			h[j] = std::min(h[j], std::max(f[i - 1][j], w2[i][j]));
		}
		int ret = INF;
		for(int j = 0; j <= n; j++) ret = std::min(ret, std::max(h[j], g[i + 1][j]));
		printf("%d\n", ret + 1);
	}
	return 0;
} /*
9
3 7 3 7 3 8 7 7 8
2 7 7 8 2 3 2 3 3
*/