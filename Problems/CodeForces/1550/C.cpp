#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

int a[N];
int n;

LL f[N][2];

int tmp[N];
void preprocess() {
	for(int i = 1; i <= n; i++) tmp[i] = a[i];
	std::sort(tmp + 1, tmp + n + 1);
	int n_ = std::unique(tmp + 1, tmp + n + 1) - tmp - 1;
	for(int i = 1; i <= n; i++) a[i] = std::lower_bound(tmp + 1, tmp + n_ + 1, a[i]) - tmp;
}

struct BIT {
	LL t[N];
	inline int lowbit(int x) { return x & -x; }
	void add(int x, int v) { while(x <= n) t[x] += v, x += lowbit(x); }
	int query(int x) { if(!x) return 0; LL ret = 0; while(x) ret += t[x], x -= lowbit(x); return ret; }
	LL query(int l, int r) { return query(r) - query(l - 1); }
} bit[2];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) f[i][0] = f[i][1] = bit[0].t[i] = bit[1].t[i] = 0;
		preprocess();
		for(int i = 1; i <= n; i++) f[i][0] = 1, f[i][1] = 0;
		for(int i = 1; i <= n; i++)
			for(int k = 0; k <= 1; k++) {
				f[i][k] += bit[k].query(a[i] + 1, n);
				if(!k) f[i][k + 1] += bit[k].query(1, a[i]);
				bit[k].add(a[i], f[i][k]);
			}
		for(int i = 1; i <= n; i++) printf("f[%d] = {%lld, %lld}\n", i, f[i][0], f[i][1]);
		LL ans = 0;
		for(int i = 1; i <= n; i++) ans += f[i][0] + f[i][1];
		printf("%lld\n", ans);
	}
	return 0;
}