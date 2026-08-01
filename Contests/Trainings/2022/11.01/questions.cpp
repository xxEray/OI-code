#include <cstdio>
#include <algorithm>
#include <cmath>

const int N = 2e5 + 5;
const int SQRT_N = 500;

int n, m;
int a[N];

int blk[N];

struct Query { int l, r, k, id, ans; } q[N];
bool operator<(Query x, Query y) { return blk[x.r] == blk[y.r] ? x.l < y.l : x.r < y.r; }

int cnt[N], ans[N];

void add(int x) { cnt[a[x]]++, ans[cnt[a[x]]]++; }
void del(int x) { ans[cnt[a[x]]]--, cnt[a[x]]--; }

int main() {
#ifndef DEBUG
	freopen("questions.in", "r", stdin);
	freopen("questions.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int sqrtn = sqrt(n);
	for(int i = 1; i <= n; i++) blk[i] = (i - 1) / sqrtn + 1;
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].k), q[i].id = i;
	std::sort(q + 1, q + m + 1);
	int l = 1, r = 0;
	for(int i = 1; i <= m; i++) {
		while(r < q[i].r) add(++r);
		while(l < q[i].l) del(l++);
		while(l > q[i].l) add(--l);
		while(r > q[i].r) del(r--);
		q[i].ans = ans[q[i].k];
	}
	std::sort(q + 1, q + m + 1, [&](Query x, Query y) { return x.id < y.id; });
	for(int i = 1; i <= m; i++) printf("%d\n", q[i].ans);
	return 0;
}
