#include <bits/stdc++.h>

const int N = 100 + 5;

int n;
int b[N];

struct Node { int k[N]; } f[N][N];
Node operator^(Node x, Node y) {
	Node z;
	for(int i = 1; i <= n; i++) z.k[i] = x.k[i] ^ y.k[i];
	return z;
}

int equ[N][N];
bool vis[N];
void gauss(int r, int c) {
	for(int var = 1; var <= c - 1; var++) {
		int id = -1;
		for(int i = 1; i <= r; i++) if(!vis[i] && equ[i][var]) { id = i; break; }
		assert(id != -1);
		vis[id] = true;
		for(int i = 1; i <= r; i++) if(i != id && equ[i][var])
			for(int j = var; j <= c; j++)
				equ[i][j] ^= equ[id][j];
	}
}

int out[N];

int main() {
#ifndef DEBUG
	freopen("burke.in", "r", stdin);
	freopen("burke.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for(int j = 1; j <= n; j++) f[0][j].k[j] = 1;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) f[i][j] = f[i - 1][j] ^ f[i][j - 1];
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) equ[i][j] = f[i][n].k[j];
		equ[i][n + 1] = b[i];
	}
	// for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) {
	// 	printf("[%d][%d]: ", i, j);
	// 	for(int t = 1; t <= n; t++) printf("%d ", f[i][j].k[t]);
	// 	puts("");
	// }
	gauss(n, n + 1);
	for(int i = 1; i <= n; i++) if(equ[i][i]) out[i] = equ[i][n + 1];
	for(int i = 1; i <= n; i++) printf("%d ", out[i]);
	puts("");
	return 0;
}