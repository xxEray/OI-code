#include <cstdio>
#include <algorithm>
#include <set>
#include <cassert>

typedef long long LL;

const int N = 2500 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;
struct Node { int l, r; LL v; } a[N];
LL c[N << 1][N << 1];

int tmp[N << 1];
int cn = 0;
void discrete() {
	for(int i = 1; i <= n; i++) tmp[++cn] = a[i].l, tmp[++cn] = a[i].r;
	std::sort(tmp + 1, tmp + cn + 1);
	cn = std::unique(tmp + 1, tmp + cn + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i].l = std::lower_bound(tmp + 1, tmp + cn + 1, a[i].l) - tmp;
	for(int i = 1; i <= n; i++) a[i].r = std::lower_bound(tmp + 1, tmp + cn + 1, a[i].r) - tmp;
}

LL f[N << 1];
std::multiset<LL> st;

int main() {
#ifndef DEBUG
	freopen("interval.in", "r", stdin);
	freopen("interval.out", "w", stdout);
#endif
	// freopen("D:\\Useless\\Temp\\down\\interval\\ex_A2.in", "r", stdin);
	scanf("%d%d", &n, &m);
	LL all = 0;
	for(int i = 1; i <= n; i++) scanf("%d%d%lld", &a[i].l, &a[i].r, &a[i].v), all += a[i].v;
	discrete();
	std::sort(a + 1, a + n + 1, [&](Node x, Node y) { return x.r < y.r; });
	// for(int i = 1; i <= n; i++) printf("%d %d %d\n", a[i].l, a[i].r, a[i].v);
	for(int i = 1; i <= cn; i++) {
		st.clear();
		LL sum = 0;
		int p = 1;
		for(int j = i; j <= cn; j++) {
			while(p <= n && a[p].r <= j) {
				if(a[p].l >= i) sum += a[p].v, st.insert(a[p].v);
				p++;
			}
			while((int)st.size() > m) sum -= *st.begin(), st.erase(st.begin());
			c[i][j] = sum;
			// printf("a[%d][%d] = %lld\n", i, j, sum);
		}
	}
	for(int i = 1; i <= cn; i++) for(int j = 0; j < i; j++) f[i] = std::max(f[i], f[j] + c[j + 1][i]);
	printf("%lld\n", all - f[cn]);
	return 0;
} /*
5 1
1 1 10
2 2 10
3 3 10
2 3 1
2 3 1
*/