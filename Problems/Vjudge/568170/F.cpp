#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n, Q;
LL m;
LL a[N];
int nxt[N];

LL calc_phi(LL x) {
	LL v = x; // , copy = x;
	for(int i = 2; (LL)i * i <= x; i++) if(x % i == 0) {
		v = v / i * (i - 1);
		while(x % i == 0) x /= i;
	}
	if(x > 1) v = v / x * (x - 1);
	// printf("phi(%lld) = %lld\n", copy, v);
	return v;
}
std::unordered_map<int, int> phi;
void get_phi() {
	int x = m;
	while(x > 1) phi[x] = calc_phi(x), x = phi[x];
}

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }
LL qpow(LL x, LL y, LL mod) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
bool bigger_than(int l, int r, LL val) {
	long double v = 1, v2 = 1;
	for(int i = r; i >= l; i--) {
		v = powl(a[i], v);
		if(v >= 1e10) return true;
		v2 = qpow(a[i], v2, 1000000000000);
	}
	return v2 >= val;
}
LL calc(int l, int r, LL mod) {
	if(l == r) return a[l] % mod;
	else if(mod == 1) return 0;
	else if(gcd(a[l], mod) == 1) return qpow(a[l], calc(l + 1, r, phi[mod]), mod);
	else if(r <= l + 5) return qpow(a[l], calc(l + 1, r, phi[mod]) + bigger_than(l + 1, r, phi[mod]) * phi[mod], mod);
	else return qpow(a[l], calc(l + 1, r, phi[mod]) + phi[mod], mod);
}

int main() {
	scanf("%d%lld", &n, &m);
	get_phi();
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	nxt[n + 1] = n + 1;
	for(int i = n; i >= 1; i--) nxt[i] = (a[i] == 1 ? i : nxt[i + 1]);
	scanf("%d", &Q);
	while(Q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		r = std::min(r, nxt[l] - 1);
		if(l > r) printf("%lld\n", 1 % m);
		else printf("%lld\n", calc(l, r, m));
	}
	return 0;
}