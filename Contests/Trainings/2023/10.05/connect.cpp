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
	void read(double &x) { long long y; read(y); x = y; }
}
using FIO::read;

const int N = 3e5 + 5;
const double eps = 1e-8;

int n;
double L, R;
struct Node { double x, v0, v; } a[5 * N];

double b[5 * N];
int q[5 * N];
bool check(double x) {
	bool flag = false;
	// printf("check %.8f\n", x);
	int hd = 1, tl = 0;
	for(int i = 0; i <= n; i++) b[i] = a[i].v - x * a[i].x;
	// printf("b: "); for(int i = 0; i <= n; i++) printf("%.2f ", b[i]); puts("");
	for(int i = 0, jl = 0, jr = 0; i <= n; i++) {
		while(jr + 1 <= n && a[jr + 1].v - a[i].v <= R + eps) {
			jr++;
			while(hd <= tl && b[q[tl]] <= b[jr] + eps) tl--;
			q[++tl] = jr;
		}
		while(jl + 1 <= n && a[jl + 1].v - a[i].v < L - eps) {
			jl++;
			while(hd <= tl && q[hd] <= jl) hd++;
		}
		if(hd <= tl) flag |= (b[q[hd]] >= b[i]);
		// printf("i = %d: [%d, %d], flag = %d\n", i, jl, jr, flag);
	}
	return flag;
}

int main() {
#ifndef DEBUG
	freopen("connect.in", "r", stdin);
	freopen("connect.out", "w", stdout);
#endif
	read(n), read(L), read(R);
	for(int i = 1; i <= n; i++) read(a[i].x);
	for(int i = 1; i <= n; i++) read(a[i].v0);
	for(int i = 1; i <= n; i++) a[i].v = a[i - 1].v + a[i].x * a[i].v0, a[i].x += a[i - 1].x;
	int cn = n;
	for(int i = 1, j = 1; i <= n; i++) {
		while(j <= n && a[j].v <= a[i - 1].v + L + eps) j++;
		if(std::abs(a[i - 1].v + L - a[j - 1].v) <= eps) continue;
		if(j <= n) {
			cn++;
			a[cn].v0 = a[j].v0;
			a[cn].v = a[i - 1].v + L;
			a[cn].x = a[j - 1].x + (a[cn].v - a[j - 1].v) / a[cn].v0;
		}
	}
	for(int i = 1, j = 1; i <= n; i++) {
		while(j <= n && a[j].v <= a[i - 1].v + R + eps) j++;
		if(std::abs(a[i - 1].v + R - a[j - 1].v) <= eps) continue;
		if(j <= n) {
			cn++;
			a[cn].v0 = a[j].v0;
			a[cn].v = a[i - 1].v + R;
			a[cn].x = a[j - 1].x + (a[cn].v - a[j - 1].v) / a[cn].v0;
		}
	}
	for(int i = n, j = n; i >= 1; i--) {
		while(j >= 0 && a[j].v >= a[i].v - L - eps) j--;
		if(std::abs(a[i].v - L - a[j + 1].v) <= eps) continue;
		if(j >= 0) {
			cn++;
			a[cn].v0 = a[j + 1].v0;
			a[cn].v = a[i].v - L;
			a[cn].x = a[j + 1].x - (a[j + 1].v - a[cn].v) / a[cn].v0;
		}
	}
	for(int i = n, j = n; i >= 1; i--) {
		while(j >= 0 && a[j].v >= a[i].v - R - eps) j--;
		if(std::abs(a[i].v - R - a[j + 1].v) <= eps) continue;
		if(j >= 0) {
			cn++;
			a[cn].v0 = a[j + 1].v0;
			a[cn].v = a[i].v - R;
			a[cn].x = a[j + 1].x - (a[j + 1].v - a[cn].v) / a[cn].v0;
		}
	}
	// for(int i = 1; i <= cn; i++) printf("(x=%lld, v=%lld)\n", a[i].x, a[i].v);
	std::sort(a + 1, a + cn + 1, [&](Node x, Node y) { return x.x < y.x; });
	// for(int i = 1; i < cn; i++) assert(a[i].x != a[i + 1].x || (a[i].v == a[i + 1].v && a[i].v0 == a[i + 1].v0));
	n = std::unique(a + 1, a + cn + 1, [&](Node x, Node y) { return std::abs(x.x - y.x) <= eps; }) - a - 1;
	a[n + 1].v = a[n].v;
	// for(int i = 1; i <= n; i++) printf("(x=%.2f, v=%.2f)\n", a[i].x, a[i].v);
	double l = 0, r = 1e18;
	int cnt = 100;
	while(l + eps < r && cnt--) {
		double mid = (l + r) / 2;
		if(check(mid)) l = mid;
		else r = mid;
	}
	printf("%.8f\n", l);
	return 0;
} /*
4 8 10
1 10 2 3
4 1 3 2
*/