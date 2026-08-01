#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;

int n; LL m, T;
struct Node { LL p; int d, id; } a[N];

int id[N];
LL out[N];

int main() {
	scanf("%d%lld%lld", &n, &m, &T);
	for(int i = 1; i <= n; i++) { int type; scanf("%lld%d", &a[i].p, &type); a[i].d = (type == 2 ? -1 : 1); a[i].id = i; }
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.p < y.p; });
	for(int i = 1; i <= n; i++) id[i] = a[i].id;
	LL offset = 0;
	for(int i = 1; i <= n; i++) {
		if(a[i].d == 1) {
			if(T >= m - a[i].p) (offset += (T - (m - a[i].p)) / m + 1) %= n;
		} else {
			if(T >= a[i].p + 1) (offset -= (T - (a[i].p + 1)) / m + 1) %= n;
		}
		// printf("offset = %lld\n", offset);
	}
	offset = (offset + n) % n + 1;
	// printf("offset = %lld\n", offset);
	for(int i = 1; i <= n; i++) a[i].p = ((a[i].p + T * a[i].d) % m + m) % m;
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.p < y.p; });
	int c = 0;
	for(int i = offset; i <= n; i++) out[id[++c]] = a[i].p;
	for(int i = 1; i < offset; i++) out[id[++c]] = a[i].p;
	for(int i = 1; i <= n; i++) printf("%lld\n", out[i]);
	return 0;
} /*
2 4 8
1 R
3 L

*/