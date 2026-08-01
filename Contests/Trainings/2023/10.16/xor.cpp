#include <bits/stdc++.h>

typedef long long LL;

const int N = 25;
const int MAXS = (1 << 18) + 5;

int n;
LL a[N];

LL sum[MAXS];
int f[MAXS];

int main() {
#ifndef DEBUG
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = n + 1; i >= 1; i--) a[i] ^= a[i - 1];
	n++;
//	for(int i = 1; i <= n; i++) printf("%lld ", a[i]);
	int U = (1 << n) - 1;
	for(int s = 0; s <= U; s++)
		for(int i = 1; i <= n; i++) if(s >> (i - 1) & 1)
			sum[s] ^= a[i];
	for(int s = 0; s <= U; s++)
		for(int t = s; t; t = (t - 1) & s) if(!sum[t])
			f[s] = std::max(f[s], f[s ^ t] + 1);
	printf("%d\n", n - f[U]);
	return 0;
}
