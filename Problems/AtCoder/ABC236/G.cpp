#include <cstdio>
#include <algorithm>
#include <cassert>

const int N = 100 + 5;
const int INF = 0x3f3f3f3f;

int n, m, L;

struct Matrix {
	int a[N][N], r, c;
	Matrix &operator*=(Matrix &x) {
		assert(c == x.r);
		Matrix ret;
		ret.r = r, ret.c = x.c;
		for(int i = 1; i <= ret.r; i++) for(int j = 1; j <= ret.c; j++) ret.a[i][j] = INF;
		for(int i = 1; i <= r; i++)
			for(int j = 1; j <= c; j++)
				for(int k = 1; k <= x.c; k++)
					ret.a[i][k] = std::min(ret.a[i][k], std::max(a[i][j], x.a[j][k]));
		return *this = ret;
	}
} dp, w;

int main() {
	scanf("%d%d%d", &n, &m, &L);
	w.r = w.c = n, dp.r = 1, dp.c = n;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) w.a[i][j] = INF;
	for(int i = 1; i <= m; i++) { int x, y; scanf("%d%d", &x, &y); w.a[x][y] = i; }
	for(int i = 2; i <= n; i++) dp.a[1][i] = INF;
	while(true) {
		if(L & 1) dp *= w;
		if(!(L >>= 1)) break;
		w *= w;
	}
	for(int i = 1; i <= n; i++) printf("%d ", dp.a[1][i] >= INF ? -1 : dp.a[1][i]);
	return 0;
}