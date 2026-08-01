#include <bits/stdc++.h>

#define SZ(x) ((int)(x).size())
#define msg(...) fprintf(stderr, __VA_ARGS__)

typedef long long LL;

const int N = 1e5 + 5;
const LL D = (1 << 19);
const LL LLINF = (1LL << 38);

int n, K;
char s[N];
int a[N];

struct SparseTable {
	int go[18][N];
	int minpos(int x, int y) { return a[x] <= a[y] ? x : y; }
	void init() {
		for(int i = 0; i <= n; i++) go[0][i] = i;
		for(int j = 1; j <= 17; j++)
			for(int i = 0; i + (1 << j) - 1 <= n; i++)
				go[j][i] = minpos(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
	}
	int get(int l, int r) {
		assert(l <= r);
		int k = 31 ^ __builtin_clz(r - l + 1);
		return minpos(go[k][l], go[k][r - (1 << k) + 1]);
	}
} ST;

// struct DP { int cnt; LL cost; };
// DP operator+(DP x, DP y) { return (DP){x.cnt + y.cnt, x.cost + y.cost}; }
// DP operator+(DP x, LL y) { return (DP){x.cnt, x.cost + y}; }
// DP operator-(DP x, LL y) { return (DP){x.cnt, x.cost - y}; }
// bool operator<(DP x, DP y) { return x.cost == y.cost ? x.cnt < y.cnt : x.cost < y.cost; }
// bool operator>=(DP x, DP y) { return !(x < y); }
typedef LL DP;
inline DP toDP(LL cost) { return cost * D; }
inline DP DPof(int cnt, LL cost) { return cost * D + cnt; }
inline int cntof(DP x) { assert(x >= 0); return x >= 0 ? x % D : (D + x % D) % D; }
inline LL costof(DP x) { assert(x >= 0); return x >= 0 ? x / D : (x - D + 1) / D; }
DP calc(LL ex) {
	// msg("calc %lld\n", ex);
	auto dfs = [&](auto &&self, int l, int r) -> std::pair<DP, LL> {
		if(l >= r) return {DPof(1, ex), 0};
		std::vector<int> pos;
		int val = a[ST.get(l, r)];
		for(int j = ST.get(l, r); a[j] == val; j = ST.get(j + 1, r)) {
			pos.emplace_back(j);
			if(j == r) break;
		}
		LL gu = (LL)SZ(pos) * (SZ(pos) - 1) / 2;
		std::vector<DP> f(1), h(SZ(pos) + 1);
		std::vector<LL> g(1);
		{
			int j = l;
			for(int i : pos) {
				auto [fv, gv] = self(self, j, i - 1);
				f.emplace_back(fv), g.emplace_back(gv);
				gu += gv;
				j = i + 1;
			}
			auto [fv, gv] = self(self, j, r);
			f.emplace_back(fv), g.emplace_back(gv);
			gu += gv;
		}
		for(int i = 1; i <= SZ(pos); i++) g[i] += g[i - 1];
		std::deque<std::pair<DP, DP>> q;
		q.emplace_back(toDP(0), h[0] + f[1] - toDP(g[1]));
		for(int i = 1; i <= SZ(pos); i++) {
			if(i < SZ(pos)) h[i] = toDP(g[i] + (LL)i * (i - 1) / 2);
			else h[i] = toDP(LLINF);
			// for(int j = 0; j < i; j++)
			// 	h[i] = std::min(h[i], h[j] + f[j + 1] + toDP(-g[j + 1] + (LL)j * (j + 1) / 2 - (LL)i * j + g[i] + (LL)i * (i - 1) / 2));
			while(q.size() >= 2 && q[1].second - q[0].second <= (__int128_t)i * (q[1].first - q[0].first)) q.pop_front();
			h[i] = std::min(h[i], q[0].second - i * q[0].first + toDP(g[i] + (LL)i * (i - 1) / 2));
			auto yy = h[i] + f[i + 1] + toDP(-g[i + 1] + (LL)i * (i + 1) / 2);
			while(q.size() >= 2 && (__int128_t)(yy - q.end()[-2].second) * (toDP(i) - q.back().first) >= (__int128_t)(yy - q.back().second) * (toDP(i) - q.end()[-2].first))
				q.pop_back();
			q.emplace_back(toDP(i), yy);
		}
		// msg("[%d, %d]:\n", l, r);
		// msg("  pos: "); for(int p : pos) msg("%d ", p); msg("\n");
		// msg("  f: "); for(auto [p, q] : f) msg("(%d,%lld) ", p, q); msg("\n");
		// msg("  g: "); for(int p : g) msg("%d ", p); msg("\n");
		// msg("  h: "); for(auto [p, q] : h) msg("(%d,%lld) ", p, q); msg("\n");
		auto res = std::min({h[SZ(pos)] + toDP(g.back()), h[SZ(pos)] + f.back(), f.back() + toDP(gu - g.back())});
		assert(cntof(res));
		// if(res.cnt == 0) res.cnt = 1, res.cost = ex;
		// msg("  return {(%d,%lld), %lld}\n", res.cnt, res.cost, gu);
		return {res, gu};
	};
	auto [retf, retg] = dfs(dfs, 0, n);
	auto ret = std::min(retf, toDP(retg));
	// msg("calc %lld = (%d, %lld)\n", ex, ret.cnt, ret.cost);
	return ret + 1;
}

int main() {
	scanf("%d%d%s", &n, &K, s + 1);
	for(int i = 1; i <= n; i++) a[i] = a[i - 1] + (s[i] == '(' ? 1 : -1);
	// msg("a: "); for(int i = 0; i <= n; i++) msg("%d ", a[i]); msg("\n");
	ST.init();
	// calc(1);
	LL l = 0, r = 1e10 + 10;
	while(l < r) {
		LL mid = (l + r) >> 1;
		if(cntof(calc(mid)) <= K) r = mid;
		else l = mid + 1;
	}
	printf("%lld\n", costof(calc(l)) - l * (K - 1));
	return 0;
} /*
15 5
())(()())()(())
*/