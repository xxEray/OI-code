#include <cstdio>
#include <algorithm>
#include <cmath>

typedef long long LL;

const int N = 4e5 + 5;
const int MX = 2e5;

int n; LL m;

const double PI = acos(-1);
struct Complex {
	double x, y;
	Complex(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
};
Complex operator+(const Complex &a, const Complex &b) { return Complex(a.x + b.x, a.y + b.y); }
Complex operator-(const Complex &a, const Complex &b) { return Complex(a.x - b.x, a.y - b.y); }
Complex operator*(const Complex &a, const Complex &b) { return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
struct FFT {
	int rev[N];
	int limit;
	int init(int mx) {
		int w = 0;
		limit = 1;
		while(limit <= mx) limit <<= 1, w++; // w = log2(limit)
		for(int i = 0; i < limit; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (w - 1));
		return limit;
	}
	void trans(Complex *a, int type) { // type = 1 / -1
		for(int i = 0; i < limit; i++) if(i < rev[i]) std::swap(a[i], a[rev[i]]);
		for(int i = 1; i < limit; i <<= 1) {
			Complex wn = Complex(cos(PI / i), type * sin(PI / i));
			for(int j = 0; j < limit; j += (i << 1)) {
				Complex w(1, 0);
				for(int k = 0; k < i; k++, w = w * wn) {
					Complex x = a[j + k], y = w * a[j + i + k];
					a[j + k] = x + y;
					a[j + i + k] = x - y;
				}
			}
		}
		if(type == -1) for(int i = 0; i < limit; i++) a[i].x /= limit;
	}
	int trans(Complex *a, int n_, int type) { int ret = init(n_); trans(a, type); return ret; }
} fft;

LL cnt[N];
Complex tmp[N];

int main() {
	scanf("%d%lld", &n, &m);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); cnt[x]++; }
	for(int i = 1; i <= MX; i++) tmp[i].x = cnt[i];
	int mx = fft.init(MX);
	fft.trans(tmp, 1);
	for(int i = 0; i < mx; i++) tmp[i] = tmp[i] * tmp[i];
	fft.trans(tmp, -1);
	for(int i = 1; i <= MX; i++) cnt[i] = round(tmp[i].x);
	LL ans = 0;
	for(int i = MX; i >= 1 && m; i--)
		if(m >= cnt[i]) ans += cnt[i] * i, m -= cnt[i];
		else ans += m * i, m = 0;
	printf("%lld\n", ans);
	return 0;
}