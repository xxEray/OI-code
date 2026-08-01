#include <cstdio>
#include <algorithm>
using std::abs;

const int N = 2e5 + 5;

int a[N];
int n, m, Q;

int lg[N], mx[N][21];
void preprocess() {
	lg[0] = -1;
	for(int i = 1; i <= m; i++) lg[i] = lg[i >> 1] + 1;
	for(int i = 1; i <= m; i++) mx[i][0] = a[i];
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i + (1 << j) - 1 <= m; i++)
			mx[i][j] = std::max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
}
int max_of(int l, int r) {
	if(l > r) return 0;
	int k = lg[r - l + 1];
	return std::max(mx[l][k], mx[r - (1 << k) + 1][k]);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) scanf("%d", &a[i]);
	preprocess();
	scanf("%d", &Q);
	while(Q--) {
		int sx, sy, tx, ty, K;
		scanf("%d%d%d%d%d", &sx, &sy, &tx, &ty, &K);
		if(sy > ty) std::swap(sx, tx), std::swap(sy, ty);
		if(abs(sx - tx) % K || abs(sy - ty) % K) { puts("NO"); continue; }
		int top = sx + (n - sx) / K * K;
		if(max_of(sy + 1, ty - 1) >= top) { puts("NO"); continue; }
		puts("YES");
	}
	return 0;
}