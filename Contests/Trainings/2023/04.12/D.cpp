#include <cstdio>
#include <algorithm>
#include <set>
#include <cassert>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, K;
int aa[N], bb[N], ls[N], rs[N];

struct Segment { int l, r; };
bool operator<(Segment x, Segment y) { return x.l == y.l ? x.r < y.r : x.l < y.l; }
using Set = std::set<Segment>;
Set st[N], st_copy[N];

void remove_all(Set &cur, int l, int r) {
	while(true) {
		auto it = cur.lower_bound({l, 0});
		if(it == cur.end() || it->r > r) break;
		cur.erase(it);
	}
}
void split(int p, Set &cur) {
	auto it = cur.lower_bound({p, 0});
	if(it == cur.begin()) return;
	it--;
	int l = it->l, r = it->r;
	if(r >= p) {
		cur.erase({l, r});
		if(l <= p - 1) cur.insert({l, p - 1});
		if(p <= r) cur.insert({p, r});
	}
}
void setand_eq(Set &x, Set &y) {
	if(x.size() > y.size()) x.swap(y);
	int last = -1;
	for(auto i : x) {
		split(i.l, y), split(i.r + 1, y);
		remove_all(y, last + 1, i.l - 1);
		last = i.r;
	}
	remove_all(y, last + 1, K - 1);
	x.swap(y);
}
void setor_eq(Set &x, Set &y) {
	if(x.size() > y.size()) x.swap(y);
	for(auto i : x) {
		split(i.l, y), split(i.r + 1, y);
		remove_all(y, i.l, i.r);
		y.insert({i.l, i.r});
	}
	x.swap(y);
}
bool check_setand(int l, int r, const Set &cur) {
	if(l > r) return false;
	auto it = cur.lower_bound({l, 0});
	if(it != cur.end() && it->l <= r) return true;
	if(it != cur.begin() && std::prev(it)->r >= l) return true;
	return false;
};

int f[N];
void dfs(int u) {
	if(!u) return;
	dfs(ls[u]), dfs(rs[u]);
	// st_copy[ls[u]] = st[ls[u]], st_copy[rs[u]] = st[rs[u]];
	if(!ls[u] && !rs[u]) {
		f[u] = 0;
		return;
	}
	st[0] = {{0, K - 1}};
	auto &a = st[ls[u]], &b = st[rs[u]], &c = st[u];
	if(a.size() > b.size()) a.swap(b);
	bool flag;
	// check if a & b & c isn't empty
	flag = false;
	for(auto &i : a) {
		if(check_setand(std::max(i.l, c.begin()->l), std::min(i.r, c.begin()->r), b)) { flag = true; break; }
		if(c.size() == 2 && check_setand(std::max(i.l, c.rbegin()->l), std::min(i.r, c.rbegin()->r), b)) { flag = true; break; }
	}
	if(flag) {
		setand_eq(a, b), setand_eq(c, a);
		f[u] = f[ls[u]] + f[rs[u]];
		return;
	}
	// check if any of a & b, a & c, b & c isn't empty
	flag = false;
	for(auto &i : a) if(check_setand(i.l, i.r, b)) { flag = true; break; }
	if(!flag) for(auto &i : c) if(check_setand(i.l, i.r, a)) { flag = true; break; }
	if(!flag) for(auto &i : c) if(check_setand(i.l, i.r, b)) { flag = true; break; }
	if(flag) {
		// calculate (a & b) | (a & c) | (b & c) = (a & b) | (c & (a | b))
		for(auto &i : c) {
			split(i.l, a), split(i.l, b);
			split(i.r + 1, a), split(i.r + 1, b);
		}
		auto in_c = [&](int l, int r) -> bool {
			if(l >= c.begin()->l && r <= c.begin()->r) return true;
			else if(c.size() == 2 && l >= c.rbegin()->l && r <= c.rbegin()->r) return true;
			else return false;
		};
		auto lbound = [&](int l) -> int {
			if(c.rbegin()->r < l) return c.rbegin()->r + 1;
			else if(c.size() == 2 && c.begin()->r < l) return c.begin()->r + 1;
			else return 0;
		};
		auto rbound = [&](int r) -> int {
			if(c.begin()->l > r) return c.begin()->l - 1;
			else if(c.size() == 2 && c.rbegin()->l > r) return c.rbegin()->l - 1;
			else return K - 1;
		};
		for(auto ita = a.begin(); ita != a.end(); ita++) {
			auto &i = *ita;
			if(in_c(i.l, i.r)) {
				split(i.l, b), split(i.r + 1, b);
				remove_all(b, i.l, i.r);
				b.insert({i.l, i.r});
			} else {
				int lb = std::max(ita == a.begin() ? 0 : std::prev(ita)->r + 1, lbound(ita->l));
				int rb = std::min(std::next(ita) == a.end() ? K - 1 : std::next(ita)->l - 1, rbound(ita->r));
				split(lb, b), split(i.l, b), split(i.r + 1, b), split(rb + 1, b);
				remove_all(b, lb, i.l - 1), remove_all(b, i.r + 1, rb);
			}
		}
		if(a.begin()->l > c.begin()->l) remove_all(b, 0, c.begin()->l - 1);
		if(a.rbegin()->r < c.rbegin()->r) remove_all(b, c.rbegin()->r + 1, K - 1);
		if(c.size() == 2) {
			auto it = a.lower_bound({c.begin()->r + 1, 0});
			if(it == a.end() || it->l >= c.rbegin()->l) remove_all(b, c.begin()->r + 1, c.rbegin()->l - 1);
		}
		c.swap(b);
		f[u] = f[ls[u]] + f[rs[u]] + 1;
		return;
	}
	setor_eq(a, b), setor_eq(c, a);
	f[u] = f[ls[u]] + f[rs[u]] + 2;
}

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d%d%d%d", &aa[i], &bb[i], &ls[i], &rs[i]);
	for(int i = 1; i <= n; i++)
		if(aa[i] <= bb[i]) {
			if(K - bb[i] <= K - 1 - aa[i]) st[i].insert({K - bb[i], K - 1 - aa[i]});
		} else {
			if(0 <= K - 1 - aa[i]) st[i].insert({0, K - 1 - aa[i]});
			if(K - bb[i] <= K - 1) st[i].insert({K - bb[i], K - 1});
		}
	// for(int i = 1; i <= n; i++) {
	// 	printf("%d: ", i);
	// 	for(auto j : st[i]) printf("[%d, %d] ", j.l, j.r);
	// 	puts("");
	// }
	dfs(1);
	// st_copy[1] = st[1];
	// for(int i = 1; i <= n; i++) {
	// 	printf("%d: (%d) ", i, f[i]);
	// 	for(auto j : st_copy[i]) printf("[%d, %d] ", j.l, j.r);
	// 	puts("");
	// }
	printf("%d\n", f[1] + (st[1].empty() || st[1].begin()->l >= 1));
	return 0;
} /*
5 5
2 0 0 2
2 4 0 3
0 2 0 4
2 4 5 0
4 1 0 0
*/