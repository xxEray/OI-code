#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

const int N = 200 + 5;
const int VAL = 1e7 + 5;

int n;
int a[N], b[VAL];

bool isprm[VAL];
void sieve(int mx) {
	for(int i = 2; i <= mx; i++) isprm[i] = true;
	for(int i = 2; i <= mx; i++) if(isprm[i])
		for(int j = i + i; j <= mx; j += i) isprm[j] = false;
	isprm[2] = false;
}

std::vector<int> to[N];
int match[N], vis[N];
bool dfs(int u, int tag) {
	if(vis[u] == tag) return false;
	vis[u] = tag;
	for(int v : to[u]) if(!match[v] || dfs(match[v], tag)) { match[u] = v, match[v] = u; return true; }
	return false;
}

int main() {
	sieve(1e7 + 1);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); b[x] = 1; }
	for(int i = 10000001; i >= 1; i--) b[i] = b[i] ^ b[i - 1];
	int m = 0;
	int cnt[2] = {0, 0};
	for(int i = 1; i <= 10000001; i++) if(b[i] == 1) a[++m] = i, cnt[i & 1]++;
	// for(int i = 1; i <= m; i++) printf("%d ", a[i]);
	for(int i = 1; i <= m; i++) for(int j = i + 1; j <= m; j++) if(isprm[a[j] - a[i]]) to[i].push_back(j), to[j].push_back(i);
	int ans = 0;
	for(int i = 1; i <= m; i++) if((a[i] & 1) && dfs(i, i)) ans++;
	cnt[0] -= ans, cnt[1] -= ans;
	ans += cnt[0] / 2 * 2 + cnt[1] / 2 * 2;
	if(cnt[0] & 1) assert(cnt[1] & 1), ans += 3;
	printf("%d\n", ans);
	return 0;
}