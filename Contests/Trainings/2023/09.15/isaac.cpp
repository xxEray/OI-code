#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D;
	char rdc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char c = rdc(), fl = 0;
		while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
		for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
		if(fl) x = -x;
	}
}
using FIO::read;

typedef long long LL;

const int N = 1e6 + 5;
const double eps = 1e-4;

int n; LL L;
struct Func { LL a, b; } a[N];

struct Node { double x; LL a, b; };
bool operator<(Node x, Node y) { return x.x < y.x - eps; }
std::vector<Node> vctl, vctr;

inline double calc(double x, LL a_, LL b) { return (x - a_) * (x - a_) + b; }
inline double intersect(LL a1, LL b1, LL a2, LL b2) { return (a1 + a2) / 2. + (b2 - b1) / (2. * (a2 - a1)); }

int main() {
	read(n), read(L);
	for(int i = 1; i <= n; i++) {
		int p, q;
		read(p), read(q);
		a[i].a = p, a[i].b = (LL)q * q;
	}
	std::sort(a + 1, a + n + 1, [&](Func x, Func y) { return x.a == y.a ? x.b < y.b : x.a < y.a; });
	int c = 0;
	for(int i = 1; i <= n; i++) if(i == 1 || a[i].a != a[i - 1].a) a[++c] = a[i];
	n = c;
	// printf("a: "); for(int i = 1; i <= n; i++) printf("(%lld, %lld) ", a[i].a, a[i].b); puts("");
	for(int i = 1; i <= n; i++) {
		if(!vctl.empty() && calc(L, vctl.back().a, vctl.back().b) < calc(L, a[i].a, a[i].b) + eps) continue;
		double p;
		while(true) {
			if(vctl.empty() || calc(a[i].a, vctl.back().a, vctl.back().b) > calc(a[i].a, a[i].a, a[i].b) - eps) p = a[i].a;
			else p = intersect(vctl.back().a, vctl.back().b, a[i].a, a[i].b);
			if(!vctl.empty() && vctl.back().x > p - eps) vctl.pop_back();
			else break;
		}
		vctl.push_back({p, a[i].a, a[i].b});
	}
	for(int i = n; i >= 1; i--) {
		if(!vctr.empty() && calc(0, vctr.back().a, vctr.back().b) < calc(0, a[i].a, a[i].b) + eps) continue;
		double p;
		while(true) {
			if(vctr.empty() || calc(a[i].a, vctr.back().a, vctr.back().b) > calc(a[i].a, a[i].a, a[i].b) - eps) p = a[i].a;
			else p = intersect(vctr.back().a, vctr.back().b, a[i].a, a[i].b);
			if(!vctr.empty() && vctr.back().x < p + eps) vctr.pop_back();
			else break;
		}
		vctr.push_back({p, a[i].a, a[i].b});
	}
	std::sort(vctl.begin(), vctl.end()), std::sort(vctr.begin(), vctr.end());
	// printf("vctl: "); for(auto &p : vctl) printf("(%.3f, %lld, %lld) ", p.x, p.a, p.b); puts("");
	// printf("vctr: "); for(auto &p : vctr) printf("(%.3f, %lld, %lld) ", p.x, p.a, p.b); puts("");
	double ans = 0;
	for(int i = 0; i <= n; i++) {
		double l = std::max(a[i].a, 0LL), r = std::min((i == n ? L : a[i + 1].a), L);
		if(l > r + eps) continue;
		int vll = std::upper_bound(vctl.begin(), vctl.end(), (Node){l, 0, 0}) - vctl.begin() - 1, vlr = std::upper_bound(vctl.begin(), vctl.end(), (Node){r, 0, 0}) - vctl.begin() - 1;
		int vrl = std::lower_bound(vctr.begin(), vctr.end(), (Node){l, 0, 0}) - vctr.begin(), vrr = std::lower_bound(vctr.begin(), vctr.end(), (Node){r, 0, 0}) - vctr.begin();
		// printf("[l = %.3f, r = %.3f]: vll=%d, vlr=%d, vrl=%d, vrr=%d\n", l, r, vll, vlr, vrl, vrr);
		auto calculate = [&](double x) -> double {
			auto itl = (vlr < 0 ? vctl.begin() + vll : std::upper_bound(vctl.begin() + vll, vctl.begin() + vlr + 1, (Node){x, 0, 0}));
			auto itr = (vrl >= (int)vctr.size() ? vctr.begin() + vrr + 1 : std::lower_bound(vctr.begin() + vrl, vctr.begin() + vrr + 1, (Node){x, 0, 0}));
			// printf("x = %.6f", x);
			// if(itl != vctl.begin() + vll) printf(", nl = (%.3f, %lld, %lld)", std::prev(itl)->x, std::prev(itl)->a, std::prev(itl)->b);
			// if(itr != vctr.begin() + vrr + 1) printf(", nr = (%.3f, %lld, %lld)", itr->x, itr->a, itr->b);
			// puts("");
			return std::min(itl == vctl.begin() + vll ? 1e36 : calc(x, std::prev(itl)->a, std::prev(itl)->b), itr == vctr.begin() + vrr + 1 ? 1e36 : calc(x, itr->a, itr->b));
		};
		int cnt = 0;
		while(l + eps < r && ++cnt <= 70) {
			double lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;
			if(calculate(lmid) < calculate(rmid)) l = lmid;
			else r = rmid;
		}
		ans = std::max(ans, calculate(l));
		// printf("Finally, x = %.6f, ans = %.6f\n", l, ans);
	}
	printf("%.6f\n", sqrt(ans));
	return 0;
} /*
8 98
67 86
114 91
-11 87
14 53
11 -67
88 -47
106 28
-24 -8
*/