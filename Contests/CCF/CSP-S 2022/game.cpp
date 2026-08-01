#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;
const int NONE = 1e9 + 1;

int n, m, Q;
int a[N], b[N];

struct ST {
	int lg[N], mn[N][21], mx[N][21];
	int calcmin(int x, int y) { return x == NONE || y == NONE ? (x == NONE ? y : x) : std::min(x, y); }
	int calcmax(int x, int y) { return x == NONE || y == NONE ? (x == NONE ? y : x) : std::max(x, y); }
	void preprocess(int *arr, int bd, int type) {
		lg[0] = -1;
		for(int i = 1; i <= bd; i++) lg[i] = lg[i >> 1] + 1;
		for(int i = 1; i <= bd; i++) mn[i][0] = mx[i][0] = (type == 2 ? arr[i] : (type == 1 ? (arr[i] >= 0 ? arr[i] : NONE) : (arr[i] <= 0 ? arr[i] : NONE)));
		for(int j = 1; j <= 20; j++)
			for(int i = 1; i + (1 << j) - 1 <= bd; i++) {
				mn[i][j] = calcmin(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
				mx[i][j] = calcmax(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
			}
	}
	int getmin(int l, int r) {
		int k = lg[r - l + 1];
		return calcmin(mn[l][k], mn[r - (1 << k) + 1][k]);
	}
	int getmax(int l, int r) {
		int k = lg[r - l + 1];
		return calcmax(mx[l][k], mx[r - (1 << k) + 1][k]);
	}
} sta[2], stb;

int main() {
//#ifndef DEBUG
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
//#endif
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
	sta[0].preprocess(a, n, 0), sta[1].preprocess(a, n, 1), stb.preprocess(b, m, 2);
	while(Q--) {
		int l1, r1, l2, r2;
		scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
		int mn2 = stb.getmin(l2, r2), mx2 = stb.getmax(l2, r2);
		LL ans = -LLINF;
		if(mn2 >= 0 && sta[1].getmax(l1, r1) != NONE) ans = std::max(ans, (LL)sta[1].getmax(l1, r1) * mn2);
		if(mn2 <= 0 && sta[1].getmin(l1, r1) != NONE) ans = std::max(ans, (LL)sta[1].getmin(l1, r1) * mn2);
		if(mx2 >= 0 && sta[0].getmax(l1, r1) != NONE) ans = std::max(ans, (LL)sta[0].getmax(l1, r1) * mx2);
		if(mx2 <= 0 && sta[0].getmin(l1, r1) != NONE) ans = std::max(ans, (LL)sta[0].getmin(l1, r1) * mx2);
		printf("%lld\n", ans);
	}
	return 0;
}
