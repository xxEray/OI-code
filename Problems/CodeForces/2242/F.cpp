#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n;
int a[N];

struct Treap {
	std::mt19937 rnd;
	struct Node {
		Node *ls, *rs;
		int sz, v;
		void maintain() { sz = ls->sz + rs->sz + 1; }
	} *nil, *rt;
	void init() { nil = new Node, nil->ls = nil->rs = nil, nil->sz = 0, nil->v = 0, rt = nil; }
	Node *nw(int v) {
		auto p = new Node;
		p->ls = p->rs = nil, p->sz = 1, p->v = v;
		return p;
	}
	Node *copy(Node *const p) { return new Node(*p); }
	std::pair<Node *, Node *> split(Node *const p, int sz) {
		if(p == nil) return {nil, nil};
		Node *x, *y;
		if(sz >= p->ls->sz + 1) x = copy(p), std::tie(x->rs, y) = split(x->rs, sz - p->ls->sz - 1), x->maintain();
		else y = copy(p), std::tie(x, y->ls) = split(y->ls, sz), y->maintain();
		return {x, y};
	}
	Node *merge(Node *const x, Node *const y) {
		if(x == nil || y == nil) return x == nil ? y : x;
		std::uniform_int_distribution dist(1, x->sz + y->sz);
		Node *p;
		if(dist(rnd) <= x->sz) p = copy(x), p->rs = merge(p->rs, y);
		else p = copy(y), p->ls = merge(x, p->ls);
		p->maintain();
		return p;
	}
	void print(Node *p) const {
		if(p == nil) return;
		print(p->ls);
		printf("%d ", p->v);
		print(p->rs);
	}
	void print() const { print(rt); puts(""); }
	Node *build(int l, int r) {
		if(l > r) return nil;
		int mid = (l + r) >> 1;
		Node *p = nw(mid);
		p->ls = build(l, mid - 1), p->rs = build(mid + 1, r);
		p->maintain();
		return p;
	}
	void move(int ind) {
		Node *x, *y, *z;
		// [ind, 2 * ind - 1] ## [0, 2 * n - ind]
		std::tie(x, y) = split(rt, 2 * n - ind + 1); // x = [0, 2 * n - ind]
		std::tie(y, z) = split(rt, ind); // z = [ind, 2 * n]
		std::tie(y, z) = split(z, ind); // y = [ind, 2 * ind - 1]
		// printf("move %d: x=", ind);
		// print(x);
		// printf("; y=");
		// print(y);
		// puts("");
		rt = merge(y, x);
	}
	int query0() const {
		Node *p = rt;
		while(p->ls != nil) p = p->ls;
		return p->v;
	}
} treap;

int main() {
	treap.init();
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	treap.rt = treap.build(0, 2 * n);
	// treap.print();
	for(int i = n; i >= 1; i--) {
		treap.move(a[i]);
		printf("%d ", treap.query0());
		// printf("i = %d: ", i), treap.print();
	}
	puts("");
	return 0;
}