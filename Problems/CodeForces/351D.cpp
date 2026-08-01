#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 1e5 + 5;

int a[N];
struct Query { int l, r, id; } q[N];
int n, m;

std::vector<int> pos[N];

struct BIT { // Binary Indexed Tree
    struct { // 单点修改，区间查询
        int c[N];
        int query(int r) {
            if(r == 0) return c[0];
            int ret = 0;
            while(r) ret = ret + c[r], r -= (r & -r);
            return ret + c[0];
        }
        void add(int x, int y) {
            if(x == 0) { c[x] = c[x] + y; return; }
            while(x <= n) c[x] = c[x] + y, x += x & -x;
        }
    } tr1, tr2;
    int query(int r) { return (r + 1) * tr1.query(r) - tr2.query(r); }
    int query(int l, int r) {
        if(l == 0) return query(r);
        return query(r) - query(l - 1);
    }
    void add(int l, int r, int k) {
        tr1.add(r + 1, -k), tr1.add(l, k);
        tr2.add(r + 1, -k * (r + 1)), tr2.add(l, k * l);
    }
} seg, clseg;

int out[N], last[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
	std::sort(q + 1, q + m + 1, [](Query x, Query y) { return x.r < y. r; });
	for(int i = 1, j = 1; i <= n; i++) {
		auto &p = pos[a[i]];
		int sz = p.size();
		if(p.empty()) p.push_back(0);
		if(p.size() == 1U) seg.add(p.back() + 1, i, 1);
		else if(p.back() - p[sz - 2] == i - p.back()) seg.add(p.back() + 1, i, 1);
		else {
			int tmp = p[sz - 2] + 1;
			seg.add(p.front(), p[sz - 2], -1), seg.add(p.back() + 1, i, 1);
			p.clear(), p.push_back(tmp), p.push_back(last[a[i]]);
		}
		p.push_back(i);
		// printf("%d: ", i);
		// for(int k = 1; k <= 3; k++) {
		// 	printf("%d[", k);
		// 	for(auto r : pos[k]) printf("%d ", r);
		// 	printf("] ");
		// }
		// printf("t[");
		// for(int k = 1; k <= i; k++) printf("%d ", seg.query(k, k));
		// printf("]");
		// puts("");
		if(last[a[i]]) clseg.add(last[a[i]], last[a[i]], -1);
		clseg.add(i, i, 1);
		last[a[i]] = i;
		while(j <= m && q[j].r == i) out[q[j].id] = clseg.query(q[j].l, q[j].r) + !seg.query(q[j].l, q[j].l), j++;
	}
	for(int i = 1; i <= m; i++) printf("%d\n", out[i]);
	return 0;
}