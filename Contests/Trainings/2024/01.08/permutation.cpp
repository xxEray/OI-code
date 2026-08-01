#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D;
	char rdc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char c = rdc();
		while(c < '0' || c > '9') c = rdc();
		for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
	}
}
using FIO::read;

typedef long long LL;

const int N = 3e7 + 5;
const LL MOD = 1e9 + 7;

int n;
int a[N];

std::bitset<N> isprm;
std::vector<int> prime;
int bl[N], mpf[N];
void sieve() {
	isprm.set();
	bl[1] = 1, mpf[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(isprm[i]) prime.emplace_back(i), bl[i] = i, mpf[i] = i;
		for(int p : prime) {
			if((LL)p * i > n) break;
			isprm[p * i] = false, mpf[p * i] = mpf[i];
			if(i % p == 0) {
				bl[p * i] = bl[i];
				break;
			} else bl[p * i] = p * bl[i];
		}
	}
}

int fac[N];
void preprocess() {
	fac[0] = 1;
	for(int i = 1; i < N; i++) fac[i] = (LL)fac[i - 1] * i % MOD;
}

int cnt[N], vis[N];

int main() {
#ifndef DEBUG
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
#endif
	preprocess();
	read(n);
	for(int i = 1; i <= n; i++) read(a[i]);
	bool special = true;
	for(int i = 1; i <= n; i++) special &= (a[i] == i);
	if(special) { puts("1"); return 0; }
	sieve();
	// printf("bl: "); for(int i = 1; i <= n; i++) printf("%d ", bl[i]); puts("");
	for(int i = 1; i <= n; i++) if(a[i]) {
		if(bl[i] != bl[a[i]] && (!isprm[mpf[i]] || !isprm[mpf[a[i]]] || (mpf[i] == 1 ? 1 : n / mpf[i]) != (mpf[a[i]] == 1 ? 1 : n / mpf[a[i]]))) { puts("0"); return 0; }
		if(!vis[mpf[a[i]]]) vis[mpf[a[i]]] = mpf[i];
		else if(vis[mpf[a[i]]] != mpf[i]) { puts("0"); return 0; }
		if(!cnt[mpf[i]]) cnt[mpf[i]] = mpf[a[i]];
		else if(cnt[mpf[i]] != mpf[a[i]]) { puts("0"); return 0; }
	}
	for(int i = 1; i <= n; i++) cnt[i] = 0;
	LL ans = 1;
	for(int i = 1; i <= n; i++) if(!a[i]) cnt[bl[i]]++;
	for(int i = 1; i <= n; i++) if(cnt[i]) (ans *= (LL)fac[cnt[i]]) %= MOD;
	for(int i = 1; i <= n; i++) cnt[i] = 0;
	for(int i = 1; i <= n; i++) if(isprm[i] && bl[i] == i && !vis[i]) cnt[i == 1 ? 1 : n / i]++;
	for(int i = 1; i <= n; i++) if(cnt[i]) (ans *= (LL)fac[cnt[i]]) %= MOD;
	printf("%lld\n", ans);
	return 0;
}