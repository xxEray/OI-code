#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e7 + 5;
const LL MOD = 1e9 + 7;

int mx, Q;

int t[N], op[N];

bool isprm[N];
int prime[N], p;

LL inv[1005], ans[N];

int main() {
// #ifndef DEBUG
// 	freopen("lcm.in", "r", stdin);
// 	freopen("lcm.out", "w", stdout);
// #endif
	for(int i = 2; i <= 20000000; i++) isprm[i] = true;
	// for(int i = 2; i <= 20000000; i++) for(int j = i + i; j <= 20000000; j += i) isprm[j] = false;
	for(int i = 2; i <= 20000000; i++) {
		if(isprm[i]) prime[++p] = i, op[i] = i, t[i] = 2;
		for(int j = 1; j <= p; j++) {
			if((LL)i * prime[j] > 20000000) break;
			isprm[i * prime[j]] = false;
			if(op[i] == prime[j]) op[i * prime[j]] = prime[j], t[i * prime[j]] = t[i] + 1;
			else op[i * prime[j]] = 0, t[i * prime[j]] = 0;
			if(i % prime[j] == 0) break;
		}
	}
	// for(LL i = 2; i <= 20000000; i++) if(isprm[i]) {
	// 	int cnt = 1;
	// 	for(LL j = i; j <= 20000000; j *= i)
	// 		t[j] = ++cnt;
	// }
	inv[1] = 1;
	for(int i = 2; i <= 1000; i++) inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
	ans[1] = 1;
	for(int i = 2; i <= 20000000; i++) {
		ans[i] = ans[i - 1];
		if(t[i]) (ans[i] *= inv[t[i] - 1] * t[i] % MOD) %= MOD;
	}
	// for(int i = 1; i <= 10; i++) printf("ans[%d] = %lld\n", i, ans[i]);
	unsigned int seed, a, b, c;
	scanf("%d%d%u%u%u%u", &mx, &Q, &seed, &a, &b, &c);
	LL out = 0;
	for(int i = 1; i <= Q; i++) {
		int n = seed % mx + 1;
		seed = (seed ^ a) * b + c;
		// printf("n = %d, ans = %lld\n", n, ans[n]);
		out ^= ans[n];
	}
	printf("%lld\n", out);
	return 0;
}