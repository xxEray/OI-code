#include <bits/stdc++.h>

typedef long long LL;

const int N = 5000 + 5;

int n;
struct Node { int t, x; } a[N];
bool operator<(Node x, Node y) { return x.t < y.t; }

bool f[N][N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].t, &a[i].x);
	a[0].x = 0, a[0].t = 0;
	f[0][0] = true;
	for(int i = 0; i <= n; i++) {
		if(std::abs(a[i].x - a[i + 2].x) <= a[i + 2].t - a[i].t) {
			int l = std::max(a[i + 2].x - (a[i + 2].t - a[i].t), std::min(a[i].x, a[i + 2].x) - (a[i + 2].t - a[i].t - std::abs(a[i].x - a[i + 2].x)) / 2);
			int r = std::min(a[i + 2].x + (a[i + 2].t - a[i].t), std::max(a[i].x, a[i + 2].x) + (a[i + 2].t - a[i].t - std::abs(a[i].x - a[i + 2].x)) / 2);
			for(int j = i + 3; j <= n; j++) if(l <= a[j].x && a[j].x <= r) f[i + 2][j] |= f[i][i + 1];
			f[i + 2][0] |= f[i][i + 1];
		}
		{
			int tt = a[i].t + std::abs(a[i + 1].x - a[i].x);
			for(int j = i + 2; j <= n; j++)
				if(tt + std::abs(a[j].x - a[j - 1].x) <= a[j].t - a[i].t) {
					int l = std::max(a[j].x - (a[j].t - tt), std::min(a[j - 1].x, a[j].x) - (a[j].t - tt - std::abs(a[j - 1].x - a[j].x)) / 2);
					int r = std::min(a[j].x + (a[j].t - tt), std::max(a[j - 1].x, a[j].x) + (a[j].t - tt - std::abs(a[j - 1].x - a[j].x)) / 2);
					for(int k = j + 1; k <= n; k++) if(l <= a[k].x && a[k].x <= r) f[j][k] |= f[i][0];
					f[j][0] |= f[i][0];
					tt += std::abs(a[j - 1].x - a[j].x), tt = std::max(tt, a[j - 1].t);
				} else break;
		}
		if(std::abs(a[i].x - a[i + 1].x) <= a[i + 1].t - a[i].t) {
			int l = std::min(a[i].x, a[i + 1].x) - (a[i + 1].t - a[i].t - std::abs(a[i].x - a[i + 1].x)) / 2;
			int r = std::max(a[i].x, a[i + 1].x) + (a[i + 1].t - a[i].t - std::abs(a[i].x - a[i + 1].x)) / 2;
			for(int j = i + 2; j <= n; j++) if(l <= a[j].x && a[j].x <= r) f[i + 1][j] |= f[i][0];
			for(int j = i + 2; j <= n; j++) f[i + 1][j] |= f[i][j];
			f[i + 1][0] |= f[i][0];
		}
	}
	// for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) if(f[i][j]) printf("(%d, %d)\n", i, j);
	puts(f[n - 1][n] || f[n][0] ? "YES" : "NO");
	return 0;
} /*
3
3 3
7 1
8 4
*/