#include <bits/stdc++.h>

typedef long long LL;

const int N = 5000 + 5;
const LL MOD = 1e9 + 7;

int n, m;
LL V;
LL a[N];

LL f[N][N], g[N][N];

int main() {
	scanf("%d%d%lld", &n, &m, &V);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	f[0][0] = 1, g[0][0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
	return 0;
}