#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 3e5 + 5;

struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }
int n, m;
int pre[N], fa[N], beside[N], pos[N]; // beside[left] -> right
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[y] = x : 0; } // the order of the arguments is important
std::vector<int> elem[N];

int in[N];
std::vector<int> stk, ans;
bool topo() {
	for(int i = 1; i <= n; i++) for(int j = head[i]; j; j = edge[j].nxt) in[edge[j].to]++;
	int cnt = 0;
	for(int i = 1; i <= n; i++) if(!in[i]) {
		stk.push_back(i), cnt++;
		for(int j : elem[i]) ans.push_back(j);
	}
	while(!stk.empty()) {
		int u = stk.back();
		stk.pop_back();
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			if(!in[v]) continue;
			in[v]--;
			if(!in[v]) {
				stk.push_back(v), cnt++;
				for(int j : elem[v]) ans.push_back(j);
			}
		}
	}
	return cnt == n;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &pre[i]);
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 1; i <= m; i++) { int x, y; scanf("%d%d", &x, &y); merge(x, y); beside[x] = y; }
	for(int i = 1; i <= n; i++) if(find(i) == i) {
		for(int j = i; j; j = beside[j])
			if(pos[j]) { puts("0"); return 0; }
			else elem[i].push_back(j), pos[j] = elem[i].size();
	}
	for(int i = 1; i <= n; i++) if(pre[i]) {
		if(find(pre[i]) != find(i)) add_edge(find(pre[i]), find(i));
		else if(pos[pre[i]] > pos[i]) { puts("0"); return 0; }
	}
	if(topo()) for(int i : ans) printf("%d ", i);
	else puts("0");
	return 0;
}