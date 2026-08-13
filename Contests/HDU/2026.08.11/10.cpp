#include <bits/stdc++.h>
#ifdef DEBUG
#include "stl_printer.h"
#endif

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 998244353;

int n;
char s[N];

int sum[N];

void mod(LL &x) { if(x >= MOD) x -= MOD; }

LL f[N];
int nxt[N], last[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		bool flag = true;
		for(int i = 2; i <= n; i++) flag &= (s[i] != s[i - 1]);
		if(flag) { puts("1"); continue; }
		for(int i = 0; i <= n + 1; i++) last[i] = 0;
		sum[n + 1] = 0;
		for(int i = n; i >= 1; i--) sum[i] = sum[i + 1] + (s[i] == '1' ? 1 : -1);
		int mn = *std::min_element(sum + 1, sum + n + 2);
		for(int i = 1; i <= n + 1; i++) sum[i] -= mn - 1;
		for(int i = n, j = n + 1; i >= 1; i--) {
			if(i <= n - 1 && s[i] == s[i + 1]) {
				while(j >= i + 2) last[sum[j]] = j, j--;
			}
			if(s[i] == '1') nxt[i - 1] = last[sum[i] + 1] - 1;
			else nxt[i - 1] = last[sum[i] - 1] - 1;
		}
		// printf("sum: %s\n", tostring(sum + 1, sum + n + 2).c_str());
		// printf("last: %s\n", tostring(last + 1, last + n + 2).c_str());
		f[0] = 1;
		for(int i = 1; i <= n; i++) f[i] = 0;
		for(int i = 0; i < n; i++) {
			mod(f[i + 1] += f[i]);
			if(nxt[i] > 0) mod(f[nxt[i]] += f[i]);
		}
		// for(int i = 0; i <= n; i++) printf("[%d]: nxt=%d, f=%lld\n", i, nxt[i], f[i]);
		LL ans = 0;
		for(int i = 1; i <= n; i++) if(sum[i + 1] == sum[n + 1]) ans += f[i];
		printf("%lld\n", ans % MOD);
	}
	return 0;
} /*
1
011
*/