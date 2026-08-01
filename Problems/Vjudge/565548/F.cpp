#include <bits/stdc++.h>

const int N = 70000 + 5;
const int M = 150000 + 5;
const int INF = 0x3f3f3f3f;

int n, m, W, H;
struct Node { int x, y; } a[N];
struct Edge { int p, l, r, d, u, w; } e[M];
std::vector<int> to[N];

int dis[N];
bool vis[M];

struct SegmentTree {
	std::set<std::pair<int, int>> t[N << 2];
	void insert(int qx, int qy, int qid, int x = 1, int l = 1, int r = W) {
		t[x].insert({qy, qid});
		if(l == r) return;
		int mid = (l + r) >> 1;
		if(qx <= mid) insert(qx, qy, qid, x << 1, l, mid);
		else insert(qx, qy, qid, x << 1 | 1, mid + 1, r);
	}
	void query(int ql, int qr, int qd, int qu, std::vector<int> &ret, int x = 1, int l = 1, int r = W) {
		if(ql <= l && r <= qr) {
			auto it = t[x].lower_bound({qd, 0});
			while(it != t[x].end() && it->first <= qu) ret.push_back(it->second), it++;
			return;
		}
		int mid = (l + r) >> 1;
		if(ql <= mid) query(ql, qr, qd, qu, ret, x << 1, l, mid);
		if(qr > mid) query(ql, qr, qd, qu, ret, x << 1 | 1, mid + 1, r);
	}
	void erase(int qx, int qy, int qid, int x = 1, int l = 1, int r = W) {
		t[x].erase({qy, qid});
		if(l == r) return;
		int mid = (l + r) >> 1;
		if(qx <= mid) erase(qx, qy, qid, x << 1, l, mid);
		else erase(qx, qy, qid, x << 1 | 1, mid + 1, r);
	}
} seg;

int main() {
	scanf("%d%d%d%d", &n, &m, &W, &H);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
	for(int i = 1; i <= m; i++) scanf("%d%d%d%d%d%d", &e[i].p, &e[i].w, &e[i].l, &e[i].r, &e[i].d, &e[i].u), to[e[i].p].push_back(i);
	for(int i = 1; i <= n; i++) seg.insert(a[i].x, a[i].y, i);
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
	for(int i = 1; i <= n; i++) dis[i] = INF;
	dis[1] = 0, seg.erase(a[1].x, a[1].y, 1);
	for(int i : to[1]) q.push({e[i].w, i});
	while(!q.empty()) {
		auto p = q.top();
		q.pop();
		int w = p.first, i = p.second;
		if(vis[i]) continue;
		vis[i] = true;
		std::vector<int> out;
		seg.query(e[i].l, e[i].r, e[i].d, e[i].u, out);
		for(int u : out) {
			dis[u] = w;
			seg.erase(a[u].x, a[u].y, u);
			for(int j : to[u]) q.push({w + e[j].w, j});
		}
	}
	for(int i = 2; i <= n; i++) printf("%d\n", dis[i]);
	return 0;
}