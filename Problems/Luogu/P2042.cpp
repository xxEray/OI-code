#include <bits/stdc++.h>

const int N = 5e5 + 5;
const int NONE = 1234;
const int INF = 0x3f3f3f3f;

int n, Q;

struct FHQ {
private:
	struct Node {
		Node *ls, *rs;
		int sz, w;
		int val, sum, premax, sufmax, summax;
		int assign, rev;
	} buffer[N], *nil, *root;
	std::vector<int> reuse;
	int tot;
	Node *nw(int val) {
		Node *x;
		if(reuse.empty()) x = &buffer[++tot];
		else x = &buffer[reuse.back()], reuse.pop_back();
		x->ls = x->rs = nil;
		x->sz = 1, x->w = rand() << 15 | rand();
		x->val = x->sum = x->premax = x->sufmax = x->summax = val;
		x->assign = NONE, x->rev = 0;
		return x;
	}
	void pushup(Node *x) {
		x->sz = x->ls->sz + x->rs->sz + 1;
		x->sum = x->ls->sum + x->rs->sum + x->val;
		x->premax = std::max({x->ls == nil ? -INF : x->ls->premax, x->ls->sum + x->val, x->ls->sum + x->val + x->rs->premax});
		x->sufmax = std::max({x->rs == nil ? -INF : x->rs->sufmax, x->rs->sum + x->val, x->rs->sum + x->val + x->ls->sufmax});
		x->summax = std::max({x->ls == nil ? -INF : x->ls->summax, x->rs == nil ? -INF : x->rs->summax, x->val, x->ls->sufmax + x->val, x->rs->premax + x->val, x->ls->sufmax + x->val + x->rs->premax});
	}
	void pushrev(Node *x) { if(x != nil) std::swap(x->ls, x->rs), x->rev ^= 1, pushup(x); }
	void pushassign(Node *x, int val) {
		if(x == nil || val == NONE) return;
		x->assign = val;
		x->val = val, x->sum = val * x->sz;
		x->premax = x->sufmax = x->summax = val * (val >= 0 ? x->sz : 1);
	}
	void pushdown(Node *x) {
		if(x->rev) pushrev(x->ls), pushrev(x->rs), x->rev = 0;
		pushassign(x->ls, x->assign), pushassign(x->rs, x->assign);
		x->assign = NONE;
	}
	Node *merge(Node *x, Node *y) {
		if(x == nil || y == nil) return x == nil ? y : x;
		if(x->ls->w > x->rs->w) { pushdown(x), x->rs = merge(x->rs, y), pushup(x); return x; }
		else { pushdown(y), y->ls = merge(x, y->ls), pushup(y); return y; }
	}
	void split(Node *rt, int sz, Node *&x, Node *&y) {
		if(rt == nil) { x = y = nil; return; }
		if(sz <= rt->ls->sz) y = rt, pushdown(y), split(rt->ls, sz, x, y->ls), pushup(y);
		else x = rt, pushdown(x), split(rt->rs, sz - rt->ls->sz - 1, x->rs, y), pushup(x);
	}
	void recycle(Node *x) {
		if(x == nil) return;
		recycle(x->ls), recycle(x->rs);
		reuse.push_back(x - buffer);
	}
public:
	FHQ() { nil = &buffer[0], nil->ls = nil->rs = nil, nil->sz = nil->val = nil->sum = nil->premax = nil->sufmax = nil->summax = nil->assign = nil->rev = 0; root = nil; }
	void insert(int pos, int val) {
		Node *x, *y;
		split(root, pos - 1, x, y);
		root = merge(x, merge(nw(val), y));
	}
	void remove(int l, int r) {
		Node *x, *y, *z;
		split(root, l - 1, x, y);
		split(y, r - l + 1, y, z);
		root = merge(x, z);
		recycle(y);
	}
	void assign(int l, int r, int val) {
		Node *x, *y, *z;
		split(root, l - 1, x, y), split(y, r - l + 1, y, z);
		pushassign(y, val);
		root = merge(x, merge(y, z));
	}
	void reverse(int l, int r) {
		Node *x, *y, *z;
		split(root, l - 1, x, y), split(y, r - l + 1, y, z);
		pushrev(y);
		root = merge(x, merge(y, z));
	}
	int getsum(int l, int r) {
		Node *x, *y, *z;
		split(root, l - 1, x, y), split(y, r - l + 1, y, z);
		int ret = y->sum;
		root = merge(x, merge(y, z));
		return ret;
	}
	int getmaxsum(int l, int r) {
		Node *x, *y, *z;
		split(root, l - 1, x, y), split(y, r - l + 1, y, z);
		int ret = y->summax;
		root = merge(x, merge(y, z));
		return ret;
	}
	int size() { return root->sz; }
} treap;

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); treap.insert(i, x); }
	while(Q--) {
		char str[20];
		scanf("%s", str);
		if(!strcmp(str, "INSERT")) {
			int pos, tot, x;
			scanf("%d%d", &pos, &tot);
			while(tot--) scanf("%d", &x), treap.insert(++pos, x);
		} else if(!strcmp(str, "DELETE")) {
			int pos, tot;
			scanf("%d%d", &pos, &tot);
			treap.remove(pos, pos + tot - 1);
		} else if(!strcmp(str, "MAKE-SAME")) {
			int pos, tot, x;
			scanf("%d%d%d", &pos, &tot, &x);
			treap.assign(pos, pos + tot - 1, x);
		} else if(!strcmp(str, "REVERSE")) {
			int pos, tot;
			scanf("%d%d", &pos, &tot);
			treap.reverse(pos, pos + tot - 1);
		} else if(!strcmp(str, "GET-SUM")) {
			int pos, tot;
			scanf("%d%d", &pos, &tot);
			int ret = treap.getsum(pos, pos + tot - 1);
			printf("%d\n", ret);
		} else if(!strcmp(str, "MAX-SUM")) {
			int ret = treap.getmaxsum(1, treap.size());
			printf("%d\n", ret);
		}
	}
	return 0;
}