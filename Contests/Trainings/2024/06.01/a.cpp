#include <bits/stdc++.h>

const int N = 2000 + 5;

int n, D;
int cnt[N][N];

int sa[N][N], sb[N][N], sc[N][N];
int sum(int s[N][N], int il, int jl, int ir, int jr) { return s[ir][jr] - s[il - 1][jr] - s[ir][jl - 1] + s[il - 1][jl - 1]; }
bool check(int d) {
	// printf("check %d\n", d);
	for(int i = 0; i < 2 * D; i++) for(int j = 0; j < 2 * D; j++) sa[i][j] = sb[i][j] = sc[i][j] = 0;
	int v = d / D + 1;
	for(int i = 0; i < D; i++) for(int j = 0; j < D; j++) {
		if((long long)v * v >= cnt[i][j]) sc[i + D][j + D] = sc[i][j + D] = sc[i + D][j] = sc[i][j] = 1;
		if((long long)v * (v - 1) >= cnt[i][j]) sb[i + D][j + D] = sb[i][j + D] = sb[i + D][j] = sb[i][j] = 1;
		if((long long)(v - 1) * (v - 1) >= cnt[i][j]) sa[i + D][j + D] = sa[i][j + D] = sa[i + D][j] = sa[i][j] = 1;
	}
	for(int i = 0; i < 2 * D; i++) for(int j = 0; j < 2 * D; j++) sa[i][j] += sa[i - 1][j] + sa[i][j - 1] - sa[i - 1][j - 1];
	for(int i = 0; i < 2 * D; i++) for(int j = 0; j < 2 * D; j++) sb[i][j] += sb[i - 1][j] + sb[i][j - 1] - sb[i - 1][j - 1];
	for(int i = 0; i < 2 * D; i++) for(int j = 0; j < 2 * D; j++) sc[i][j] += sc[i - 1][j] + sc[i][j - 1] - sc[i - 1][j - 1];
	int r = d % D;
	for(int i = 0; i < D; i++) for(int j = 0; j < D; j++) {
		int ret = sum(sc, i, j, i + r - 1, j + r - 1);
		ret += sum(sb, 0, j, D - 1, j + r - 1) + sum(sb, i, 0, i + r - 1, D - 1) - 2 * sum(sb, i, j, i + r - 1, j + r - 1);
		ret += sum(sa, 0, 0, D - 1, D - 1) - (sum(sa, 0, j, D - 1, j + r - 1) + sum(sa, i, 0, i + r - 1, D - 1) - sum(sa, i, j, i + r - 1, j + r - 1));
		if(ret == D * D) return true;
	}
	return false;
}

int main() {
#ifndef DEBUG
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	scanf("%d%d", &n, &D);
	for(int i = 1; i <= n; i++) { int x, y; scanf("%d%d", &x, &y); cnt[x % D][y % D]++; }
	int l = 1, r = n * D + 1;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", l - 1);
	return 0;
} /*
19 1
1 3
2 3
0 1
1 1
2 1
3 1
4 4
5 4
6 4
7 4
8 4
8 3
8 2
8 1
8 0
7 0
6 0
5 0
4 0
*/