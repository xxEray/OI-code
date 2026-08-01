#include <bits/stdc++.h>

typedef long long LL;

const int N = 5000 + 5;
const int M = 1e6 + 5;
const LL MOD = 1e9 + 7;

int n, m;

int jl[N], jr[N], kl[N], kr[N];
int nl[N], nr[N];
LL f[N][N], sumr[N], sumc[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) jl[i] = 0, jr[i] = i - 1, kl[i] = 0, kr[i] = std::max(i - 2, 0);
		for(int i = 1; i <= m; i++) {
			int l, r, x;
			scanf("%d%d%d", &l, &r, &x);
			if(x == 1) jr[r] = std::min(jr[r], l - 1), kr[r] = std::min(kr[r], std::max(l - 2, 0));
			else if(x == 2) jl[r] = std::max(jl[r], l), kr[r] = std::min(kr[r], l - 1);
			else if(x == 3) kl[r] = std::max(kl[r], l);
		}
		bool flag = true;
		for(int i = 1; i <= n; i++) if(jl[i] > jr[i] || kl[i] > kr[i]) { puts("0"); flag = false; break; }
		if(!flag) continue;
		for(int j = 0; j <= n; j++) for(int k = 0; k <= n; k++) f[j][k] = 0;
		for(int i = 0; i <= n; i++) sumr[i] = sumc[i] = 0, nl[i] = 0, nr[i] = n;
		f[0][0] = 1, sumr[0] = sumc[0] = 1;
		auto reset = [&](int i, int j) { (sumr[i] += MOD - f[i][j]) %= MOD, (sumc[j] += MOD - f[i][j]) %= MOD, f[i][j] = 0; };
		for(int i = 1; i <= n; i++) {
			// f[i - 1][j][k] -> f[i][i - 1][k]
			for(int k = 0; k <= i - 3; k++) {
				LL val = (sumc[k] - (k == 0 ? f[0][0] : 0LL) + MOD) % MOD;
				(f[i - 1][k] += val) %= MOD, (sumr[i - 1] += val) %= MOD, (sumc[k] += val) %= MOD;
			}
			// f[i - 1][j][k] -> f[i][i - 1][j]
			for(int j = 0; j <= i - 2; j++) {
				LL val = sumr[j];
				(f[i - 1][j] += val) %= MOD, (sumr[i - 1] += val) %= MOD, (sumc[j] += val) %= MOD;
			}
			// remain (jl[i]..jr[i], kl[i]..kr[i])
			for(int j = 0; j < jl[i]; j++) while(nl[j] <= nr[j]) reset(j, nl[j]++);
			for(int j = jr[i] + 1; j <= i - 1; j++) while(nl[j] <= nr[j]) reset(j, nl[j]++);
			for(int j = jl[i]; j <= jr[i]; j++) {
				while(nl[j] <= nr[j] && nl[j] < kl[i]) reset(j, nl[j]++);
				while(nr[j] >= nl[j] && nr[j] > kr[i]) reset(j, nr[j]--);
			}
			// printf("i = %d: j[%d, %d], k[%d, %d]\n", i, jl[i], jr[i], kl[i], kr[i]);
			// for(int j = 0; j < i; j++) for(int k = 0; k < std::max(j, 1); k++)
			// 	if(f[j][k]) printf("f[%d][%d][%d] = %lld\n", i, j, k, f[j][k]);
		}
		LL ans = 0;
		for(int j = jl[n]; j <= jr[n]; j++) for(int k = kl[n]; k <= kr[n]; k++)
			if(!j && !k) (ans += f[j][k] * 3) %= MOD;
			else (ans += f[j][k] * 6) %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
} /*
4
1 0
2 0
3 0
5 2
1 3 3
4 5 1
*/