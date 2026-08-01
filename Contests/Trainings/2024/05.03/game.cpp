#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const int MAXV = 2205;
const LL MOD = 1e9 + 7;

const int power3[] = {1, 3, 9, 27, 81, 243, 729, 2187};

int n, K;

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
void get_factorial() {
	fac[0] = 1;
	for(int i = 1; i <= 50000; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[50000] = inv(fac[50000]);
	for(int i = 50000; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

std::vector<int> prime;
bool isprm[N];
void sieve() {
	for(int i = 2; i <= 50000; i++) isprm[i] = true;
	for(int i = 2; i <= 50000; i++) {
		if(isprm[i]) prime.emplace_back(i);
		for(int p : prime) {
			if(p * i > 50000) break;
			isprm[p * i] = false;
			if(i % p == 0) break;
		}
	}
}

int xor3[MAXV][MAXV];
int xor3of(int x, int y) {
	int z = 0;
	for(int i = 0; i <= 5; i++) z += power3[i] * ((x + y) % 3), x /= 3, y /= 3;
	return z;
}

struct Poly {
	LL a[MAXV];
	Poly() { memset(a, 0, sizeof(a)); }
};
Poly operator*(const Poly &x, const Poly &y) {
	Poly z;
	for(int i = 0; i < 2187; i++) for(int j = 0; j < 2187; j++) (z.a[xor3[i][j]] += x.a[i] * y.a[j]) %= MOD;
	return z;
}
Poly qpow(Poly x, int y) { Poly ret; ret.a[0] = 1; while(true) { if(y & 1) ret = ret * x; if(!(y >>= 1)) return ret; x = x * x; } }

int main() {
#ifndef DEBUG
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
#endif
	sieve(), get_factorial();
	scanf("%d%d", &n, &K);
	for(int i = 0; i < 2187; i++) for(int j = 0; j < 2187; j++) xor3[i][j] = xor3of(i, j);
	Poly ans;
	for(int i = 1; i <= n; i++) {
		int prod = 1, x;
		scanf("%d", &x);
		for(int p : prime) {
			if(p * p > x) break;
			if(x % p == 0) {
				int cnt = 0;
				while(x % p == 0) cnt++, x /= p;
				prod *= cnt + 1;
			}
		}
		if(x > 1) prod *= 2;
		ans.a[prod]++;
	}
	// printf("a: "); for(int i = 1; i <= n; i++) printf("%d ", a[i]); puts("");
	ans = qpow(ans, K);
	printf("%lld\n", (qpow(n, K) - ans.a[0] % MOD + MOD) % MOD);
	return 0;
} /*
1 1
1
*/