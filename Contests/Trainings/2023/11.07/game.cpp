#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e7 + 5;
const int MOD = 998244353;

int n;
int a[N];

int cnt[N];

void input() {
	int A, B, C, M;
	scanf("%d%d%d%d%d%d", &n, &a[0], &A, &B, &C, &M);
	for(int i = 1; i <= n; i++) a[i] = ((LL)A * a[i - 1] % M * a[i - 1] % M + (LL)B * a[i - 1] % M + C) % M + 1;
	a[0] = 0;
}

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }

struct Equation {
	int k, b;
	Equation() {}
	Equation(int b_) : k(0), b(b_) {}
	Equation(int k_, int b_) : k(k_), b(b_) {}
};
Equation operator+(const Equation &x, const Equation &y) { return Equation(x.k + y.k, x.b + y.b); }
Equation operator-(const Equation &x, const Equation &y) { return Equation(x.k - y.k, x.b - y.b); }

int main() {
#ifndef DEBUG
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
#endif
	int T; scanf("%d", &T);
	while(T--) {
		input();
		for(int i = 1; i <= n; i++) cnt[i] = 0;
		for(int i = 1; i <= n; i++) cnt[a[i]]++;
		Equation prob(0, 0);
		bool flag = false;
		for(int i = 1; i <= n; i++) if(cnt[i]) {
			if(flag) prob = Equation(2, 0) - prob; // prob = 2p - prob
			else flag = true;
			if(cnt[i] == 1) {
				prob = 1 - prob;
			} else {
				prob = Equation(-1, 1) - prob; // prob = 1 - p - prob
			}
			// printf("%d(cnt=%d): prob = %dp%+d\n", i, cnt[i], prob.k, prob.b);
		}
		// printf("prob = %dp%+d\n", prob.k, prob.b);
		// printf("lower = %d/%d\n", lower.p, lower.q);
		// printf("upper = %d/%d\n", upper.p, upper.q);
		printf("%lld\n", ((-prob.b % MOD + MOD) % MOD) * inv((prob.k % MOD + MOD) % MOD) % MOD);
		// double p = std::min(std::max((double)-prob.b / prob.k, (double)lower.p / lower.q), (double)upper.p / upper.q), pr = 0;
		// printf("p = %.5f\n", p);
		// fflush(stdout);
		// flag = false;
		// for(int i = 1; i <= n; i++) if(cnt[i]) {
		// 	if(flag) pr = 2 * p - pr;
		// 	else flag = true;
		// 	// assert(-1e-3 <= pr && pr <= 1 + 1e-3);
		// 	printf("%d: pr = %.3f\n", i, pr);
		// 	if(cnt[i] == 1) pr = 1 - pr;
		// 	else pr = 1 - p - pr;
		// 	// assert(-1e-3 <= pr && pr <= 1 + 1e-3);
		// 	printf("%d: pr = %.3f\n", i, pr);
		// }
	}
	rand();
	return 0;
} /*
1
5 1 0 1 0 4
*/