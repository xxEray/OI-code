#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D;
	char gc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char ch = gc();
		while(ch < '0' || ch > '9') ch = gc();
		for(x = 0; '0' <= ch && ch <= '9'; ch = gc()) x = x * 10 + ch - '0';
	}
}
using FIO::read;

typedef long long LL;
const int N = 5e4 + 5;

int a[N], b[N];
int n, Q;

int nxt[1030][N];

int main() {
#ifndef DEBUG
	freopen("expedition.in", "r", stdin);
	freopen("expedition.out", "w", stdout);
#endif
	read(n);
	for(int i = 1; i <= n; i++) read(a[i]);
	for(int i = 1; i <= n; i++) read(b[i]);
	for(int j = 1; j <= 1023; j++) for(int i = n; i >= 1; i--) nxt[j][i] = ((a[i] | j) == j) ? i : nxt[j][i + 1];
	read(Q);
	LL ans = 0;
	while(Q--) {
		int l, r, x;
		read(l), read(r), read(x);
		LL ret = 0;
		int now = nxt[x][l];
		while(now && now <= r) {
			x -= a[now], ret += b[now];
			now = nxt[x][now];
		}
		ans ^= ret;
	}
	printf("%lld\n", ans);
	return 0;
}
