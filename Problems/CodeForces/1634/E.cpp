#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

const int N = 2e5 + 5;

struct Node { int val, id, ans; };
bool operator<(Node x, Node y) { return x.val < y.val; }
std::vector<Node> a[N];
int n;

struct Edge { int to, nxt, id, exist; } edge[N << 2];
int head[N << 1];
void add_edge(int u, int v, int id) { static int k = 2; edge[k] = (Edge){v, head[u], id, 1}, head[u] = k++; }
void add_both(int u, int v, int id) { /* printf("%d: %d <-> %d\n", id, u, v); */ add_edge(u, v, id), add_edge(v, u, id); }

int elem_cnt = 0;
std::vector<int> tmp;
void preprocess() {
	for(int i = 1; i <= n; i++) for(auto j : a[i]) tmp.push_back(j.val);
	std::sort(tmp.begin(), tmp.end());
	tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
	elem_cnt = tmp.size();
	for(int i = 1; i <= n; i++) for(auto &j : a[i]) j.val = std::lower_bound(tmp.begin(), tmp.end(), j.val) - tmp.begin() + 1;
}

int cnt[N], vis[N << 1], info[N << 2][2];
std::vector<int> circle;
void dfs(int u, int fa) {
	// if(vis[u]) return;
	// printf("dfs %d\n", u);
	// vis[u] = true;
	for(int &i = head[u]; i; i = edge[i].nxt) if(edge[i].exist && edge[i].to != fa) {
		int v = edge[i].to;
		edge[i].exist = edge[i ^ 1].exist = 0;
		int oldi = i;
		dfs(v, u);
		circle.push_back(edge[oldi].id);
	}
	// printf("%d ", u);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int len;
		scanf("%d", &len);
		for(int j = 1; j <= len; j++) { int x; scanf("%d", &x); a[i].push_back({x, j, -1}); }
	}
	preprocess();
	int cntid = 0;
	for(int i = 1; i <= n; i++) {
		std::sort(a[i].begin(), a[i].end());
		for(int j = 0; j < (int)a[i].size();)
			if(j < (int)a[i].size() - 1 && a[i][j].val == a[i][j + 1].val) a[i][j].ans = 'L', a[i][j + 1].ans = 'R', j += 2;
			else cnt[a[i][j].val]++, add_both(a[i][j].val, i + elem_cnt, ++cntid), info[cntid][0] = i, info[cntid][1] = j, j++;
	}
	for(int i = 1; i <= elem_cnt; i++) if(cnt[i] & 1) { puts("NO"); return 0; }
	for(int i = elem_cnt + 1; i <= elem_cnt + n; i++) /* if(!vis[i]) */ {
		circle.clear();
		dfs(i, 0);
		int t = 1;
		for(int j : circle) a[info[j][0]][info[j][1]].ans = (t ? 'L' : 'R'), t ^= 1;
	}
	puts("YES");
	for(int i = 1; i <= n; i++) {
		std::sort(a[i].begin(), a[i].end(), [](Node x, Node y) { return x.id < y.id; });
		for(auto j : a[i]) putchar(j.ans);
		puts("");
	}
	return 0;
} /*
3
2
1 2
4
1 2 3 3
6
1 1 2 2 3 3

*/