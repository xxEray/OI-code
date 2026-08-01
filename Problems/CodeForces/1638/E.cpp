#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cassert>

typedef long long LL;

const int N = 1e6 + 5;

int n, Q;
LL v[N];
struct Segment { int l, r, c; };
bool operator<(Segment x, Segment y) { return x.l < y.l; }
std::set<Segment> color;

struct BIT {
	LL t[N];
	void add(int r, LL val) { while(r <= n + 1) t[r] += val, r += r & -r; }
	LL query(int r) { LL ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	void add(int l, int r, LL val) { if(l <= r) /* printf("    bit: [%d, %d] += %lld\n", l, r, val),  */add(l, val), add(r + 1, -val);}
} bit;

void c_init() {
	color.insert({1, n, 1});
}
void c_color(int l, int r, int c) {
	while(true) {
		auto it = color.lower_bound({l, 0, 0});
		if(it == color.end() || it->r > r) break;
		bit.add(it->l, it->r, v[it->c]);
		color.erase(it);
	}
	auto it = color.upper_bound({l, 0, 0});
	if(it != color.begin()) {
		it--;
		int tl = it->l, tr = it->r, tc = it->c;
		color.erase(it);
		if(tr >= r + 1) {
			bit.add(l, r, v[tc]);
			color.insert({tl, l - 1, tc}), color.insert({r + 1, tr, tc});
		} else if(l - 1 >= tl) bit.add(l, tr, v[tc]), color.insert({tl, l - 1, tc});
	}
	it = color.lower_bound({l, 0, 0});
	if(it != color.end()) {
		int tl = it->l, tr = it->r, tc = it->c;
		color.erase(it);
		if(tr >= r + 1) bit.add(tl, r, v[tc]), color.insert({r + 1, tr, tc});
	}
	bit.add(l, r, -v[c]);
	color.insert({l, r, c});
	// printf("  ");
	// for(auto t : color) printf("[%d, %d](%d) ", t.l, t.r, t.c);
	// puts("");
	// printf("  bit: ");
	// for(int i = 1; i <= n; i++) printf("%lld ", bit.query(i));
	// puts("");
}
void c_add(int cl, LL vl) {
	v[cl] += vl;
	// printf("  v: ");
	// for(int i = 1; i <= n; i++) printf("%lld ", v[i]);
	// puts("");
}
LL c_query(int x) {
	// printf("  bit: ");
	// for(int i = 1; i <= n; i++) printf("%lld ", bit.query(i));
	// printf("\n  color of %d is %d\n", x, std::prev(color.upper_bound({x, 0, 0}))->c);
	// printf("  Ans is ");
	return bit.query(x) + v[std::prev(color.upper_bound({x, 0, 0}))->c];
}

int main() {
	scanf("%d%d", &n, &Q);
	c_init();
	while(Q--) {
		char oper[10];
		scanf("%s", oper);
		if(!strcmp(oper, "Color")) {
			int l, r, c;
			scanf("%d%d%d", &l, &r, &c);
			c_color(l, r, c);
		} else if(!strcmp(oper, "Add")) {
			int c; LL vl;
			scanf("%d%lld", &c, &vl);
			c_add(c, vl);
		} else if(!strcmp(oper, "Query")) {
			int ind; scanf("%d", &ind);
			printf("%lld\n", c_query(ind));
		} else if(!strcmp(oper, "Kill")) return 0;
		else assert(false);
	}
	return 0;
} /*
1000000 1000000
Color 268945 569540 878605
Color 285855 776838 458049
Add 458049 -18986837
Color 22991 787001 401204
Add 401204 474128753
Color 91022 98663 340570
Color 6539 724154 971642
Add 971642 295843459
Query 445145

750985375
*/