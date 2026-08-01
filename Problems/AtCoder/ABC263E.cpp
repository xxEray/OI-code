#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;

int n;

int a[N];

LL f[N], sum[N];

LL inv[N];
void preprocess(int mx) {
	inv[1] = 1;
	for(int i = 2; i <= mx; i++) inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) scanf("%d", &a[i]);
	preprocess(n);
	f[n] = 0;
	for(int i = n - 1; i >= 1; i--) {
		f[i] = (sum[i + 1] - sum[i + a[i] + 1] + MOD) % MOD * inv[a[i] + 1] % MOD;
		// for(int j = i + 1; j <= i + a[i]; j++) (f[i] += f[j] * inv[a[i] + 1] % MOD) %= MOD;
		// f[i] = f'[i] + 1/(a[i]+1)*(f[i]+1)
		f[i] = (f[i] + 1) * (a[i] + 1) % MOD * inv[a[i]] % MOD;
		sum[i] = (sum[i + 1] + f[i]) % MOD;
	}
	printf("%lld\n", f[1]);
	return 0;
}