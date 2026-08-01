#include <cstdio>
#include <algorithm>
#include <cassert>

typedef long long LL;

const int N = 2e5 + 5;

int n, m;

LL a[N], b[N], d[N];
struct Node { LL v; int id; } c[N];

LL out[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= m; i++) scanf("%lld", &b[i]), c[i].v = b[i], c[i].id = i;
	std::sort(a + 1, a + n + 1, [&](int x, int y) { return x > y; }), std::sort(b + 1, b + m + 1), std::sort(c + 1, c + m + 1, [&](Node x, Node y) { return x.v < y.v; });
	for(int i = 1; i <= n; i++) a[i] *= i;
	int tot = 0;
	for(int i = 1; i <= n; i++) {
		while(tot > 1 && (a[i] - a[tot]) * (d[tot] - d[tot - 1]) > (a[tot] - a[tot - 1]) * (i - d[tot])) tot--;
		a[++tot] = a[i], d[tot] = i;
	}
	// for(int i = 1; i <= tot; i++) printf("%lld,%lld ", a[i], d[i]);
	// puts("");
	int p = 1;
	for(int i = 1; i <= m; i++) {
		while(p < tot && a[p] + b[i] * d[p] < a[p + 1] + b[i] * d[p + 1]) p++;
		out[c[i].id] = a[p] + b[i] * d[p];
		// printf("%d: %d", c[i].id, p);
		// for(int j = 1; j <= tot; j++) if(!(a[j] + b[i] * d[j] <= a[p] + b[i] * d[p])) printf(",%d", j);
		// puts("");
	}
	for(int i = 1; i <= m; i++) printf("%lld ", out[i]);
	puts("");
	return 0;
}