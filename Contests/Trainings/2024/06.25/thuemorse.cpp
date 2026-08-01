#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e6 + 5;
const int MOD = 1e9 + 7;

LL n;
char s[N];

namespace Solve_n20 {
	template<int n> struct Solver {
		char s[(1 << n) + 5];
		struct SAM {
			struct State { int len, link; std::map<int, int> next; } t[(1 << n) << 1];
			int tot, last;
			SAM() : tot(1), last(0) { t[0].len = 0, t[0].link = -1, t[0].next.clear(); }
			void init() { tot = 1, last = 0, t[0].len = 0, t[0].link = -1, t[0].next.clear(); }
			void insert(int c) {
				int cur = tot++, p = last;
				t[cur].len = t[last].len + 1, t[cur].next.clear();
				last = cur;
				for(; ~p && !t[p].next[c]; p = t[p].link) t[p].next[c] = cur;
				if(p == -1) t[cur].link = 0;
				else {
					int q = t[p].next[c];
					if(t[p].len + 1 == t[q].len) t[cur].link = q;
					else {
						int clone = tot++;
						t[clone].len = t[p].len + 1;
						t[clone].link = t[q].link, t[q].link = clone;
						t[clone].next = t[q].next;
						t[cur].link = clone;
						for(; ~p && t[p].next[c] == q; p = t[p].link) t[p].next[c] = clone;
					}
				}
			}
		} sam;
		std::vector<int> son[(1 << n) << 1];
		int cnt[(1 << n) << 1], tin[(1 << n) + 5];
		void dfs(int u) { for(int v : son[u]) dfs(v), cnt[u] += cnt[v]; }
		bool inited;
		void init() {
			for(int i = 0; i < (1 << n); i++) s[i] = ((__builtin_popcount(i) & 1) ? 'b' : 'a');
			for(int i = 0; i < (1 << n); i++) sam.insert(s[i]);
			for(int i = 1; i < sam.tot; i++) son[sam.t[i].link].emplace_back(i);
			int now = 0;
			for(int i = 0; i < (1 << n); i++) now = sam.t[now].next[s[i]], cnt[now]++;
			dfs(0);
			for(int i = 1; i < sam.tot; i++) (tin[cnt[i]] += sam.t[i].len - sam.t[sam.t[i].link].len) %= MOD;
		}
		void solve() {
			if(!inited) init(), inited = true;
			int len = strlen(::s + 1), now = 0;
			for(int i = 1; i <= len; i++) {
				if(!sam.t[now].next.count(::s[i])) { now = 0; break; }
				now = sam.t[now].next[::s[i]];
			}
			if(now) printf("%d %d\n", cnt[now], tin[cnt[now]]);
			else printf("0 -1\n");
		}
	};
	#define GEN1(t) Solver<t> solver##t;
	GEN1(1) GEN1(2) GEN1(3) GEN1(4) GEN1(5) GEN1(6) GEN1(7) GEN1(8) GEN1(9) GEN1(10)
	GEN1(11) GEN1(12) GEN1(13) GEN1(14) GEN1(15) GEN1(16) GEN1(17) GEN1(18) GEN1(19) GEN1(20)
	void solve() {
		#define GEN3(t) if(n == t) solver##t.solve();
		GEN3(1) GEN3(2) GEN3(3) GEN3(4) GEN3(5) GEN3(6) GEN3(7) GEN3(8) GEN3(9) GEN3(10)
		GEN3(11) GEN3(12) GEN3(13) GEN3(14) GEN3(15) GEN3(16) GEN3(17) GEN3(18) GEN3(19) GEN3(20)
	}
}

int main() {
#ifndef DEBUG
	freopen("thuemorse.in", "r", stdin);
	freopen("thuemorse.out", "w", stdout);
#endif
	int T, tp; scanf("%d%d", &T, &tp);
	while(T--) {
		scanf("%lld%s", &n, s + 1);
		Solve_n20::solve();
	}
	return 0;
} /*
1 1
4
abba
*/