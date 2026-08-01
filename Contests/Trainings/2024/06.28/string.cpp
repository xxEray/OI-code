#include <bits/stdc++.h>

#ifdef DEBUG
#define msg(...) fprintf(stderr, __VA_ARGS__)
#else
#define msg(...) ((void)0)
#endif

typedef long long LL;

const int N = 3e5 + 5;
const LL MOD = 998244353;

int n, K;
char s[N];

int nxt[N][29], prv[N][29];
LL f[N], g[N];

namespace Solve_K1 {
	int last[29];
	void main() {
		scanf("%d%s", &n, s + 1);
		for(int i = 1; i <= n; i++) s[i] -= 'a';
		for(int i = 0; i < 26; i++) last[i] = n + 1;
		for(int i = n; i >= 0; i--) {
			for(int j = 0; j < 26; j++) nxt[i][j] = last[j];
			last[s[i]] = i;
		}
		for(int i = 1; i <= n + 1; i++) f[i] = 0;
		for(int j = 0; j < 26; j++) f[nxt[0][j]] = 1;
		for(int i = 1; i < n; i++)
			for(int j = 0; j < 26; j++)
				if(nxt[i][j] <= nxt[i][s[i]])
					(f[nxt[i][j]] += f[i]) %= MOD;
		// for(int i = 1; i <= n; i++) printf("f[%d] = %lld\n", i, f[i]);
		LL ans = 0;
		for(int i = 1; i <= n; i++) if(nxt[i][s[i]] == n + 1) (ans += f[i]) %= MOD;
		printf("%lld\n", ans);
	}
}

namespace Solve_K2 {
	int last[29];
	void main() {
		scanf("%d%s", &n, s + 1);
		for(int i = 1; i <= n; i++) s[i] -= 'a';
		for(int i = 0; i < 26; i++) last[i] = n + 1;
		for(int i = n; i >= 0; i--) {
			for(int j = 0; j < 26; j++) nxt[i][j] = last[j];
			last[s[i]] = i;
		}
		f[0] = 1;
		for(int i = 1; i <= n + 1; i++) f[i] = 0;
		for(int j = 0; j < 26; j++) f[nxt[0][j]] = 1;
		for(int i = 1; i < n; i++)
			for(int j = 0; j < 26; j++)
				if(nxt[i][j] <= nxt[i][s[i]])
					(f[nxt[i][j]] += f[i]) %= MOD;
		for(int i = 0; i < 26; i++) last[i] = 0;
		for(int i = 1; i <= n + 1; i++) {
			for(int j = 0; j < 26; j++) prv[i][j] = last[j];
			last[s[i]] = i;
		}
		g[n + 1] = 1;
		for(int i = 0; i <= n; i++) g[i] = 0;
		for(int j = 0; j < 26; j++) g[prv[n + 1][j]] = 1;
		for(int i = n; i > 1; i--)
			for(int j = 0; j < 26; j++)
				if(prv[i][j] >= prv[i][s[i]])
					(g[prv[i][j]] += g[i]) %= MOD;
		// for(int i = 1; i <= n; i++) printf("f[%d] = %lld\n", i, f[i]);
		LL ans = 0;
		for(int j = 0; j < 26; j++)
			if(nxt[0][j] != n + 1 && nxt[nxt[0][j]][j] != n + 1 && nxt[nxt[nxt[0][j]][j]][j] == n + 1)
				(ans += 1) %= MOD; // , msg("single (j=%d)\n", j);
		for(int i = n; i >= 1; i--) for(int j = 0; j < 26; j++) {
			if(j == s[i] || prv[i][j] == 0 || prv[prv[i][j]][j] == 0) continue;
			int p = prv[i][j], q = prv[p][j];
			if(nxt[q][s[i]] != i) continue;
			if(prv[q][j] == 0) (ans += g[i]) %= MOD; // , msg("begin -> %d (j=%d)\n", i, j);
		}
		for(int i = 1; i <= n; i++) for(int j = 0; j < 26; j++) {
			if(j == s[i] || nxt[i][j] == n + 1 || nxt[nxt[i][j]][j] == n + 1) continue;
			int p = nxt[i][j], q = nxt[p][j];
			if(prv[q][s[i]] != i) continue;
			if(nxt[q][j] == n + 1) (ans += f[i]) %= MOD; // , msg("%d -> end (j=%d)\n", i, j);
			for(int k = 0; k < 26; k++)
				if(nxt[p][k] != n + 1 && nxt[p][k] < nxt[q][j] && nxt[p][k] == nxt[q][k] && prv[nxt[q][k]][j] == q)
					(ans += f[i] * g[nxt[p][k]]) %= MOD; // , msg("%d -> %d (j=%d, k=%d)\n", i, nxt[p][k], j, k);
		}
		printf("%lld\n", ans);
	}
}

int main() {
// #ifndef DEBUG
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
// #endif
	int T; scanf("%d%d", &T, &K);
	if(K == 1) {
		while(T--) Solve_K1::main();
	} else {
		while(T--) Solve_K2::main();
	}
	return 0;
} /*
1 2
35
weloveuweloveuweloveuweloveuweloveu
*/