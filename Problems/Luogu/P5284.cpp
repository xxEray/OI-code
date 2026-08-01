#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cassert>
#include <map>

typedef long long LL;
const int N = 6e5 + 5;

int n, nA, nB, m;
char s[N];
struct Node { int l, r, id, bl, now; } a[N * 2];

int len[N * 2], last[N * 2], pos[N * 2];
bool isend[N * 4];

std::vector<std::pair<int, int>> to[N * 4];

struct SAM {
	struct State { int len, link; std::map<int, int> next; } t[N * 2];
	int tot, last;
	SAM() : tot(1), last(0) { t[0].len = 0, t[0].link = -1, t[0].next.clear(); }
	void init() { tot = 1, last = 0, t[0].len = 0, t[0].link = -1, t[0].next.clear(); }
	void insert(int c) {
		int cur = tot++, p = last;
		t[cur].len = t[last].len + 1, t[cur].next.clear();
		last = cur;
		for(; ~p && !t[p].next[c]; p = t[p].link) t[p].next[c] = cur;
		if(p == -1) t[cur].link = 0;
		else {
			int q = t[p].next[c];
			if(t[p].len + 1 == t[q].len) t[cur].link = q;
			else {
				int clone = tot++;
				t[clone].len = t[p].len + 1;
				t[clone].link = t[q].link, t[q].link = clone;
				t[clone].next = t[q].next;
				t[cur].link = clone;
				for(; ~p && t[p].next[c] == q; p = t[p].link) t[p].next[c] = clone;
			}
		}
	}
} sam;

int tot;

int go[21][N * 2];
void preprocess() {
	pos[n + 1] = 0;
	for(int i = n; i >= 1; i--) pos[i] = sam.t[pos[i + 1]].next[s[i]];
	for(int i = 1; i <= tot; i++) go[0][i] = sam.t[i].link;
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= tot; i++)
			go[j][i] = go[j - 1][go[j - 1][i]];
}

int find(int l, int r) {
	int now = pos[l];
	for(int i = 20; i >= 0; i--) if(go[i][now] && sam.t[go[i][now]].len >= r - l + 1) now = go[i][now];
	assert(now);
	return now;
}

int vis[N * 4];
LL f[N * 4];
bool flag;
LL dfs(int u) {
	if(vis[u]) { flag |= (vis[u] == 1); return f[u]; }
	vis[u] = 1;
	LL ret = 0;
	for(auto &p : to[u]) {
		int v = p.first, w = p.second;
		LL val = dfs(v);
		if(isend[v]) ret = std::max(ret, val + w), isend[u] = true;
	}
	vis[u] = 2;
	return f[u] = ret;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		sam.init();
		for(int i = n; i >= 1; i--) sam.insert(s[i]);
		tot = sam.tot - 1;
		// for(int i = 0; i <= tot; i++) for(auto &p : sam.t[i].next) printf("%d %d %c\n", i, p.second, p.first);
		// for(int i = 1; i <= tot; i++) printf("%d %d link\n", sam.t[i].link, i);
		preprocess();
		scanf("%d", &nA);
		for(int i = 1; i <= nA; i++) scanf("%d%d", &a[i].l, &a[i].r), a[i].bl = find(a[i].l, a[i].r), a[i].id = i;
		scanf("%d", &nB);
		for(int i = nA + 1; i <= nA + nB; i++) scanf("%d%d", &a[i].l, &a[i].r), a[i].bl = find(a[i].l, a[i].r), a[i].id = i;
		for(int i = 0; i <= tot + nA + nB; i++) to[i].clear();
		for(int i = 1; i <= tot; i++) {
			int p = sam.t[i].link;
			len[i] = sam.t[i].len;
			last[i] = to[p].size();
			to[p].push_back({i, len[i] - sam.t[p].len});
		}
		std::sort(a + 1, a + nA + nB + 1, [&](Node x, Node y) { return x.r - x.l == y.r - y.l ? x.id < y.id : x.r - x.l > y.r - y.l; });
		for(int i = 0; i <= tot; i++) isend[i] = false;
		for(int i = 1; i <= nA + nB; i++) {
			int u = sam.t[a[i].bl].link, v = to[u][last[a[i].bl]].first;
			a[i].now = tot + i;
			isend[a[i].now] = (a[i].id <= nA);
			to[u][last[a[i].bl]] = {a[i].now, (a[i].r - a[i].l + 1) - sam.t[u].len};
			to[a[i].now].push_back({v, len[a[i].bl] - (a[i].r - a[i].l + 1)});
			len[a[i].bl] = a[i].r - a[i].l + 1;
		}
		std::sort(a + 1, a + nA + nB + 1, [&](Node x, Node y) { return x.id < y.id; });
		scanf("%d", &m);
		for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); to[a[u].now].push_back({a[nA + v].now, a[nA + v].r - a[nA + v].l + 1}); }
		// for(int i = 0; i <= tot + nA + nB; i++) for(auto &p : to[i]) printf("%d -> %d  w=%d\n", i, p.first, p.second);
		for(int i = 0; i <= tot + nA + nB; i++) vis[i] = 0, f[i] = 0;
		flag = false;
		LL ans = dfs(0);
		if(flag) puts("-1");
		else printf("%lld\n", ans);
	}
	return 0;
}