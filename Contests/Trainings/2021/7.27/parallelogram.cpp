#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 5e3 + 5;
const int MAXN = 5e3;

bool isprm[N];
int prime[N], c;
LL f[N], g[N];
LL go[20][N];
int logof[N];

int maxind(int x, int y) { return f[x] > f[y] ? x : y; }

void sieve() {
	for(int i = 2; i <= MAXN; i++) isprm[i] = true;
	g[1] = 1;
	for(int i = 2; i <= MAXN; i++) {
		if(isprm[i]) prime[++c] = i, g[i] = 2;
		for(int j = 1; j <= c; j++) {
			int p = prime[j];
			if((LL)p * i > MAXN) break;
			isprm[i * p] = false;
			if(i % p == 0) { g[i * p] = g[i] + 1; break; }
			else g[i * p] = g[i] * 2;
		}
	}
	for(int i = 1; i <= MAXN; i++)
		for(int j = 1; j < i; j++)
			f[i] += g[j] * g[i - j];
	for(int i = 1; i <= MAXN; i++) go[0][i] = i;
	for(int i = 2; i <= MAXN; i++) logof[i] = logof[i >> 1] + 1;
	for(int j = 1; j < 20; j++)
		for(int i = 1; i + (1 << j) - 1 <= MAXN; i++)
			go[j][i] = maxind(go[j - 1][i], go[j - 1][i + (1 << (j - 1))]);
}

int main() {
#ifndef DEBUG
	freopen("parallelogram.in", "r", stdin);
	freopen("parallelogram.out", "w", stdout);
#endif
	sieve();
	int Q; scanf("%d", &Q);
	while(Q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		int k = logof[r - l + 1];
		int ind = maxind(go[k][l], go[k][r - (1 << k) + 1]);
		printf("%d %lld\n", ind, f[ind]);
	}
	return 0;
}
