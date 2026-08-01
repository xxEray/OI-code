#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D, out[D], *O = out;
	char rdc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char c = rdc(), fl = 0;
		while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
		for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
		if(fl) x = -x;
	}
	void wrtc(char c) { (O == out + D ? fwrite(O = out, 1, D, stdout) : 0), *O++ = c; }
	template<typename T> void write(T x, char ch = 0) {
		static char c[60]; int top = 0;
		if(x < 0) wrtc('-'), x = -x;
		do c[++top] = x % 10, x /= 10; while(x);
		while(top) wrtc(c[top--] + '0');
		if(ch) wrtc(ch);
	}
	void flush() { fwrite(out, 1, O - out, stdout); }
	struct Flusher { ~Flusher() { flush(); } } flusher;
}
using FIO::write;
using FIO::read;

const int N = 1e5 + 5;
const double eps = 1e-8;

int n;
struct Node { double a, b; int id; } a[N];
double pre[N];
double suma, sumb;

int out[N];

double getr(double l) {
	double sum = 0;
	for(int i = 1; i <= n; i++)
		if(l <= pre[i - 1]) {
			if(sum + a[i].a * a[i].b <= sumb / 2) sum += a[i].a * a[i].b;
			else return pre[i - 1] + (sumb / 2 - sum) / a[i].b;
		} else if(pre[i - 1] <= l && l <= pre[i]) {
			if((pre[i] - l) * a[i].b <= sumb / 2) sum += (pre[i] - l) * a[i].b;
			else return l + (sumb / 2) / a[i].b;
		}
	return std::abs(sum - sumb / 2) <= eps ? pre[n] : 1e18;
}

int main() {
	srand(time(0));
	int T; read(T);
	while(T--) {
		suma = sumb = 0;
		read(n);
		for(int i = 1; i <= n; i++) { int x; read(x); a[i].a = x; suma += a[i].a; a[i].id = i; }
		for(int i = 1; i <= n; i++) { int x; read(x); a[i].b = x; sumb += a[i].b; a[i].b /= a[i].a; }
		std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.b < y.b; });
		for(int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i].a;
		// for(int i = 1; i <= n; i++) printf("(%.0Lf, %.8Lf) ", a[i].a, a[i].b);
		// puts("");
		double l = 0, r = suma, cnt = 0;
		while(l + eps <= r && ++cnt <= 100) {
			double mid = (l + r) / 2;
			double rr = getr(mid);
			if(std::abs(rr - 1e18) <= eps || rr - mid < suma / 2) r = mid;
			else l = mid;
		}
		r = getr(l);
		// printf("l = %.8Lf, r = %.8Lf\n", l, r);
		std::vector<std::pair<int, double>> ops;
		for(int i = 1; i <= n + 2; i++) out[i] = 0;
		for(int i = 1; i <= n; i++)
			if(l <= pre[i - 1] + eps && pre[i] - eps <= r) out[a[i].id] = 1;
			else if(pre[i - 1] + eps <= l && l <= pre[i] - eps && pre[i] - eps <= r) out[a[i].id] = 1, ops.push_back({a[i].id, (pre[i] - l) / a[i].a});
			else if(l <= pre[i - 1] + eps && pre[i - 1] + eps <= r && r <= pre[i] - eps) out[a[i].id] = 1, ops.push_back({a[i].id, (r - pre[i - 1]) / a[i].a});
			else if(pre[i - 1] + eps <= l && r <= pre[i] - eps) out[a[i].id] = 1, ops.push_back({a[i].id, (r - l) / a[i].a});
		printf("%d\n", (int)ops.size());
		for(auto &p : ops) printf("%d %.8f\n", p.first, p.second);
		for(int i = 1; i <= n + (int)ops.size(); i++) printf("%d ", out[i]);
		puts("");
	}
	return 0;
} /*
1
3
1 2 3
5 7 6
*/