#include <bits/stdc++.h>

typedef long long LL;

const int N = (1 << 25) + 5;
const LL MOD = 1e9 + 7;

int n, m;
int eu[65], ev[65];

int tmp[65];

LL power2[65];

int mapping[65];
LL f[N], g[N];

int sl[N], sr[N];

void solve(int L) {
	fprintf(stderr, "Found! time = %.3f\n", clock() / (double)CLOCKS_PER_SEC);
	// for(int i = 1; i <= n; i++) printf("mapping[%d] = %d\n", i, mapping[i]);
	for(int i = 1; i <= m; i++) eu[i] = mapping[eu[i]], ev[i] = mapping[ev[i]];
	// for(int i = 1; i <= m; i++) printf("%d <-> %d\n", eu[i], ev[i]);
	int R = n - L;
	std::vector<std::pair<int, int>> vct, vctl, vctr;
	for(int i = 1; i <= m; i++) {
		int u = eu[i], v = ev[i];
		if(u > v) std::swap(u, v);
		if(u <= L && v <= L) vctl.emplace_back(u, v);
		else if(u <= L && v > L) vct.emplace_back(u, v);
		else vctr.emplace_back(u, v);
	}
	int Ul = (1 << L) - 1, Ur = (1 << R) - 1;
	for(int s = 0; s <= Ul; s++) {
		int cnt = 0;
		for(auto [u, v] : vctl) if((s >> (u - 1) & 1) && (s >> (v - 1) & 1)) cnt++;
		f[s] = power2[cnt];
	}
	for(int s = 0; s <= Ur; s++) {
		int cnt = 0;
		for(auto [u, v] : vctr) if((s >> (u - 1 - L) & 1) && (s >> (v - 1 - L) & 1)) cnt++;
		g[s] = power2[cnt];
	}
	for(int i = 0; i < L; i++) for(int s = 0; s <= Ul; s++) if(~s >> i & 1) (f[s | (1 << i)] += MOD - f[s]) %= MOD;
	for(int i = 0; i < R; i++) for(int s = 0; s <= Ur; s++) if(~s >> i & 1) (g[s | (1 << i)] += MOD - g[s]) %= MOD;
	for(int i = 0; i < L; i++) for(int s = 0; s <= Ul; s++) if(~s >> i & 1) (f[s] += f[s | (1 << i)]) %= MOD;
	for(int i = 0; i < R; i++) for(int s = 0; s <= Ur; s++) if(~s >> i & 1) (g[s] += g[s | (1 << i)]) %= MOD;
	// for(int s = 0; s <= Ul; s++) printf("f[%d] = %lld\n", s, f[s]);
	// for(int s = 0; s <= Ur; s++) printf("g[%d] = %lld\n", s, g[s]);
	LL ans = 0;
	int Ue = (1 << (int)vct.size()) - 1;
	for(int s = 0; s <= Ue; s++) {
		if(s) {
			int p = __builtin_ctz(s);
			sl[s] = sl[s ^ (1 << p)] | (1 << (vct[p].first - 1));
			sr[s] = sr[s ^ (1 << p)] | (1 << (vct[p].second - 1 - L));
		}
		(ans += f[Ul ^ sl[s]] * g[Ur ^ sr[s]]) %= MOD;
	}
	printf("%lld\n", ans);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) scanf("%d%d", &eu[i], &ev[i]);
	power2[0] = 1;
	for(int i = 1; i <= m; i++) power2[i] = power2[i - 1] * 2 % MOD;
	int cnt = 0;
	while(++cnt <= 100000) {
		for(int i = 1; i <= n; i++) tmp[i] = i;
		std::random_shuffle(tmp + 1, tmp + n + 1);
		for(int i = 1; i <= n; i++) mapping[tmp[i]] = i;
		int L = rand() % 6 - 3 + n / 2;
		if(L < 1) L = 1;
		if(L >= n) L = n - 1;
		int cnt = 0;
		for(int i = 1; i <= m; i++) (cnt += (mapping[eu[i]] <= L) != (mapping[ev[i]] <= L));
		if(cnt <= 25) { solve(L); return 0; }
	}
	while(true) {
		for(int i = 1; i <= n; i++) tmp[i] = i;
		std::random_shuffle(tmp + 1, tmp + n + 1);
		for(int i = 1; i <= n; i++) mapping[tmp[i]] = i;
		int L = rand() % 8 - 4 + n / 2;
		if(L < 1) L = 1;
		if(L >= n) L = n - 1;
		int cnt = 0;
		for(int i = 1; i <= m; i++) (cnt += (mapping[eu[i]] <= L) != (mapping[ev[i]] <= L));
		if(cnt <= 25) { solve(L); return 0; }
	}
	return 0;
} /*
40 60
2 1
3 2
4 3
5 1
6 2
7 5
8 1
9 5
10 8
11 1
12 1
13 5
14 7
15 14
16 1
17 6
18 5
19 16
20 11
21 5
22 4
*/