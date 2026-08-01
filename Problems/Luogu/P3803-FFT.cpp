// FFT template
#include <cstdio>
#include <algorithm>
#include <cmath>

const int N = 4e6 + 5;
const double PI = acos(-1);

struct Complex {
	double x, y;
	Complex(double x = 0, double y = 0) : x(x), y(y) {}
};
Complex operator+(const Complex &a, const Complex &b) { return Complex(a.x + b.x, a.y + b.y); }
Complex operator-(const Complex &a, const Complex &b) { return Complex(a.x - b.x, a.y - b.y); }
Complex operator*(const Complex &a, const Complex &b) { return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }

Complex a[N], b[N];
int n, m;

int limit = 1, w = 0;
int rev[N];

void FFT(Complex *a, int type) {
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

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i <= n; i++) scanf("%lf", &a[i].x);
	for(int i = 0; i <= m; i++) scanf("%lf", &b[i].x);
	while(limit <= n + m) limit <<= 1, w++; // w = log2(limit)
	for(int i = 0; i < limit; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (w - 1));
	FFT(a, 1);
	FFT(b, 1);
	for(int i = 0; i < limit; i++) a[i] = a[i] * b[i];
	FFT(a, -1);
	for(int i = 0; i <= n + m; i++) printf("%d ", (int)(a[i].x + 0.5));
	return 0;
}