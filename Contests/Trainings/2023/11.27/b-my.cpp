#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;
const LL MOD = 1e9 + 7;

std::vector<std::pair<LL, int>> factor;
LL K, K2;
int Q;
std::vector<LL> q;

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL getinv(LL x) { return qpow(x, MOD - 2); }
LL inv[N];
LL fac[N], invfac[N];
LL C(int x, int y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = getinv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
	inv[1] = 1;
	for(int i = 2; i <= mx; i++) inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
}

namespace Problem1 {
	void main() {
		LL n = 1;
		for(auto [p, c] : factor) (n *= qpow(p, c)) %= MOD;
		printf("%lld\n", qpow(n, 2 * K2 % (MOD - 1)));
	}
}

namespace Problem2 {
	// LL ans = 0;
	// void dfs(int id, LL prod, LL val) {
	// 	if(id == (int)factor.size()) {
	// 		ans += prod;
	// 		if(ans >= MOD) ans -= MOD;
	// 		return;
	// 	}
	// 	LL prod2 = 1;
	// 	for(int i = 0; i <= factor[id].second; i++) {
	// 		if(i) (prod2 *= (K + i - 1) * inv[i] % MOD) %= MOD;
	// 		dfs(id + 1, prod * prod2 % MOD, val * );
	// 	}
	// }
	// void main() {
	// 	LL phi = 1;
	// 	for(auto [p, c] : factor) (phi *= qpow(p, c - 1)) %= MOD;
	// 	dfs(0, 1, 1);
	// 	printf("%lld\n", ans);
	// }
	const int N = 1000 + 5;
	LL n = 1;
	bool flag = true;
	struct Polynomial { LL a[N]; } f;
	Polynomial operator*(const Polynomial &x, const Polynomial &y) {
		Polynomial z;
		__builtin_memset(z.a, 0, sizeof(LL) * (n + 3));
		for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) (z.a[i + j - (i + j >= n) * n] += x.a[i] * y.a[j] % MOD) %= MOD;
		return z;
	}
	void main() {
		for(auto [p, c] : factor)
			if(pow(p, c) <= 1e5 && n * qpow(p, c) <= 1000) n *= qpow(p, c);
			else flag = false;
		if(flag) {
			Polynomial ret, x;
			__builtin_memset(ret.a, 0, sizeof(LL) * (n + 3));
			__builtin_memset(x.a, 0, sizeof(LL) * (n + 3));
			ret.a[0] = 1;
			for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) x.a[i * j % n]++;
			printf("f: "); for(int i = 0; i < n; i++) printf("%lld ", x.a[i]); puts("");
			LL y = K2;
			while(true) {
				if(y & 1) ret = ret * x;
				if(!(y >>= 1)) break;
				x = x * x;
			}
			f = ret;
			LL ans = 0;
			for(int i = 0; i < n; i++) (ans += f.a[i] * qpow(3, i) % MOD) %= MOD;
			printf("f: "); for(int i = 0; i < n; i++) printf("%lld ", f.a[i]); puts("");
			printf("%lld\n", ans);
		} else puts("0");
	}
}

namespace Problem3 {
	void main() {
		if(::Problem2::flag) {
			for(int x : q) printf("%lld\n", ::Problem2::f.a[x]);
		} else {
			for(int i = 1; i <= Q; i++) puts("0");
		}
	}
}

char str[N];

int main() {
#ifndef DEBUG
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	get_factorial(3e5);
	int cnt;
	scanf("%d", &cnt);
	for(int i = 1; i <= cnt; i++) { LL p; int c; scanf("%lld%d", &p, &c); factor.emplace_back(p, c); }
	scanf("%s", str + 1);
	int len = strlen(str + 1);
	for(int i = 1; i <= len; i++) {
		K = (K * 10 + str[i] - '0') % MOD;
		K2 = (K2 * 10 + str[i] - '0') % (MOD - 1);
	}
	scanf("%d", &Q);
	for(int i = 1; i <= Q; i++) { LL x; scanf("%lld", &x); q.emplace_back(x); }
	Problem1::main();
	Problem2::main();
	Problem3::main();
	return 0;
}