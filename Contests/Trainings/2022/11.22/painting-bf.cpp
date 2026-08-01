#include <bits/stdc++.h>

const int N = 100 + 5;

int n = 5, K = 1e9;

struct Matrix {
	int a[N][N];
	Matrix() { for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) a[i][j] = 0; }
	friend Matrix operator*(Matrix x, Matrix y) {
		Matrix z;
		for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) for(int k = 0; k < n; k++) z.a[i][j] |= x.a[i][k] & y.a[k][j];
		return z;
	}
};
int ans = -1;
Matrix A;
void solve(int sz) {
	Matrix B = A, C = A;
	Matrix ret;
	for(int i = 0; i < n; i++) ret.a[i][i] = 1;
	int x = K;
	while(true) {
		if(x & 1) ret = ret * B;
		if(!(x >>= 1)) break;
		B = B * B;
	}
	bool flag = true;
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) flag &= ret.a[i][j] == 0;
	if(flag) {
		ans = sz;
		printf("%d:\n", ans);
		for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) printf("%d%c", C.a[i][j], " \n"[j == n - 1]);
	}
}
void dfs(int i, int j, int sz) {
	if(sz + (n - j) + (n - i) * (n - i + 1) / 2 < ans || sz > n * (n - 1) / 2) return;
	if(i == n) { if(sz > ans && sz <= n * (n - 1) / 2) solve(sz); return; }
	if(j == n) dfs(i + 1, i + 1, sz);
	A.a[i][j] = 0, dfs(i, j + 1, sz);
	A.a[i][j] = 1, dfs(i, j + 1, sz + 1);
}

int main() {
	dfs(0, 1, 0);
	return 0;
}
