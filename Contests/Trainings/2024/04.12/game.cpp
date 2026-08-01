#include <bits/stdc++.h>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

typedef long long LL;
typedef __int128_t LLL;

const LL D = 2.5e6;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

LL qpow(LL x, LL y, LL mod) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
LL inv(LL x, LL mod) { return qpow(x, mod - 2, mod); }

LL g, p;

void get_g() {
	std::vector<LL> factor;
	LL q = p - 1;
	for(LL i = 2; i * i <= q; i++) if(q % i == 0) {
		factor.emplace_back(i);
		while(q % i == 0) q /= i;
	}
	if(q > 1) factor.emplace_back(q);
	for(LL i = 2; i <= p; i++) {
		bool flag = true;
		for(auto x : factor) flag &= (qpow(i, (p - 1) / x, p) != 1);
		if(flag) { g = i; break; }
	}
	// printf("g = %lld\n", g);
}

LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }

std::unordered_map<LL, int> mp;
LL tmp2;
void prebsgs() {
	LL power = 1;
	for(int i = 0; i < std::min(D, p); i++) mp[power] = i, (power *= g) %= p;
	tmp2 = inv(qpow(g, D, p), p);
}
LL bsgs(LL x) {
	LL power = x;
	for(int i = 0; i <= (p - 1) / D; i++) {
		if(mp.find(power) != mp.end()) return (mp[power] + i * D) % (p - 1);
		(power *= tmp2) %= p;
	}
	assert(false); return 0;
}

void exgcd(LL a, LL b, LL &x, LL &y) {
	if(b == 0) { x = 1, y = 0; return; }
	exgcd(b, a % b, x, y);
	std::tie(x, y) = std::make_pair(y, x - a / b * y);
}
LL inv_exgcd(LL x, LL mod) {
	LL tmp1, tmp2;
	exgcd(x, mod, tmp1, tmp2);
	// printf("inv(%lld) (mod %lld) = %lld\n", x, mod, (tmp1 % mod + mod) % mod);
	return (tmp1 % mod + mod) % mod;
}

LL f(LL l, LL r, LL a, LL b, LL c, LL d, LL e) {
	// printf("f(%lld, %lld, %lld, %lld, %lld, %lld, %lld)\n", l, r, a, b, c, d, e);
	if(l > r) return LLINF;
	else if((c * l + d) / e == (c * r + d) / e) return std::min(std::min(a * l, a * r) + b * (((LLL)c * l + d) / e), (LLL)LLINF);
	else if(c >= e) return f(l, r, a + b * (c / e), b, c % e, d, e);
	else if(a >= 0) return std::min((LL)std::min(a * l + b * (((LLL)c * l + d) / e), (LLL)LLINF), f((c * l + d) / e + 1, (c * r + d) / e, b, a, e, c - d - 1, c));
	else return std::min((LL)std::min(a * r + b * ((LLL)c * r + d) / e, (LLL)LLINF), f((c * l + d) / e, (c * r + d) / e - 1, b, a, e, e - d - 1, c));
}

LL fbf(LL l, LL r, LL a, LL b, LL c, LL d, LL e) {
	LL ret = LLINF;
	for(LL i = l; i <= r; i++) ret = std::min(ret, a * i + b * ((c * i + d) / e));
	return ret;
}

int main() {
#ifndef DEBUG
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
#endif
	int T;
	scanf("%lld%d", &p, &T);
	get_g();
	prebsgs();
	fprintf(stderr, "%.3f\n", (double)clock() / CLOCKS_PER_SEC);
	while(T--) {
		LL a, b, c, d;
		scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
		c %= p, d %= p;
		if(!c || !d) {
			if(!c && !d) printf("%lld\n", a + b);
			else puts("Ciallo!");
			continue;
		}
		c = bsgs(c), d = bsgs(d);
		if(!c || !d) {
			// printf("a = %lld, b = %lld, c = %lld, d = %lld\n", a, b, c, d);
			if(!c && !d) printf("%lld\n", a + b);
			else if(!c) printf("%lld\n", a + b * ((p - 1) / gcd(d, p - 1)));
			else printf("%lld\n", a * ((p - 1) / gcd(c, p - 1)) + b);
			continue;
		}
		// printf("c = %lld, d = %lld\n", c, d);
		LL q = p - 1;
		LL gc = gcd(gcd(c, d), q);
		c /= gc, d /= gc, q /= gc;
		gc = gcd(c, q), c /= gc, q /= gc, b *= gc;
		(d *= inv_exgcd(c, q)) %= q;
		// printf("d = %lld\n", d);
		gc = gcd(d, q), d /= gc, q /= gc, a *= gc;
		// printf("a = %lld, b = %lld, d = %lld, q = %lld\n", a, b, d, q);
		printf("%lld\n", std::min(a + b * q, f(1, q - 1, b + a * d, -a * q, d, 0, q)));
	}
	return 0;
} /*
979369441 1
166708983 172266912 336385775 222226368
*/