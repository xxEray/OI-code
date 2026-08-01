#include <cassert>
typedef long long LL;
typedef double DB;
LL gcd(LL x, LL y) { return y == 0 ? abs(x) : gcd(y, x % y); }
LL lcm(LL x, LL y) { return x / gcd(x, y) * y; }
struct Fraction {
	LL p, q;
	Fraction() : p(0), q(1) {}
	Fraction(LL x) : p(x), q(1) {}
	Fraction(LL p_, LL q_) : p(p_), q(q_) { assert(q != 0); if(p == 0) q = 1; }
	// DB val() { assert(q != 0); return p.to<DB>() / q.to<DB>(); }
	DB val() { assert(q != 0); return (DB)p / q; }
};
Fraction operator+(Fraction x, Fraction y) {
	LL qq = lcm(x.q, y.q);
	LL pp = x.p * (qq / x.q) + y.p * (qq / y.q);
	LL g = gcd(pp, qq);
	pp /= g, qq /= g;
	// printf("%lld/%lld + %lld/%lld = %lld/%lld\n", x.p, x.q, y.p, y.q, pp, qq);
	return Fraction(pp, qq);
}
Fraction operator-(Fraction x, Fraction y) {
	LL qq = lcm(x.q, y.q);
	LL pp = x.p * (qq / x.q) - y.p * (qq / y.q);
	LL g = gcd(pp, qq);
	pp /= g, qq /= g;
	// printf("%lld/%lld - %lld/%lld = %lld/%lld\n", x.p, x.q, y.p, y.q, pp, qq);
	return Fraction(pp, qq);
}
Fraction operator*(Fraction x, Fraction y) {
	LL g = gcd(x.p * y.p, x.q * y.q);
	// printf("%lld/%lld * %lld/%lld = %lld/%lld\n", x.p, x.q, y.p, y.q, x.p * y.p / g, x.q * y.q / g);
	return Fraction(x.p * y.p / g, x.q * y.q / g);
}
Fraction operator/(Fraction x, Fraction y) {
	assert(y.p != 0);
	LL g = gcd(x.p * y.q, x.q * y.p);
	if((x.q < 0) ^ (y.p < 0)) g = -g;
	// printf("%lld/%lld / %lld/%lld = %lld/%lld\n", x.p, x.q, y.p, y.q, x.p * y.q / g, x.q * y.p / g);
	return Fraction(x.p * y.q / g, x.q * y.p / g);
}
bool operator<(Fraction x, Fraction y) {
	LL qq = lcm(x.q, y.q);
	return x.p * (qq / x.q) < y.p * (qq / y.q);
}
bool operator==(Fraction x, Fraction y) { return x.p == y.p && x.q == y.q; }
bool operator!=(Fraction x, Fraction y) { return !(x == y); }
bool operator>(Fraction x, Fraction y) { return y < x; }
bool operator<=(Fraction x, Fraction y) { return !(x > y); }
bool operator>=(Fraction x, Fraction y) { return !(x < y); }