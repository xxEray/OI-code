#include <bits/stdc++.h>

const int N = 4e5 + 5;
const int MAXV = 1e6 + 5;

int n, m;
int a[N], b[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N], fa[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

std::vector<int> minimum_expression(const std::vector<int> &vct) {
	int len = vct.size();
	int i = 0, j = 1, k = 0;
	while(k < len && i < len && j < len) {
		if(vct[(i + k) % len] == vct[(j + k) % len]) k++;
		else {
			if(vct[(i + k) % len] < vct[(j + k) % len]) j = j + k + 1;
			else i = i + k + 1;
			if(i == j) j++;
			k = 0;
		}
	}
	i = std::min(i, j);
	std::vector<int> ret(vct.begin() + i, vct.end());
	ret.insert(ret.end(), vct.begin(), vct.begin() + i);
	// printf("minimum_expression:\n "); for(int x : vct) printf("%d ", x); puts("");
	// printf(" "); for(int x : ret) printf("%d ", x); puts("");
	return ret;
}

int fath[N];
bool odd[N], simple[N];
int cnt[N];
std::vector<int> vct[N];
int find(int x) { return x == fath[x] ? x : fath[x] = find(fath[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? cnt[y] += cnt[x], odd[y] &= odd[x], simple[y] &= simple[x], fath[x] = y : 0; }

int dep[N], c[N];
void dfs(int u) {
	dep[u] = dep[fa[u]] + 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		if(dep[v]) {
			if(dep[v] < dep[u]) {
				// printf("u = %d, v = %d\n", u, v);
				c[u]++, c[v]--;
				odd[v] &= ~(dep[v] - dep[u]) & 1;
				cnt[v]++;
			}
		} else {
			fa[v] = u;
			dfs(v);
		}
	}
}

void dfs2(int u) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		if(dep[v] == dep[u] + 1) {
			dfs2(v);
			c[u] += c[v];
		}
	}
	if(c[u] > 1) simple[find(u)] = false;
	if(c[u]) merge(u, fa[u]);
}

struct BIT {
	int t[MAXV];
	void add(int x, int v) { while(x <= 1000002) t[x] ^= v, x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret ^= t[r], r -= r & -r; return ret; }
	int query(int l, int r) { return query(r) - query(l - 1); }
} bit;
int tin[MAXV];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]), a[i]++, b[i]++;
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) odd[i] = true, simple[i] = true, fath[i] = i;
	std::vector<int> roots;
	for(int i = 1; i <= n; i++) if(!dep[i]) dfs(i), roots.emplace_back(i);
	// for(int i = 1; i <= n; i++) printf("%d: fa=%d\n", i, fa[i]);
	for(int u : roots) dfs2(u);
	for(int i = 1; i <= n; i++) vct[find(i)].emplace_back(i);
	// for(int i = 1; i <= n; i++) if(find(i) == i) {
	// 	printf("%d: odd=%d, simple=%d, cnt=%d, ", i, odd[i], simple[i], cnt[i]);
	// 	for(int x : vct[i]) printf("%d ", x);
	// 	puts("");
	// }
	bool flag = true;
	for(int i = 1; i <= n; i++) if(find(i) == i) {
		bool same = true;
		for(int j : vct[i]) tin[a[j]]++, tin[b[j]]--;
		for(int j : vct[i]) same &= !tin[a[j]] && !tin[b[j]];
		for(int j : vct[i]) tin[a[j]]--, tin[b[j]]++;
		if(!same) { flag = false; continue; }
		if(cnt[i] == 1) {
			std::vector<int> va, vb;
			for(int j : vct[i]) va.emplace_back(a[j]), vb.emplace_back(b[j]);
			if(minimum_expression(va) != minimum_expression(vb)) flag = false;
		} else if(odd[i] && simple[i]) {
			bool duplicated = false;
			for(int j : vct[i]) {
				if(tin[a[j]]) duplicated = true;
				tin[a[j]]++;
			}
			for(int j : vct[i]) tin[a[j]]--;
			if(!duplicated) {
				int sum = 0;
				for(int j : vct[i]) sum ^= bit.query(a[j] + 1, 1000002), bit.add(a[j], 1);
				for(int j : vct[i]) bit.add(a[j], 1);
				for(int j : vct[i]) sum ^= bit.query(b[j] + 1, 1000002), bit.add(b[j], 1);
				for(int j : vct[i]) bit.add(b[j], 1);
				if(sum) flag = false;
			}
		}
	}
	puts(flag ? "possible" : "impossible");
	return 0;
} /*
6 6
1 2
2 3
3 1
2 3
3 4
4 2
1 2
2 3
1 3
4 5
5 6
4 6

*/