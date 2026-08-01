#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;
const LL phiMOD = MOD - 1;

int n, m;

LL qpow(LL x, LL y, LL mod) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }

bool isprm[N];
std::vector<int> prime;
int mu[N];
void discrete(int mx) {
	for(int i = 2; i <= mx; i++) isprm[i] = true;
	mu[1] = 1;
	for(int i = 2; i <= mx; i++) {
		if(isprm[i]) prime.push_back(i), mu[i] = -1;
		for(int p : prime) {
			if((LL)p * i > mx) break;
			isprm[p * i] = false;
			if(i % p == 0) {
				mu[p * i] = 0;
				break;
			}
			mu[p * i] = mu[p] * mu[i];
		}
	}
}

LL g[N], preg[N], power[N];

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }
LL lcm(int x, int y) { return x / gcd(x, y) * (LL)y; }

int main() {
#ifndef DEBUG
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	discrete(m);
	for(int i = 1; i <= m; i++) for(int j = 1; j <= m / i; j++) (g[i * j] += i * mu[j] + phiMOD) %= phiMOD;
	for(int i = 1; i <= m; i++) preg[i] = (preg[i - 1] + g[i]) % phiMOD;
	for(int i = 0; i <= m; i++) power[i] = qpow(i, n, phiMOD);
	// printf("mu: "); for(int i = 1; i <= m; i++) printf("%d ", mu[i]); puts("");
	// printf("g: "); for(int i = 1; i <= m; i++) printf("%lld ", g[i]); puts("");
	LL ans = 1;
	for(int pr : prime) for(LL p = pr; p <= m; p *= pr) {
		LL ret = 0;
		for(int q = 1, qr; q <= m; q = qr + 1) {
			qr = m / (m / q);
			(ret += (preg[qr] - preg[q - 1] + phiMOD) % phiMOD * (power[m / q] - power[m / q - m / ((LL)p * q)] + phiMOD) % phiMOD) %= phiMOD;
		}
		for(int q = pr; q <= m; q += pr) (ret += g[q] * power[m / q - m / ((LL)p * q)] % phiMOD + phiMOD - g[q] * power[m / q - m / lcm(p, q)] % phiMOD) %= phiMOD;
		(ans *= qpow(pr, ret, MOD)) %= MOD;
	}
	printf("%lld\n", ans);
	return 0;
}