#include <iostream>
#include <algorithm>
#include <map>
#include <string>

#define SZ(container) ((int)(container).size())

const int N = 5e5 + 5;

int n, Q;
std::string s, t[N];

struct SegData { int v, id; };
struct SegNode { SegData t; SegNode *ls, *rs; } buffer[N * 20 * 2];
SegNode *nw_node() { static int k = 0; return &buffer[++k]; }
SegData segcalc(SegData x, SegData y) {
	SegData z;
	z.v = std::max(x.v, y.v);
	z.id = (z.v == x.v ? x.id : y.id);
	return z;
}
struct SegTree {
	SegNode *rt;
	SegTree() : rt(nw_node()) {}
	void add(int qind, int qv) { add(qind, qv, rt, 1, n); }
	SegData query(int ql, int qr) { return query(ql, qr, rt, 1, n); }
private:
	void add(int qind, int qv, SegNode *x, int l, int r) {
		if(l == r) { x->t.v += qv, x->t.id = l; return; }
		int mid = (l + r) >> 1;
		if(qind <= mid) x->ls ? 0 : x->ls = nw_node(), add(qind, qv, x->ls, l, mid);
		else x->rs ? 0 : x->rs = nw_node(), add(qind, qv, x->rs, mid + 1, r);
		x->t = (x->ls && x->rs ? segcalc(x->ls->t, x->rs->t) : (x->ls ? x->ls->t : x->rs->t));
	}
	SegData query(int ql, int qr, SegNode *x, int l, int r) {
		if(!x) return SegData();
		if(ql <= l && r <= qr) return x->t;
		int mid = (l + r) >> 1;
		if(qr <= mid) return query(ql, qr, x->ls, l, mid);
		else if(ql > mid) return query(ql, qr, x->rs, mid + 1, r);
		else return segcalc(query(ql, qr, x->ls, l, mid), query(ql, qr, x->rs, mid + 1, r));
	}
} seg[N * 3];
SegNode *merge(SegNode *x, SegNode *y) {
	if(!x || !y) return x ? x : y;
	SegNode *z = nw_node();
	z->ls = merge(x->ls, y->ls), z->rs = merge(x->rs, y->rs);
	if(!z->ls && !z->rs) z->t.v = x->t.v + y->t.v, z->t.id = (x->t.v ? x->t.id : y->t.id);
	else z->t = (z->ls && z->rs ? segcalc(z->ls->t, z->rs->t) : (z->ls ? z->ls->t : z->rs->t));
	return z;
}
void merge(SegTree &x, SegTree y) { x.rt = merge(x.rt, y.rt); }

struct SAM {
	int link[N * 3], len[N * 3];
	std::map<char, int> next[N * 3];
	int tot, last;
	SAM() : tot(1), last(1) {}
	void insert(int c, int id) {
		if(next[last].count(c)) {
			int p = last, q = next[last][c];
			if(len[q] == len[p] + 1) last = q;
			else {
				int clone = ++tot;
				len[clone] = len[p] + 1;
				link[clone] = link[q], link[q] = clone;
				next[clone] = next[q];
				for(; p && next[p][c] == q; p = link[p]) next[p][c] = clone;
				last = clone;
			}
		} else {
			int cur = ++tot, p = last;
			len[cur] = len[last] + 1;
			for(; p && !next[p][c]; p = link[p]) next[p][c] = cur;
			if(!p) link[cur] = 1;
			else {
				int q = next[p][c];
				if(len[q] == len[p] + 1) link[cur] = q;
				else {
					int clone = ++tot;
					len[clone] = len[p] + 1;
					link[clone] = link[q], link[q] = clone;
					next[clone] = next[q];
					for(; p && next[p][c] == q; p = link[p]) next[p][c] = clone;
					link[cur] = clone;
				}
			}
			last = cur;
		}
		if(id) seg[last].add(id, 1);
	}
} sam;

struct Edge { int to, nxt; } edge[N * 3];
int head[N * 3];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

void build_suffix_tree() { for(int i = 2; i <= sam.tot; i++) add_edge(sam.link[i], i); }
void dfs(int u) {
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		dfs(v);
		merge(seg[u], seg[v]);
	}
}

int go[21][N * 3], position[N];
void preprocess_locate() {
	for(int i = 1; i <= sam.tot; i++) go[0][i] = sam.link[i];
	for(int j = 1; j <= 20; j++)
		for(int i = 1; i <= sam.tot; i++)
			go[j][i] = go[j - 1][go[j - 1][i]];
}
int locate(int l, int r) {
	int now = position[r];
	for(int i = 20; i >= 0; i--) if(sam.len[go[i][now]] > r - l + 1) now = go[i][now];
	return sam.len[sam.link[now]] < r - l + 1 ? now : sam.link[now];
}

int main() {
	std::cin >> s >> n;
	for(int i = 1; i <= n; i++) std::cin >> t[i];
	for(int i = 0; i < SZ(s); i++) sam.insert(s[i], 0);
	for(int i = 1; i <= n; i++) {
		sam.last = 1;
		for(int j = 0; j < SZ(t[i]); j++) sam.insert(t[i][j], i);
	}
	int now = 1;
	for(int i = 0; i < SZ(s); i++) now = sam.next[now][s[i]], position[i] = now;
	// for(int i = 1; i <= sam.tot; i++) for(auto p : sam.next[i]) printf("%d %c %d\n", i, p.first, p.second);
	// for(int i = 1; i <= sam.tot; i++) printf("link[%d] = %d, len[%d] = %d\n", i, sam.link[i], i, sam.len[i]);
	build_suffix_tree();
	dfs(1);
	preprocess_locate();
	std::cin >> Q;
	while(Q--) {
		int l, r, pl, pr;
		std::cin >> l >> r >> pl >> pr;
		int x = locate(pl - 1, pr - 1);
		SegData ans = seg[x].query(l, r);
		if(ans.v == 0) ans.id = l;
		std::cout << ans.id << ' ' << ans.v << '\n';
	}
	return 0;
} /*
st
2
staw
ctit
1
1 2 2 2
*/