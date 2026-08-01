#include <cstdio>
#include <algorithm>
using std::min;
using std::max;

const int N = 60 + 5;
const int INF = 0x3f3f3f3f;

int a[N][2], b[N][2];
int na, nb, n;

int f[N][N][N][2], mxf[N][N], g[N][N];

template<typename T> void chkmin(T &x, T y) { x > y ? x = y : 0; }
template<typename T> void chkmax(T &x, T y) { x < y ? x = y : 0; }

bool check(int x) {
	for(int i = 0; i <= n; i++) for(int j = 0; j <= na; j++) mxf[i][j] = -INF, g[i][j] = -INF;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= na; j++)
			for(int k = 0; k <= nb; k++)
				if(min(f[i][j][k][0], f[i][j][k][1]) <= x) chkmax(mxf[i][j], k);
	g[0][0] = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= na; j++)
			for(int k = 0; k <= j; k++)
				chkmax(g[i][j], g[i - 1][j - k] + mxf[i][k]);
	return g[n][na] >= nb;
}

int main() {
	scanf("%d%d%d", &na, &nb, &n);
	for(int i = 1; i <= n; i++) scanf("%d%d%d%d", &a[i][0], &a[i][1], &b[i][0], &b[i][1]);
	for(int i = 1; i <= n; i++)
		for(int ca = 0; ca <= na; ca++)
			for(int cb = 0; cb <= nb; cb++) {
				if(ca || cb) f[i][ca][cb][0] = f[i][ca][cb][1] = INF;
				else f[i][0][0][0] = f[i][0][0][1] = 0;
				for(int j = 1; j <= ca; j++) chkmin(f[i][ca][cb][0], f[i][ca - j][cb][1] + a[i][0] + j * j * b[i][0]);
				for(int j = 1; j <= cb; j++) chkmin(f[i][ca][cb][1], f[i][ca][cb - j][0] + a[i][1] + j * j * b[i][1]);
			}
	// for(int i = 1; i <= n; i++) for(int j = 0; j <= na; j++) for(int k = 0; k <= nb; k++) printf("f[%d][%d][%d] = %d\n", i, j, k, min(f[i][j][k][0], f[i][j][k][1]));
	int l = 0, r = 1e9;
	while(l < r) {
		int mid = l + ((r - l) >> 1);
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", l);
	return 0;
}