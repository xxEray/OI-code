#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 400 + 5;
const LL MOD = 998244353;

int n;
int a[N][N];
int cnt[N * N];
LL f[N][N];
std::vector<std::pair<int, int>> appear[N * N];

LL fac[2 * N], invfac[2 * N];
LL C(LL x, LL y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
void preprocess() {
	fac[0] = 1;
	for(int i = 1; i <= 2 * n; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[2 * n] = qpow(fac[2 * n], MOD - 2);
	for(int i = 2 * n; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int main() {
	scanf("%d", &n);
	preprocess();
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) scanf("%d", &a[i][j]), cnt[a[i][j]]++;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(cnt[a[i][j]] <= n) appear[a[i][j]].push_back({i, j});
	LL ans = 0;
	// cnt > n
	for(int cl = 1; cl <= n * n; cl++) if(cnt[cl] > n) {
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) f[i][j] = (f[i][j - 1] + f[i - 1][j] + (a[i][j] == cl)) % MOD;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(a[i][j] == cl) (ans += f[i][j]) %= MOD;
	}
	// cnt <= n
	for(int cl = 1; cl <= n * n; cl++) if(cnt[cl] <= n) {
		int sz = appear[cl].size();
		for(int i = 0; i < sz; i++) for(int j = 0; j < sz; j++) {
			auto p1 = appear[cl][i], p2 = appear[cl][j];
			if(p1.first <= p2.first && p1.second <= p2.second)
				(ans += C(p2.first - p1.first + p2.second - p1.second, p2.first - p1.first)) %= MOD;
		}
	}
	printf("%lld\n", ans);
	return 0;
} /*
3
1 2 3
2 3 2
3 2 1
*/