#include <bits/stdc++.h>

const int N = 4e5 + 5;

int n, m;

int pos[N];
int trie[N][30];
std::vector<int> id[N];
int ctrie;

char tmp[N];
std::vector<std::pair<int, int>> qr[N];

int fail[N], c[N][30];
std::vector<int> end[N];
int cc;
void build_AC() {
	std::queue<int> q;
	for(int i = 0; i < 26; i++) if(c[0][i]) q.push(c[0][i]);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		// printf("u = %d\n", u);
		for(int i = 0; i < 26; i++)
			if(c[u][i]) fail[c[u][i]] = c[fail[u]][i], q.push(c[u][i]);
			else c[u][i] = c[fail[u]][i];
		// for(int i = 0; i < 26; i++) printf("c[%d][%d] = %d\n", u, i, c[u][i]);
	}
	// for(int i = 1; i <= cc; i++) printf("fail[%d] = %d\n", i, fail[i]);
}

struct BIT {
	int t[N];
	void add(int x, int v) { while(x <= cc + 1) t[x] += v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	int query(int l, int r) { return query(r) - query(l - 1); }
} bit;

std::vector<int> to[N];
int dfn[N], sz[N], time_stamp;
void predfs(int u) {
	dfn[u] = ++time_stamp;
	sz[u] = 1;
	for(int v : to[u]) {
		predfs(v);
		sz[u] += sz[v];
	}
}

int out[N];
void dfs(int u, int now) {
	// printf("dfs %d %d\n", u, now);
	bit.add(dfn[now], 1);
	// for(int x = now; x; x = fail[x]) for(int y : end[x]) cnt[y]++;
	for(auto x : id[u]) for(auto [qid, y] : qr[x]) out[qid] = bit.query(dfn[y], dfn[y] + sz[y] - 1);
	for(int i = 0; i < 26; i++) if(trie[u][i]) dfs(trie[u][i], c[now][i]);
	// for(int x = now; x; x = fail[x]) for(int y : end[x]) cnt[y]--;
	bit.add(dfn[now], -1);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int t;
		char str[3];
		scanf("%d", &t);
		if(t == 1) {
			scanf("%s", str);
			int ch = str[0] - 'a';
			if(!trie[0][ch]) trie[0][ch] = ++ctrie;
			pos[i] = trie[0][ch], id[pos[i]].emplace_back(i);
		} else {
			scanf("%d%s", &t, str);
			int ch = str[0] - 'a';
			if(!trie[pos[t]][ch]) trie[pos[t]][ch] = ++ctrie;
			pos[i] = trie[pos[t]][ch], id[pos[i]].emplace_back(i);
		}
	}
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) {
		int t;
		scanf("%d%s", &t, tmp);
		int p = 0, len = strlen(tmp);
		for(int j = 0; j < len; j++) {
			if(!c[p][tmp[j] - 'a']) c[p][tmp[j] - 'a'] = ++cc;
			p = c[p][tmp[j] - 'a'];
		}
		qr[t].emplace_back(i, p);
	}
	build_AC();
	// for(int i = 0; i <= ctrie; i++) for(int j = 0; j < 26; j++) if(trie[i][j]) printf("trie[%d][%d] = %d\n", i, j, trie[i][j]);
	for(int i = 1; i <= cc; i++) to[fail[i]].emplace_back(i);
	predfs(0);
	dfs(0, 0);
	for(int i = 1; i <= m; i++) printf("%d\n", out[i]);
	return 0;
} /*
1
1 a
1
1 a
*/