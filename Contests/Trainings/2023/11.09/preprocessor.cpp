#include <bits/stdc++.h>

typedef long long LL;

const int N = 20 + 5;

int n, L, R;
LL mod;
int a[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
inline LL mod_(const LL &x) { return x >= mod ? x - mod : x; }

std::array<int, 21> fac;
void get_fac() {
	for(int i = 1; i <= n; i++) {
		int v = i;
		for(const int j : {2, 3, 5, 7, 11, 13, 17, 19}) while(v % j == 0) fac[j]++, v /= j;
	}
}

LL calc(int l, int r) {
	if(l > r) return 0;
	auto cnt = fac;
	LL prod1 = 1;
	for(int j = 0; j < n; j++) {
		int v = n + r - j;
		while(cnt[2] && v % 2 == 0) v /= 2, cnt[2]--;
		while(cnt[3] && v % 3 == 0) v /= 3, cnt[3]--;
		while(cnt[5] && v % 5 == 0) v /= 5, cnt[5]--;
		while(cnt[7] && v % 7 == 0) v /= 7, cnt[7]--;
		if(cnt[11] && v % 11 == 0) v /= 11, cnt[11]--;
		if(cnt[13] && v % 13 == 0) v /= 13, cnt[13]--;
		if(cnt[17] && v % 17 == 0) v /= 17, cnt[17]--;
		if(cnt[19] && v % 19 == 0) v /= 19, cnt[19]--;
		(prod1 *= v) %= mod;
	}
	cnt = fac;
	LL prod2 = 1;
	for(int j = 0; j < n; j++) {
		int v = n + l - 1 - j;
		while(cnt[2] && v % 2 == 0) v /= 2, cnt[2]--;
		while(cnt[3] && v % 3 == 0) v /= 3, cnt[3]--;
		while(cnt[5] && v % 5 == 0) v /= 5, cnt[5]--;
		while(cnt[7] && v % 7 == 0) v /= 7, cnt[7]--;
		if(cnt[11] && v % 11 == 0) v /= 11, cnt[11]--;
		if(cnt[13] && v % 13 == 0) v /= 13, cnt[13]--;
		if(cnt[17] && v % 17 == 0) v /= 17, cnt[17]--;
		if(cnt[19] && v % 19 == 0) v /= 19, cnt[19]--;
		(prod2 *= v) %= mod;
	}
	return mod_(prod1 - prod2 + mod);
}

LL solve(int s) {
	LL base = 0;
	for(int i = 1; i <= n; i++)
		if(s >> (i - 1) & 1) base += a[i] + 1;
	if(base > R) return 0;
	int lb = std::max(0, L - (int)base), rb = R - base;
	// printf("solve(%d) = f(%d, [%d, %d]) = %lld\n", s, n, lb, rb, calc(lb, rb));
	return calc(lb, rb);
}

int main() {
#ifndef DEBUG
	freopen("preprocessor.in", "r", stdin);
	freopen("preprocessor.out", "w", stdout);
#endif
	scanf("%d%d%d%lld", &n, &L, &R, &mod);
	get_fac();
	for(int i = 1; i <= n; i++) {
		int l, r, p;
		scanf("%d%d%d", &l, &r, &p);
		if((l & 1) != p) l++;
		if((r & 1) != p) r--;
		if(l > r) { puts("0"); return 0; }
		L -= l, R -= l;
		a[i] = r - l;
	}
	if(L & 1) L++;
	if(R & 1) R--;
	if(L > R) { puts("0"); return 0; }
	LL maxlen = 0;
	for(int i = 1; i <= n; i++) maxlen += a[i];
	if(maxlen < L) { puts("0"); return 0; }
	for(int i = 1; i <= n; i++) a[i] >>= 1;
	L >>= 1, R >>= 1;
	// printf("L = %d, R = %d\n", L, R);
	// printf("a: "); for(int i = 1; i <= n; i++) printf("%d ", a[i]); puts("");
	LL ans = 0;
	int U = (1 << n) - 1;
	for(int s = 0; s <= U; s++) (ans += ((__builtin_popcount(s) & 1) ? mod - 1 : 1) * solve(s)) %= mod;
	printf("%lld\n", ans);
	return 0;
}