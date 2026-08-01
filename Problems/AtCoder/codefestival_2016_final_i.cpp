#include <cstdio>
#include <algorithm>
#include <bitset>

typedef long long LL;

const int N = 200 + 5;
const LL MOD = 1e9 + 7;

const int fac[5] = {1, 1, 2, 6, 24};

int n, m;
char a[N][N];

int hash(int x, int y) { return (x - 1) * m + y; }

std::bitset<N * N> g[N * N], available;

void insert(std::bitset<N * N> x) {
	for(int i = n * m; i >= 0; i--) if(x[i]) {
		if(g[i].any()) x ^= g[i];
		else { g[i] = x; break; }
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) { char str[2]; scanf("%1s", str); a[i][j] = str[0] - 'a'; }
	LL ans = 1;
	for(int i = 1; i <= n / 2; i++) for(int j = 1; j <= m / 2; j++) {
		int cnt[30] = {};
		cnt[a[i][j]]++, cnt[a[i][m - j + 1]]++, cnt[a[n - i + 1][j]]++, cnt[a[n - i + 1][m - j + 1]]++;
		int v = 24;
		for(int k = 0; k < 26; k++) v /= fac[cnt[k]];
		if(v == 24) available[hash(i, j)] = 1, (ans *= 12) %= MOD;
		else (ans *= v) %= MOD;
	}
	for(int i = 1; i <= n / 2; i++) {
		std::bitset<N * N> x;
		for(int j = 1; j <= m / 2; j++) x[hash(i, j)] = 1;
		x &= available;
		insert(x);
	}
	for(int j = 1; j <= m / 2; j++) {
		std::bitset<N * N> x;
		for(int i = 1; i <= n / 2; i++) x[hash(i, j)] = 1;
		x &= available;
		insert(x);
	}
	int cnt = 0;
	for(int i = n * m; i >= 0; i--) cnt += g[i].any();
	while(cnt--) (ans *= 2) %= MOD;
	if(n & 1) {
		bool flag = true;
		for(int j = 1; j <= m / 2; j++) flag &= a[n / 2 + 1][j] == a[n / 2 + 1][m - j + 1];
		(ans *= flag ? 1 : 2) %= MOD;
	}
	if(m & 1) {
		bool flag = true;
		for(int i = 1; i <= n / 2; i++) flag &= a[i][m / 2 + 1] == a[n - i + 1][m / 2 + 1];
		(ans *= flag ? 1 : 2) %= MOD;
	}
	printf("%lld\n", ans);
	return 0;
} /*
2 4
abcd
efgh
*/