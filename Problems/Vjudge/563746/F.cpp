#include <bits/stdc++.h>

const int N = 1e3 + 5;

int n;
double p[N][N];

double f[N], g[N], h[N];

bool done[N];
void trans(int j, int i) { g[i] += p[i][j] * f[j] * h[i], h[i] *= 1 - p[i][j], f[i] = g[i] / (1 - h[i]); }

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) { int x; scanf("%d", &x); p[i][j] = x / 100.0; }
	for(int i = 1; i <= n; i++) f[i] = g[i] = h[i] = 1;
	done[n] = true, f[n] = 0;
	for(int i = 1; i <= n; i++) if(!done[i]) trans(n, i);
	for(int _ = 2; _ <= n; _++) {
		int now = 0;
		double val = 1e18;
		for(int i = 1; i <= n; i++) if(!done[i] && f[i] < val) now = i, val = f[i];
		done[now] = true;
		for(int i = 1; i <= n; i++) if(!done[i]) trans(now, i);
	}
	printf("%.6lf\n", f[1]);
	return 0;
}