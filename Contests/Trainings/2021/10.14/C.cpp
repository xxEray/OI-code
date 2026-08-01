#include <cstdio>
#include <algorithm>
#include <cmath>

typedef long long LL;

const int N = 5e6 + 5;
const int MAXN = 5e5;
const double PI = acos(-1);

bool isprm[N];
int prime[N], c;
LL f[N], g[N], h[N];
LL go[20][N];
int logof[N];

int maxind(int x, int y) { return f[x] >= f[y] ? x : y; }

void sieve() {
	for(int i = 2; i <= MAXN; i++) isprm[i] = true;
	g[1] = 1;
	for(int i = 2; i <= MAXN; i++) {
		if(isprm[i]) prime[++c] = i, g[i] = 2, h[i] = 1;
		for(int j = 1; j <= c; j++) {
			int p = prime[j];
			if((LL)p * i > MAXN) break;
			isprm[i * p] = false;
			if(i % p == 0) { h[i * p] = h[i] + 1, g[i * p] = g[i] / (h[i] + 1) * (h[i] + 2); break; }
			else g[i * p] = g[i] * 2, h[i * p] = 1;
		}
	}
}

struct Complex { double x, y; Complex(double x_ = 0, double y_ = 0) : x(x_), y(y_) {} };
Complex operator+(Complex a, Complex b) { return Complex(a.x + b.x, a.y + b.y); }
Complex operator-(Complex a, Complex b) { return Complex(a.x - b.x, a.y - b.y); }
Complex operator*(Complex a, Complex b) { return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }

Complex tmp[N];
int rev[N];
int limit;
void preFFT() {
	limit = 1;
	while(limit <= MAXN + MAXN) limit <<= 1;
	for(int i = 0; i < limit; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? limit >> 1 : 0);
}

void FFT(Complex *a, int type) {
	for(int i = 0; i < limit; i++) if(i < rev[i]) std::swap(a[i], a[rev[i]]);
	for(int i = 1; i < limit; i <<= 1) {
		Complex wn(cos(PI / i), type * sin(PI / i));
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

void RMQ() {
	for(int i = 1; i <= MAXN; i++) go[0][i] = i;
	for(int i = 2; i <= MAXN; i++) logof[i] = logof[i >> 1] + 1;
	for(int j = 1; j < 20; j++)
		for(int i = 1; i + (1 << j) - 1 <= MAXN; i++)
			go[j][i] = maxind(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
}

int main() {
	sieve();
	preFFT();
	for(int i = 1; i < limit; i++) tmp[i] = Complex(g[i], 0);
	FFT(tmp, 1);
	for(int i = 0; i < limit; i++) tmp[i] = tmp[i] * tmp[i];
	FFT(tmp, -1);
	for(int i = 1; i < limit; i++) f[i] = tmp[i].x + 0.5;
	RMQ();
	int Q; scanf("%d", &Q);
	while(Q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		int k = logof[r - l + 1];
		int ind = maxind(go[k][l], go[k][r - (1 << k) + 1]);
		printf("%d %lld\n", ind, f[ind]);
	}
	return 0;
} /*
3
4 4
2 6
*/