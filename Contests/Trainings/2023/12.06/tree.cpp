#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D;
	char rdc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char c = rdc(), fl = 0;
		while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
		for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
		if(fl) x = -x;
	}
}
using FIO::read;

typedef long long LL;

const int N = 1e6 + 5;

int n;
int fa[N];

int mx[N];
int dep[N], sz[N];

int cnt[N];
std::bitset<N> bs;

int main() {
#ifndef DEBUG
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	read(n);
	for(int i = 2; i <= n; i++) read(fa[i]);
	for(int i = n; i >= 2; i--) sz[i]++, sz[fa[i]] += sz[i];
	for(int i = 1; i <= n; i++) mx[i] = n - sz[i];
	for(int i = 2; i <= n; i++) mx[fa[i]] = std::max(mx[fa[i]], sz[i]);
	int rt = 1;
	for(int i = 2; i <= n; i++) if(mx[rt] > mx[i]) rt = i;
	// printf("rt = %d\n", rt);
	dep[rt] = 1;
	for(int x = rt; fa[x]; x = fa[x]) dep[fa[x]] = dep[x] + 1;
	for(int i = 1; i <= n; i++) if(!dep[i]) dep[i] = dep[fa[i]] + 1;
	LL ans = 0;
	for(int i = 1; i <= n; i++) ans += dep[i];
	for(int i = 2; i <= n; i++) if(fa[i] == rt) cnt[sz[i]]++;
	cnt[n - sz[rt]]++;
	bs[0] = 1;
	for(int i = 1; i <= n; i++) {
		if(cnt[i] >= 3) {
			cnt[i << 1] += (cnt[i] - 1) >> 1;
			cnt[i] = ((cnt[i] & 1) ? 1 : 2);
		}
		if(cnt[i]) bs |= bs << i;
		if(cnt[i] & 2) bs |= bs << (i << 1);
	}
	LL ret = 0;
	for(int i = 0; i <= n - 1; i++) if(bs[i]) ret = std::max(ret, (LL)i * (n - 1 - i));
	printf("%lld\n", ans + ret);
	return 0;
}