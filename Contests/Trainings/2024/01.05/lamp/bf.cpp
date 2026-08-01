#include <bits/stdc++.h>

typedef long long LL;

const int N = 5000 + 5;
const LL MOD = 998244353;

int n;
int a[N];

int tin[N];
LL f[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	f[0] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= n; j++) tin[j] = 0;
		for(int j = i, mex = 0; j >= 1; j--) {
			tin[a[j]]++;
			while(tin[mex]) mex++;
			(f[i] += mex * f[j - 1]) %= MOD;
		}
	}
	printf("%lld\n", f[n]);
	return 0;
}