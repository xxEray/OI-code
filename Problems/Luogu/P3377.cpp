#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, m;

struct HeapNode { HeapNode *ls, *rs; int id, val, d; } *nil, buffer[N];
HeapNode *nw() { static int tot = 0; tot++; buffer[tot].ls = buffer[tot].rs = nil, buffer[tot].d = 1; return &buffer[tot]; }
HeapNode *merge(HeapNode *x, HeapNode *y) {
	if(x == nil || y == nil) return x == nil ? y : x;
	if(x->val > y->val || (x->val == y->val && x->id > y->id)) std::swap(x, y);
	x->rs = merge(x->rs, y);
	if(x->rs->d > x->ls->d) std::swap(x->ls, x->rs);
	x->d = std::max(x->ls->d, x->rs->d) + (x->ls->d == x->rs->d);
	return x;
}

bool removed[N];

int fa[N]; HeapNode *nd[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

int main() {
	nil = &buffer[0], nil->ls = nil->rs = nil, nil->d = 0;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		nd[i] = nw(), nd[i]->id = i, nd[i]->val = x;
		fa[i] = i;
	}
	while(m--) {
		int t, x, y;
		scanf("%d", &t);
		if(t == 1) {
			scanf("%d%d", &x, &y);
			if(removed[x] || removed[y]) continue;
			x = find(x), y = find(y);
			if(x != y) {
				HeapNode *v = merge(nd[x], nd[y]);
				merge(x, y);
				nd[find(x)] = v;
			}
		} else {
			scanf("%d", &x);
			if(removed[x]) { puts("-1"); continue; }
			x = find(x);
			printf("%d\n", nd[x] == nil ? -1 : nd[x]->val);
			removed[nd[x]->id] = true;
			nd[x] = merge(nd[x]->ls, nd[x]->rs);
		}
	}
	return 0;
}