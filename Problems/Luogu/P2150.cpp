#include <bits/stdc++.h>

typedef long long LL;

const int N = 500 + 5;
const int MAXS = (1 << 8) + 5;

const int prime[] = {2, 3, 5, 7, 11, 13, 17, 19};

int n;
LL mod;

struct Node { int val, mask, factor; } a[N];

LL f[3][2][MAXS][MAXS];

int main() {
	scanf("%d%lld", &n, &mod);
	for(int i = 1; i <= n; i++) {
		a[i].val = i;
		int x = i;
		for(int j = 0; j < 8; j++) if(x % prime[j] == 0) {
			a[i].mask |= (1 << j);
			while(x % prime[j] == 0) x /= prime[j];
		}
		a[i].factor = x;
	}
	std::sort(a + 2, a + n + 1, [&](Node x, Node y) { return x.factor < y.factor; });
	int U = (1 << 8) - 1;
	f[0][1][0][0] = 1;
	for(int i = 2; i <= n; i++) {
		for(int k = 0; k <= 2; k++)
			for(int s = 0; s <= U; s++)
				for(int t = ~s & U; ; t = (t - 1) & (~s & U)) {
					f[k][i & 1][s][t] = 0;
					if(!t) break;
				}
		for(int s = 0; s <= U; s++)
			for(int t = ~s & U; ; t = (t - 1) & (~s & U)) {
				if(i == 2 || a[i].factor == 1 || a[i].factor != a[i - 1].factor) {
					(f[0][i & 1][s][t] += f[0][~i & 1][s][t] + f[1][~i & 1][s][t] + f[2][~i & 1][s][t]) %= mod;
					if(!(t & a[i].mask)) (f[1][i & 1][s | a[i].mask][t] += f[0][~i & 1][s][t] + f[1][~i & 1][s][t] + f[2][~i & 1][s][t]) %= mod;
					if(!(s & a[i].mask)) (f[2][i & 1][s][t | a[i].mask] += f[0][~i & 1][s][t] + f[1][~i & 1][s][t] + f[2][~i & 1][s][t]) %= mod;
				} else {
					(f[0][i & 1][s][t] += f[0][~i & 1][s][t]) %= mod;
					(f[1][i & 1][s][t] += f[1][~i & 1][s][t]) %= mod;
					(f[2][i & 1][s][t] += f[2][~i & 1][s][t]) %= mod;
					if(!(t & a[i].mask)) (f[1][i & 1][s | a[i].mask][t] += f[0][~i & 1][s][t] + f[1][~i & 1][s][t]) %= mod;
					if(!(s & a[i].mask)) (f[2][i & 1][s][t | a[i].mask] += f[0][~i & 1][s][t] + f[2][~i & 1][s][t]) %= mod;
				}
				if(!t) break;
			}
	}
	LL ans = 0;
	for(int s = 0; s <= U; s++)
		for(int t = ~s & U; ; t = (t - 1) & (~s & U)) {
			(ans += f[0][n & 1][s][t] + f[1][n & 1][s][t] + f[2][n & 1][s][t]) %= mod;
			if(!t) break;
		}
	printf("%lld\n", ans);
	return 0;
} /*
5 100000
*/