#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e5 + 5;

int n, m, Q;
int ind[N], d[N];
int cnt = 0;

LL bigrand() { return (LL)rand() << 30 | rand(); }
LL a[N], b[N], c[N];

int main() {
	scanf("%d%d", &n, &m);
	cnt = m;
	LL val = 0, xor_all = 0;
	for(int i = 1; i <= n; i++) a[i] = bigrand(), xor_all ^= a[i];
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); ind[v]++, b[v] ^= a[u], val ^= a[u]; }
	for(int i = 1; i <= n; i++) d[i] = ind[i], c[i] = b[i];
	scanf("%d", &Q);
	while(Q--) {
		int t, x, y;
		scanf("%d", &t);
		if(t == 1) scanf("%d%d", &x, &y), cnt--, d[y]--, val ^= a[x], c[y] ^= a[x];
		else if(t == 2) scanf("%d", &x), cnt -= d[x], d[x] = 0, val ^= c[x], c[x] = 0;
		else if(t == 3) scanf("%d%d", &x, &y), cnt++, d[y]++, val ^= a[x], c[y] ^= a[x];
		else if(t == 4) scanf("%d", &x), cnt += ind[x] - d[x], d[x] = ind[x], val ^= b[x] ^ c[x], c[x] = b[x];
		puts(cnt == n && val == xor_all ? "YES" : "NO");
	}
	return 0;
}