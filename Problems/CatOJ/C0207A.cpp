#include <cstdio>
#include <algorithm>
#include <queue>
#include <array>
#include <vector>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m, K, Q;
std::vector<int> st, remain;

inline int hsh(int x, int y, int z) { return (x - 1) * m * K + (y - 1) * K + z; }

bool vis[N];
int dis[N];
int xof[N], yof[N], zof[N];
const int dirx[6] = {1, -1, 0, 0, 0, 0};
const int diry[6] = {0, 0, 1, -1, 0, 0};
const int dirz[6] = {0, 0, 0, 0, 1, -1};
int q[N];
void remake() {
	int hd = 0, tl = 0;
	for(int p : remain) st.push_back(p);
	remain.clear();
	for(int i = 1; i <= n * m * K; i++) dis[i] = INF, vis[i] = false;
	for(int p : st) dis[p] = 0, vis[p] = true, q[tl++] = p;
	while(hd < tl) {
		int p = q[hd++];
		for(int d = 0; d < 6; d++) {
			int tx = xof[p] + dirx[d], ty = yof[p] + diry[d], tz = zof[p] + dirz[d];
			int pp = hsh(tx, ty, tz);
			if(!(1 <= tx && tx <= n && 1 <= ty && ty <= m && 1 <= tz && tz <= K) || vis[pp]) continue;
			vis[pp] = true;
			dis[pp] = dis[p] + 1;
			q[tl++] = pp;
		}
	}
}

int main() {
	scanf("%d%d%d%d", &n, &m, &K, &Q);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) for(int k = 1; k <= K; k++) xof[hsh(i, j, k)] = i, yof[hsh(i, j, k)] = j, zof[hsh(i, j, k)] = k;
	remake();
	for(int qid = 1; qid <= Q; qid++) {
		if(qid % 1000 == 0) remake();
		int t, x, y, z;
		scanf("%d%d%d%d", &t, &x, &y, &z);
		if(t == 1) remain.push_back(hsh(x, y, z));
		else {
			int ans = dis[hsh(x, y, z)];
			for(int p : remain) ans = std::min(ans, std::abs(x - xof[p]) + std::abs(y - yof[p]) + std::abs(z - zof[p]));
			printf("%d\n", ans);
		}
	}
	return 0;
}