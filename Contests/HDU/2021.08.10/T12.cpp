#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 998244353;

char s[N];
int n;

std::vector<int> tot[30];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		for(int i = 0; i < 26; i++) tot[i].clear(), tot[i].push_back(0);
		scanf("%s", s + 1);
		n = strlen(s + 1);
		for(int i = 1; i <= n; i++) tot[s[i] - 'a'].push_back(i);
		LL ans = 0;
		for(int i = 0; i < 26; i++) {
			LL s1 = 0, s2 = 0;
			int r = (int)tot[i].size() - 1;
			for(int j = 1; j <= r; j++) (s1 += (LL)(2 * r + 1 - 2 * j) * tot[i][j] % MOD) %= MOD, (s2 += tot[i][j]) %= MOD;
			(ans += ((n + 1) * s1 % MOD - s2 * s2 % MOD + MOD) % MOD) %= MOD;
		}
		printf("%lld\n", ans);
	}
	return 0;
}