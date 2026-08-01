#include <bits/stdc++.h>

typedef long long LL;

const int N = 15 + 2;
const int MAXS = (1 << 15) + 5;
const LL MOD = 998244353;

int n;
char str[N];

int f[N][MAXS];

int main() {
#ifndef DEBUG
	freopen("inherit.in", "r", stdin);
	freopen("inherit.out", "w", stdout);
#endif
	scanf("%d%s", &n, str + 1);
	bool all_question_mark = true;
	for(int i = 1; i <= n; i++) all_question_mark &= (str[i] == '?');
	if(all_question_mark) {
		LL ans = 1;
		for(int i = 2; i <= n + 1; i++) (ans *= i) %= MOD;
		printf("%lld\n", ans);
		return 0;
	}
	f[1][0] = f[1][1] = 1;
	for(int i = 2; i <= n; i++)
		for(int s = 0; s < (1 << i); s++)
			for(int j = 1; j <= i; j++) if(j == 1 || (s >> (j - 1) & 1) != (s >> (j - 2) & 1)) {
				int t = (s & ((1 << (j - 1)) - 1)) | (s >> j << (j - 1));
				(f[i][s] += f[i - 1][t]) %= MOD;
			}
	LL ans = 0;
	for(int s = 0; s < (1 << n); s++) {
		bool flag = true;
		for(int i = 1; i <= n; i++) if(str[i] != '?') flag &= (str[i] - '0' == (s >> (i - 1) & 1));
		if(flag) (ans += f[n][s]) %= MOD;
	}
	printf("%lld\n", ans);
	return 0;
}