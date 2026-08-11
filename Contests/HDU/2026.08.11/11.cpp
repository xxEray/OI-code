// auto input
#include <bits/stdc++.h>
#include <cassert>
// #ifndef DEBUG
// #define assert(_) ((void)0)
// #endif
using std::cin;
using std::cout;

typedef long long LL;

const int N = 1e6 + 5;

int n, Q;

struct DSU {
	int ld[N];
	std::vector<int> compo[N];
	void init() { for(int i = 1; i <= n; i++) ld[i] = i, compo[i].clear(), compo[i].emplace_back(i); }
	int find(int x) { return ld[x] == x ? x : ld[x] = find(ld[x]); }
	void merge(int x, int y) { // merge y to x
		assert(x == find(x) && y == find(y));
		assert(compo[x].size() >= compo[y].size());
		for(int v : compo[y]) compo[x].emplace_back(v);
		std::vector<int>().swap(compo[y]);
		ld[y] = x;
	}
} dsu;

struct Variable {
	LL a, b; // ax + b
	void execute(LL v) { b += a * v, a = 0; } // 代入 x=v
	void execute(const Variable &x) { b += a * x.b, a *= x.a; } // 代入 x=a' x'+b'
} var[N];
Variable operator+(const Variable &x, const Variable &y) { return {x.a + y.a, x.b + y.b}; }

int main() {
	std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while(T--) {
		cin >> n >> Q;
		dsu.init();
		for(int i = 1; i <= n; i++) var[i] = {1, 0};
		int K = 0;
		while(Q--) {
			int p, q; LL c;
			cin >> p >> q >> c;
			p = (p + K - 1) % n + 1, q = (q + K - 1) % n + 1, c = (c + K) % 1000000000 + 1;
			// printf("p = %d, q = %d, c = %lld\n", p, q, c);
			int lp = dsu.find(p), lq = dsu.find(q);
			if(lp == lq) {
				auto v = var[p] + var[q];
				if(v.a == 0) {
					if(v.b == 2 * c) K++, cout << "Yes\n";
					else cout << "No\n";
				} else {
					// ax+b=2c => x=(2c-b)/a
					// assert(v.b % 2 == 0);
					LL x = (2 * c - v.b) / v.a;
					for(int i : dsu.compo[lp]) var[i].execute(x);
					K++, cout << "Yes\n";
				}
			} else {
				if(dsu.compo[lp].size() < dsu.compo[lq].size()) std::swap(p, q), std::swap(lp, lq);
				if(var[q].a) {
					// a1 x1+b1 + a2 x2+b2 = 2c
					// => x2 = (2c - b2 - b1 - a1 x) / a2
					Variable xq = {-var[p].a / var[q].a, (2 * c - var[p].b - var[q].b) / var[q].a};
					for(int i : dsu.compo[lq]) var[i].execute(xq);
					dsu.merge(lp, lq);
					K++, cout << "Yes\n";
				} else {
					if(var[p].a == 0) {
						auto v = var[p] + var[q];
						if(v.b == 2 * c) K++, cout << "Yes\n";
						else cout << "No\n";
					} else {
						// a1 x1+b1 + b2 = 2c
						// => x1 = (2c - b1 - b2) / a1
						LL xp = (2 * c - var[p].b - var[q].b) / var[p].a;
						for(int i : dsu.compo[lp]) var[i].execute(xp);
						dsu.merge(lp, lq);
						K++, cout << "Yes\n";
					}
				}
			}
			// printf("a: "); for(int i = 1; i <= n; i++) printf("%lldx+%lld ", var[i].a, var[i].b); puts("");
		}
	}
	return 0;
} /*
1
3 5
1 2 2
1 2 3
2 1 999999999
1 1 999999997
1 3 999999998
*/