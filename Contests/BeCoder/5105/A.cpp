#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n, K;
LL mod;

int cntA, cntB, lenA, lenB;
void build1(int l, int r, int h) {
	if(l > r) return;
	if(h <= 1 || l == r) {
		lenA = std::min(lenA, r - l + 1);
		return;
	}
	int mid = (l + r) >> 1;
	build1(l, mid, h - 1), build1(mid + 1, r, h - 1);
}
void build2(int l, int r, int h) {
	if(l > r) return;
	if(h <= 1 || l == r) {
		if(r - l + 1 == lenA) cntA++;
		else cntB++;
		return;
	}
	int mid = (l + r) >> 1;
	build2(l, mid, h - 1), build2(mid + 1, r, h - 1);
}

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
LL inv(LL x) { return qpow(x, mod - 2); }
LL C(int x, int y) { return x < 0 || y < 0 || x < y ? 0LL : fac[x] * invfac[y] % mod * invfac[x - y] % mod; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % mod;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % mod;
}

LL calc(int len) {
	const LL inv2 = inv(2);
	return (LL)len * (len - 1) / 2 % mod * n % mod * (n - 1) % mod * inv2 % mod * fac[n - 2] % mod;
}

LL sum(int l, int r) { return l > r ? 0LL : (LL)(l + r) * (r - l + 1) / 2 % mod; }
LL calc(int len1, int len2) {
	LL ret = 0;
	const LL inv2 = inv(2);
	for(int i = 3; i <= len1 + len2; i++) {
		// sumC = C(i - 3, i - 2 - len2 .. len1 - 2)
		(ret += C(n, i) * (i - 1) % mod * (i - 2) % mod * inv2 % mod * fac[i - 3] % mod *
			sum(std::max(1, i - 1 - len2), std::min(i - 2, len1 - 1)) % mod * fac[n - i]) %= mod;
	}
	// printf("calc(%d, %d) = %lld\n", len1, len2, ret);
	return ret;
}

int main() {
	scanf("%d%d%lld", &n, &K, &mod);
	get_factorial(n);
	lenA = n, build1(1, n, K), lenB = lenA + 1, build2(1, n, K);
	// printf("lenA = %d, lenB = %d, cntA = %d, cntB = %d\n", lenA, lenB, cntA, cntB);
	LL ans = 0;
	if(cntA) (ans += cntA * calc(lenA)) %= mod;
	if(cntB) (ans += cntB * calc(lenB)) %= mod;
	// printf("ans = %lld\n", ans);
	if(cntA >= 2) (ans += (LL)cntA * (cntA - 1) % mod * calc(lenA, lenA)) %= mod;
	if(cntB >= 2) (ans += (LL)cntB * (cntB - 1) % mod * calc(lenB, lenB)) %= mod;
	if(cntA && cntB) (ans += (LL)cntA * cntB % mod * calc(lenA, lenB)) %= mod;
	if(cntA && cntB) (ans += (LL)cntA * cntB % mod * calc(lenB, lenA)) %= mod;
	printf("%lld\n", ans * invfac[n] % mod);
	return 0;
}