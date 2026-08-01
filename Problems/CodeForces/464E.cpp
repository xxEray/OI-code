#include <bits/stdc++.h>

typedef long long LL;

const int V = 2e5 + 50;
const int N = V + 5;
const int MOD = 1e9 + 7;

int n, m;
struct Edge { int to, nxt, w; } edge[N << 1];
int head[N];
void add_edge(int u, int v, int w) { static int k = 1; edge[k] = (Edge){v, head[u], w}, head[u] = k++; }

LL power[N];

struct SegNode { int ls, rs, hash, lazy; } t[N * 200];
int cnt = 0;
int copy(int x) { cnt++; assert(cnt < N * 200); t[cnt] = t[x]; return cnt; }
void setlazy(int x) { assert(x); t[x].hash = 0, t[x].lazy = 1; }
void lazydown(int x) {
	assert(x);
	if(t[x].lazy) t[x].ls = copy(t[x].ls), t[x].rs = copy(t[x].rs), setlazy(t[x].ls), setlazy(t[x].rs), t[x].lazy = 0;
}
struct SegmentTree {
	int rt;
	void assign(int ql, int qr) { assign(ql, qr, rt, 0, V); }
	void assign(int ql, int qr, int &x, int l, int r) {
		if(ql > qr) return;
		x = copy(x);
		if(ql <= l && r <= qr) { setlazy(x); return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(ql <= mid) assign(ql, qr, t[x].ls, l, mid);
		if(qr > mid) assign(ql, qr, t[x].rs, mid + 1, r);
		t[x].hash = (t[t[x].ls].hash + t[t[x].rs].hash * power[mid - l + 1]) % MOD;
	}
	void modify(int qind, int qv) { return modify(qind, qv, rt, 0, V); }
	void modify(int qind, int qv, int &x, int l, int r) {
		x = copy(x);
		if(l == r) { t[x].lazy = 0, t[x].hash = qv; return; }
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qind <= mid) modify(qind, qv, t[x].ls, l, mid);
		else modify(qind, qv, t[x].rs, mid + 1, r);
		t[x].hash = (t[t[x].ls].hash + t[t[x].rs].hash * power[mid - l + 1]) % MOD;
	}
	int get(int ql, int qr) { return get(ql, qr, rt, 0, V); }
	int get(int ql, int qr, int x, int l, int r) {
		if(ql > qr || !x) return 0;
		if(ql <= l && r <= qr) return t[x].hash;
		int mid = (l + r) >> 1;
		lazydown(x);
		if(qr <= mid) return get(ql, qr, t[x].ls, l, mid);
		else if(ql > mid) return get(ql, qr, t[x].rs, mid + 1, r);
		else return (get(ql, qr, t[x].ls, l, mid) + get(ql, qr, t[x].rs, mid + 1, r) * power[mid - std::max(l, ql) + 1]) % MOD;
	}
	SegmentTree() {}
	SegmentTree(const SegmentTree &rhs) { rt = copy(rhs.rt); }
	SegmentTree &operator=(const SegmentTree &rhs) { rt = copy(rhs.rt); return *this; }
};
int compare(int p, int q, int l = 0, int r = V) {
	// printf("compare %d %d %d %d\n", p, q, l, r);
	if(!p || !q || l == r) return t[p].hash < t[q].hash ? -1 : (t[p].hash > t[q].hash ? 1 : 0);
	int mid = (l + r) >> 1;
	lazydown(p), lazydown(q);
	// printf("t[p].rs = %d, t[t[p].rs].hash = %d, t[q].rs = %d, t[t[q].rs].hash = %d\n", t[p].rs, t[t[p].rs].hash, t[q].rs, t[t[q].rs].hash);
	if(t[t[p].rs].hash == t[t[q].rs].hash) return compare(t[p].ls, t[q].ls, l, mid);
	else return compare(t[p].rs, t[q].rs, mid + 1, r);
}
bool operator<(const SegmentTree &x, const SegmentTree &y) { return compare(x.rt, y.rt) == -1; }
SegmentTree add(const SegmentTree &x, int v) {
	SegmentTree y = x;
	int l = v, r = V;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(y.get(v, mid) == (power[mid - v + 1] + MOD - 1) % MOD) l = mid + 1;
		else r = mid;
	}
	// printf("add %d, %d: l = %d,", y.get(0, V), v, l);
	y.assign(v, l - 1), y.modify(l, 1);
	// printf("=> %d\n", y.get(0, V));
	return y;
}

SegmentTree dis[N];
int last[N];

std::vector<int> path;
void get_path(int u) {
	if(last[u]) get_path(last[u]);
	path.push_back(u);
}

bool vis[N];

int main() {
	// freopen("in.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);
	power[0] = 1;
	for(int i = 1; i <= V; i++) power[i] = power[i - 1] * 2 % MOD;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add_edge(u, v, w), add_edge(v, u, w); }
	int src, dst;
	scanf("%d%d", &src, &dst);
	std::priority_queue<std::pair<SegmentTree, int>, std::vector<std::pair<SegmentTree, int>>, std::greater<std::pair<SegmentTree, int>>> q;
	for(int i = 1; i <= n; i++) dis[i].modify(V, 1);
	dis[src].modify(V, 0);
	q.push({dis[src], src});
	while(!q.empty()) {
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		// printf("%d: dis = %d\n", u, dis[u].get(0, V));
		for(int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to;
			auto &&wu = add(dis[u], edge[i].w);
			// printf("v = %d, dis[v] = %d, wu = %d\n", v, dis[v].get(0, V), wu.get(0, V));
			if(wu < dis[v]) {
				dis[v] = wu;
				q.push({dis[v], v});
				last[v] = u;
			}
		}
	}
	if(src != dst && !last[dst]) { puts("-1"); return 0; }
	printf("%d\n", dis[dst].get(0, V));
	get_path(dst);
	printf("%d\n", (int)path.size());
	for(int x : path) printf("%d ", x);
	puts("");
	return 0;
} /*
4 4
1 4 20000
1 2 10000
2 3 10000
3 4 10000
1 4

*/