#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const int M = 5e5 + 5;

int n, Q;
struct Node { int l, r; } a[N];
char str[M];

int end[N];

int trie[M][2], fail[M];
int tot;
void build_AC() {
	std::queue<int> q;
	if(trie[0][0]) q.push(trie[0][0]);
	if(trie[0][1]) q.push(trie[0][1]);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i : {0, 1})
			if(trie[u][i]) fail[trie[u][i]] = trie[fail[u]][i], q.push(trie[u][i]);
			else trie[u][i] = trie[fail[u]][i];
	}
}

int go[2][M][31];
LL tag[2][M][31];

int solve(int st, int ql, int qr, int l = 0, int r = (1 << 30) - 1) {
	if(ql <= l && r <= qr) {
		int idx = __builtin_popcount(l) & 1, idx2 = __builtin_ctz(~(l ^ r));
		tag[idx][st][idx2]++;
		// printf("tag[%d][%d][%d]++\n", idx, st, idx2);
		return go[idx][st][idx2];
	}
	int mid = (l + r) >> 1;
	if(ql <= mid) st = solve(st, ql, qr, l, mid);
	if(qr > mid) st = solve(st, ql, qr, mid + 1, r);
	return st;
}

std::vector<int> son[M * 2];
LL w[M * 2];

void dfs(int u) {
	for(int v : son[u]) {
		dfs(v);
		w[u] += w[v];
	}
}

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].l, &a[i].r);
	for(int i = 1; i <= Q; i++) {
		scanf("%s", str);
		int len = strlen(str);
		int now = 0;
		for(int j = 0; j < len; j++) {
			if(!trie[now][str[j] - '0']) trie[now][str[j] - '0'] = ++tot;
			now = trie[now][str[j] - '0'];
		}
		end[i] = now;
		// printf("end = %d\n", end[i]);
	}
	build_AC();
	for(int i = 0; i <= tot; i++) go[0][i][0] = trie[i][0], go[1][i][0] = trie[i][1];
	for(int j = 1; j <= 30; j++) for(int i = 0; i <= tot; i++) {
		go[0][i][j] = go[1][go[0][i][j - 1]][j - 1];
		go[1][i][j] = go[0][go[1][i][j - 1]][j - 1];
	}
	int now = 0;
	for(int i = 1; i <= n; i++) now = solve(now, a[i].l, a[i].r);
	w[now]++;
	for(int j = 30; j >= 1; j--) for(int i = 0; i <= tot; i++) {
		tag[0][i][j - 1] += tag[0][i][j], tag[1][go[0][i][j - 1]][j - 1] += tag[0][i][j];
		tag[1][i][j - 1] += tag[1][i][j], tag[0][go[1][i][j - 1]][j - 1] += tag[1][i][j];
	}
	for(int i = 0; i <= tot; i++) w[i] += tag[0][i][0] + tag[1][i][0];
	for(int i = 1; i <= tot; i++) son[fail[i]].emplace_back(i);
	// for(int i = 0; i <= tot; i++) printf("%d: fail=%d, trie=%d %d, w=%d\n", i, fail[i], trie[i][0], trie[i][1], w[i]);
	dfs(0);
	for(int i = 1; i <= Q; i++) printf("%lld\n", w[end[i]]);
	return 0;
}