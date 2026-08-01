#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2e5 + 5;
const int MAX_MEMORY_POOL = 1e6 + 5;

struct Graph {
	struct Edge { int to, nxt; } edge[N << 1];
	int head[N], k;
	Graph() : k(1) {}
	void add_edge(int u, int v) { edge[k] = (Edge){v, head[u]}; head[u] = k++; }
} gA, gB, gC;
struct Tree;

Tree t[MAX_MEMORY_POOL]; int tot = 0; // memory pool
inline Tree *nwTree() { return &t[tot++]; }

int nA, nB, nC;
struct Tree {
	int dep;
	Tree *fa;
	std::vector<Tree *> s;
	Tree() : fa(nullptr), dep(0) {}
	// TODO: check the order of the sons
	void build(const Graph &g, int u = 1, int fath = 0) {
		dep = 0;
		for(int i = g.head[u]; i; i = g.edge[i].nxt)
			if(g.edge[i].to != fath) {
				int v = g.edge[i].to;
				Tree *son = nwTree();
				s.push_back(son);
				son->fa = this;
				son->build(g, v, u);
				dep = std::max(dep, son->dep + 1);
			}
	}
} *A, *B, *C;
bool operator==(const Tree *a, const Tree *b) {
	if(a->s.size() != b->s.size()) return false;
	for(int i = 0; i < (int)a->s.size(); i++)
		if(!(a->s[i] == b->s[i])) // TODO: done this function
}
Tree *copy(Tree *t) {
	Tree *u = nwTree();
	u->dep = t->dep, u->fa = t->fa;
	for(int i = 0; i < (int)t->s.size(); i++) {
		Tree *v = copy(t->s[i]);
		u->s.push_back(v);
	}
}

int main() {
	A = nwTree(), B = nwTree(), C = nwTree();
	scanf("%d%d%d", &nA, &nB, &nC);
	for(int i = 1; i < nA; i++) { int u, v; scanf("%d%d", &u, &v); gA.add_edge(u, v), gA.add_edge(v, u); }
	for(int i = 1; i < nB; i++) { int u, v; scanf("%d%d", &u, &v); gB.add_edge(u, v), gB.add_edge(v, u); }
	for(int i = 1; i < nC; i++) { int u, v; scanf("%d%d", &u, &v); gC.add_edge(u, v), gC.add_edge(v, u); }
	A->build(gA), B->build(gB), C->build(gC);
	return 0;
}