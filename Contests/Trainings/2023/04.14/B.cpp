#include <cstdio>
#include <algorithm>
#include <cassert>

typedef long long LL;

const int N = 4e5 + 5;

int n, Q;
int a[N];

int fa[N * 2];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }

int main() {
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= 2 * n + 1; i++) fa[i] = i;
	while(Q--) {
		int t;
		scanf("%d", &t);
		if(t == 1) {
			int k, x;
			scanf("%d%d", &k, &x);
			a[k] = x;
		} else if(t == 2) {
			int x, y;
			scanf("%d%d", &x, &y);
			if(x == y) continue;
			merge(x, y + n), merge(y, x + n);
			if(find(x) == find(x + n) || find(y) == find(y + n)) merge(x, 2 * n + 1);
		} else if(t == 3) {
			int x, y, v;
			scanf("%d%d%d", &x, &y, &v);
			if((find(x) != find(y) && find(x) != find(y + n)) || (find(x) == find(2 * n + 1) || find(x + n) == find(2 * n + 1)))
				puts("0");
			else {
				assert(find(x) == find(y) || find(x) == find(y + n));
				LL p = (LL)v * a[x], q = a[y];
				LL g = gcd(p, q);
				p /= g, q /= g;
				if(find(x) != find(y)) putchar('-');
				printf("%lld/%lld\n", p, q);
			}
		}
	}
	return 0;
} /*
4 10
6 8 10 13
3 1 2 2
2 1 2
3 1 2 3
2 2 3
1 1 7
3 1 3 10
2 3 1
3 1 3 2
2 1 4
3 1 4 6
*/