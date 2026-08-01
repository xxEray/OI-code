#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;
const int mx = 1e6;

bool isprm[N];
std::vector<int> prime;
int mu[N];
int mpf[N], mpe[N];
LL factor[N];
void sieve() {
	for(int i = 2; i <= mx; i++) isprm[i] = true;
	factor[1] = 1, mu[1] = 1;
	for(int i = 2; i <= mx; i++) {
		if(isprm[i]) prime.emplace_back(i), mpf[i] = i, mpe[i] = 1, factor[i] = 2, mu[i] = -1;
		for(int p : prime) {
			if((LL)p * i > mx) break;
			isprm[p * i] = false, mpf[p * i] = p;
			if(i % p == 0) {
				mpe[p * i] = mpe[i] + 1, factor[p * i] = factor[i] / (mpe[i] + 1) * (mpe[i] + 2), mu[p * i] = 0;
				break;
			} else mpe[p * i] = 1, factor[p * i] = factor[i] * 2, mu[p * i] = -mu[i];
		}
	}
}

LL h1[N];
LL calch1(LL n) {
	if(n <= mx) return h1[n];
	LL ret = 0;
	int cnt = 0;
	for(LL i = 1; i <= n; i = n / (n / i) + 1) cnt++, ret += (n / i) * (n / (n / i) - i + 1);
	return ret;
}
LL calc1(LL n) {
	for(int i = 1; i <= mx; i++) h1[i] = h1[i - 1] + factor[i];
	LL ret = 0;
	for(LL t = 1; t * t <= n; t++) {
		LL m = n / (t * t);
		for(LL x = 1; x <= m; x = m / (m / x) + 1)
			ret += mu[t] * calch1(m / x) * (m / (m / x) - x + 1);
	}
	return ret;
}

LL h2[N];
LL calch2(LL n) {
	if(n <= mx) return h2[n];
	LL ret = 0;
	for(LL i = 1; i <= n; i = n / (n / i) + 1) ret += (n / i + 1) / 2 * ((n / (n / i) - (~(n / (n / i)) & 1) - (i + (~i & 1)) + 2) / 2);
	return ret;
}
LL calc2(LL n) {
	for(int i = 1; i <= mx; i++) h2[i] = h2[i - 1] + ((i & 1) ? factor[i] : 0);
	LL ret = 0;
	for(LL t = 1; t * t <= n; t += 2) {
		LL m = n / (t * t);
		for(LL x = 1; x <= m; x = m / (m / x) + 1)
			ret += mu[t] * calch2(m / x) * (m / (m / x) - (~(m / (m / x)) & 1) - (x + (~x & 1)) + 2) / 2;
	}
	return ret;
}

int main() {
#ifndef DEBUG
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
#endif
	sieve();
	LL n;
	scanf("%lld", &n);
	printf("%lld\n", (calc2(n) - (n + 1) / 2) / 2 + (calc1(n / 2) - n / 2) / 2);
	return 0;
}