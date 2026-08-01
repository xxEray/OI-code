#include "testlib.h"

const int N = 1000 + 5;
const int M = 1e6 + 5;
const int INF = 0x3f3f3f3f3f3f3f3f;

int n, m;
int a[N], b[M];

int cnt[N];
int vis[N];

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);
	n = inf.readInt(3, 1000, "n");
	for(int i = 1; i <= n; i++) a[i] = inf.readInt(1, n, "a[" + std::to_string(i) + "]");
	for(int i = 1; i <= n; i++) cnt[a[i]]++;
	for(int i = 1; i <= n; i++) ensure(cnt[i] == 1);
	m = ouf.readInt(n, INT_MAX, "L");
	if(m > 550000) quitf(_wa, "L = %d, which is greater than 5.5e5.\n", m);
	for(int i = 1; i <= m; i++) b[i] = ouf.readInt();
	for(int i = 1; i <= n; i++) if(b[i] != i) quitf(_wa, "b[%d] = %d, which is not equal to %d!\n", i, b[i], i);
	for(int i = 1; i <= n; i++) if(b[m - n + i] != a[i]) quitf(_wa, "b[L - n + %d] = %d which is not equal to a[%d]!\n", i, b[n - m + i], a[i]);
	for(int i = 1; i <= n; i++) vis[i] = -INF;
	for(int i = 1; i <= n - 1; i++) vis[b[i]] = i;
	for(int i = n; i <= m; i++) {
		if(vis[b[i]] >= i - (n - 2)) quitf(_wa, "b[%d] appears in b[%d .. %d]!\n", i, i - n + 2, i - 1);
		vis[b[i]] = i;
	}
	quitf(_ok, "correct.");
	return 0;
}