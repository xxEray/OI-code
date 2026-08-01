#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e6 + 5;

int n, m, Q, L;
struct Node { int x, ox, t; } a[2 * N], b[2 * N];
struct Query { int l, r; } q[N];

int c[N];

LL ans[15][2][2];

void solve(int T) {
	// printf("solve(%d)\n", T);
	for(int qi = 1; qi <= Q; qi++) {
		for(int i = 1; i <= n + 1; i++) c[i] = 0;
		int l = 1, r = 1;
		// puts("-----");
		// printf("#%d:\n", qi);
		auto calc = [&](int k) {
			for(int i = 1; i <= n; i++) {
				while(l < n + i - 1 && k * L - a[l + 1].x >= 0 && (k * L - a[l + 1].x - a[i].x > 2 * T || k * L + a[i].x - a[l + 1].x >= 2 * q[qi].l)) l++;
				while(r < n + i - 1 && k * L - a[r + 1].x >= 0 && (k * L - a[r + 1].x - a[i].x > 2 * T || k * L + a[i].x - a[r].x >= 2 * q[qi].r)) r++;
				// printf("%d: [%d, %d]\n", i, l, r);
				if(k * L - a[l].x - a[i].x < 0 || k * L - a[r].x - a[i].x < 0) { /* puts("   skip"); */ continue; }
				if(k * L - a[l].x - a[i].x > 2 * T || k * L - a[r].x - a[i].x > 2 * T) { /* puts("   skip"); */ continue; }
				if(k * L + a[i].x - a[l].x < 2 * q[qi].l || k * L + a[i].x - a[l].x > 2 * q[qi].r) { /* puts("   skip"); */ continue; }
				if(k * L + a[i].x - a[r].x < 2 * q[qi].l || k * L + a[i].x - a[r].x > 2 * q[qi].r) { /* puts("   skip"); */ continue; }
				int x = n - (l - i + 1) + 1;
				// [x .. x + (l - r)] += 1
				if(x + (l - r) >= n) {
					c[x]++, c[n]--; // [x .. n - 1] += 1
					c[2 * (n - 1) - x - (l - r)]++, c[n - 1]--; // [2 * (n - 1) - x - (l - r) .. n - 2] += 1
				} else c[x]++, c[x + (l - r) + 1]--; // [x .. x + (l - r)] += 1
				// printf("x = %d\n", x);
			}
			// l = 1, r = 1;
			// for(int i = 1; i <= n; i++) {
			// 	while(l < n + i - 1 && (4 * L - a[l + 1].x - a[i].x > 2 * T || 4 * L + a[i].x - a[l + 1].x >= 4 * L - 2 * q[qi].r)) l++;
			// 	while(r < n + i - 1 && (4 * L - a[r + 1].x - a[i].x > 2 * T || 4 * L + a[i].x - a[r].x >= 4 * L - 2 * q[qi].l)) r++;
			// 	printf("%d: [%d, %d]\n", i, l, r);
			// 	if(4 * L - a[l].x - a[i].x > 2 * T || 4 * L - a[r].x - a[i].x > 2 * T) { puts("   skip"); continue; }
			// 	if(4 * L + a[i].x - a[l].x < 4 * L - 2 * q[qi].r || 4 * L + a[i].x - a[l].x > 4 * L - 2 * q[qi].l) { puts("   skip"); continue; }
			// 	if(4 * L + a[i].x - a[r].x < 4 * L - 2 * q[qi].r || 4 * L + a[i].x - a[r].x > 4 * L - 2 * q[qi].l) { puts("   skip"); continue; }
			// 	int x = l - i;
			// 	// [x .. x - (l - r)] += 1
			// 	if(x - (l - r) <= 0) {
			// 		c[1]++, c[x + 1]--; // [1 .. x] += 1
			// 		c[2]++, c[(l - r) - x + 3]--; // [2 .. (l - r) - x + 2] += 1
			// 	} else c[x - (l - r)]++, c[x + 1]--; // [x - (l - r) .. x] += 1
			// 	printf("x = %d\n", x);
			// }
		};
		calc(2), calc(4), calc(6);
		for(int i = 1; i <= n; i++) c[i] += c[i - 1];
		for(int i = 1; i < n; i++) ans[qi][b[i].t][b[i + 1].t] += c[i];
	}
}

int main() {
	int T;
	scanf("%d%d%d%d%d", &n, &m, &Q, &L, &T);
	for(int i = 1; i <= n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		a[i] = {(y == 1 ? x : (2 * L - x) % (2 * L)), x, 0};
	}
	for(int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		a[n + i] = {(y == 1 ? x : (2 * L - x) % (2 * L)), x, 1};
	}
	for(int i = 1; i <= Q; i++) scanf("%d%d", &q[i].l, &q[i].r);
	n += m;
	for(int i = 1; i <= n; i++) a[i + n] = a[i], a[i + n].x += 2 * L;
	for(int i = 1; i <= n; i++) b[i] = a[i];
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.x < y.x; });
	std::sort(b + 1, b + n + 1, [&](Node x, Node y) { return x.ox < y.ox; });
	if(T > 2 * L) {
		solve(2 * L);
		for(int i = 1; i <= Q; i++)
			ans[i][0][0] *= T / (2 * L), ans[i][0][1] *= T / (2 * L), ans[i][1][0] *= T / (2 * L), ans[i][1][1] *= T / (2 * L);
	}
	solve(T % (2 * L));
	for(int i = 1; i <= Q; i++) printf("%lld %lld %lld\n", ans[i][0][0], ans[i][1][1], ans[i][0][1] + ans[i][1][0]);
	return 0;
} /*
2 2 1 10 33
2 1
1 1
3 -1
5 -1
3 9
*/