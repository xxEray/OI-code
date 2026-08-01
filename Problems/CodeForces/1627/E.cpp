// After contest
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

typedef long long LL;

const int N = 2e5 + 10;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

struct Node { int x, y, id; } a[N];
LL val[N];
int n, m, K, mx;

std::vector<int> row[N];
std::pair<int, LL> ladder[N];

LL f[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		mx = 0;
		scanf("%d%d%d", &n, &m, &K);
		for(int i = 1; i <= 2 * K + 2; i++) ladder[i] = {-1, -1};
		for(int i = 1; i <= 2 * K + 2; i++) f[i] = LLINF;
		for(int i = 1; i <= n; i++) row[i].clear();
		for(int i = 1; i <= n; i++) scanf("%lld", &val[i]);
		for(int i = 1; i <= K; i++) {
			mx++; scanf("%d%d", &a[mx].x, &a[mx].y);
			mx++; scanf("%d%d", &a[mx].x, &a[mx].y);
			LL x; scanf("%lld", &x); ladder[mx] = {mx - 1, -x};
		}
		int st, ed;
		mx++; a[mx].x = 1, a[mx].y = 1; st = mx;
		mx++; a[mx].x = n, a[mx].y = m; ed = mx;
		for(int i = 1; i <= mx; i++) row[a[i].x].push_back(i);
		for(int i = 1; i <= n; i++) std::sort(row[i].begin(), row[i].end(), [](int x, int y) { return a[x].y < a[y].y; });
		f[st] = 0;
		for(int i = 1; i <= n; i++) {
			int sz = row[i].size();
			for(int j : row[i]) if(ladder[j].first != -1) f[j] = f[ladder[j].first] + ladder[j].second;
			for(int j = 1; j < sz; j++) f[row[i][j]] = std::min(f[row[i][j]], f[row[i][j - 1]] + val[i] * (a[row[i][j]].y - a[row[i][j - 1]].y));
			for(int j = sz - 2; j >= 0; j--) f[row[i][j]] = std::min(f[row[i][j]], f[row[i][j + 1]] + val[i] * (a[row[i][j + 1]].y - a[row[i][j]].y));
		}
		if(f[ed] >= LLINF / 2) puts("NO ESCAPE");
		else printf("%lld\n", f[ed]);
	}
	return 0;
}