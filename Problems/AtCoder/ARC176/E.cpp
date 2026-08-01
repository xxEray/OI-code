#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;

int n, m;
struct Node { int x, y, v; } q[N];

int a[N], d[N], tin[N];
bool b[N];

int cnt[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) a[i] = n;
	for(int i = 1; i <= m; i++) {
		scanf("%d%d%d", &q[i].x, &q[i].y, &q[i].v);
		a[q[i].x] = std::min(a[q[i].x], q[i].v);
		a[q[i].y] = std::min(a[q[i].y], q[i].v);
	}
	for(int i = 1; i <= m; i++) {
		if(a[q[i].x] < q[i].v && a[q[i].y] < q[i].v) { puts("0"); return 0; }
		else if(a[q[i].x] < q[i].v) tin[q[i].v] += !b[q[i].y], b[q[i].y] = true;
		else if(a[q[i].y] < q[i].v) tin[q[i].v] += !b[q[i].x], b[q[i].x] = true;
		else d[q[i].x]++, d[q[i].y]++;
	}
	for(int i = 1; i <= n; i++) if(d[i] > 1) tin[a[i]] += !b[i], b[i] = true;
	LL ans = 1;
	for(int i = 1; i <= m; i++)
		if(!b[q[i].x] && !b[q[i].y])
			(ans *= 2) %= MOD, a[q[i].y]--, b[q[i].x] = true, tin[q[i].v]++;
	// printf("a: "); for(int i = 1; i <= n; i++) printf("%d ", a[i]); puts("");
	// printf("b: "); for(int i = 1; i <= n; i++) printf("%d ", b[i]); puts("");
	// printf("tin: "); for(int i = 1; i <= n; i++) printf("%d ", tin[i]); puts("");
	// printf("cnt: "); for(int i = 1; i <= n; i++) printf("%d ", cnt[i]); puts("");
	// printf("ans = %lld\n", ans);
	for(int i = 1; i <= n; i++) if(tin[i] > 1) { puts("0"); return 0; }
	for(int i = 1; i <= n; i++) if(!b[i]) cnt[a[i]]++;
	if(cnt[0]) { puts("0"); return 0; }
	int rest = 0;
	for(int i = 1; i <= n; i++) {
		rest += !tin[i];
		for(int j = 1; j <= cnt[i]; j++) (ans *= rest) %= MOD, rest--;
	}
	printf("%lld\n", ans);
	return 0;
} /*
6 4
1 2 4
2 3 6
4 5 6
5 6 3
*/