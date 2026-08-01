#include <bits/stdc++.h>

typedef long long LL;

const int N = 2.01e5 + 5;
const LL MOD = 998244353;
const int D = 2e5 + 40;

int n;
int a[N], b[N];

int mx[N];
std::vector<LL> f[N], g[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), b[a[i]]++;
	for(int i = 0; i <= D + 1; i++) {
		mx[i + 1] = (mx[i] + b[i]) / 2;
		f[i].resize(mx[i] + 1), g[i].resize(mx[i] + 1);
	}
	g[0][0] = 1;
	for(int i = 0; i <= D; i++) {
		for(int j = mx[i]; j >= 0; j--) (f[i][j] = (j == mx[i] ? 0 : f[i][j + 1]) + g[i][j]) %= MOD;
		for(int j = 0; j <= mx[i]; j++) (g[i + 1][(j + b[i]) / 2] += f[i][j]) %= MOD;
	}
	// for(int i = 0; i <= D; i++)
	// 	for(int j = mx[i]; j >= 0; j--)
	// 		if(f[i][j])
	// 			printf("f[%d][%d] = %lld\n", i, j, f[i][j]);
	printf("%lld\n", f[D][0]);
	return 0;
}