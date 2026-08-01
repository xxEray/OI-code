#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;

LL r[N], p[N];
int n;

LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }
LL lcm(LL x, LL y) { return x / gcd(x, y) * y; }

LL exgcd(LL a, LL b, LL &x, LL &y) {
    if(b == 0) { x = 1, y = 0; return a; }
	LL x_, y_;
    LL g = exgcd(b, a % b, x_, y_);
    x = y_;
    y = x_ - a / b * y_;
    return g;
}

LL mul(LL a, LL b, LL mod) { return (a * b - (LL)((long double)a / mod * b + 0.5) * mod + mod) % mod; }

// 有两个数组：r[] 和 p[]，分别表示余数和模数
// 一共有 n 组方程
LL excrt() {
	LL a1, b1, a2, b2, x, y;
	a1 = r[1], b1 = p[1];
	for(int i = 2; i <= n; i++) {
		a2 = r[i], b2 = p[i];
		if(a2 < a1) std::swap(a1, a2), std::swap(b1, b2);
		LL a = b1, b = b2, c = a2 - a1;
		LL g = exgcd(a, b, x, y);
		if(c % g) return -1;
		a /= g, b /= g, c /= g;
		b1 = lcm(b1, b2);
		y = mul(y, b1 - c, b1);
		a1 = (a2 + mul(b2, y, b1)) % b1;
	}
	return a1;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld%lld", &p[i], &r[i]);
	printf("%lld\n", excrt());
	return 0;
} /*
3
11 6
25 9
33 17
*/