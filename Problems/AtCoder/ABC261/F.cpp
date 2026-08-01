#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

const int N = 3e5 + 5;

int c[N], a[N];
int n;

struct BIT {
	int t[N];
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	void add(int x, int v) { while(x <= n) t[x] += v, x += x & -x; }
	int query(int l, int r) { return query(r) - (l > 1 ? query(l - 1) : 0); }
} bit;

std::vector<int> vec[N];
int sub[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &c[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) vec[c[i]].push_back(i);
	for(int j = 1; j <= n; j++) {
		// for(int i : vec[j]) printf("%d ", i);
		// puts("");
		for(int i : vec[j]) sub[i] += bit.query(a[i] + 1, n), bit.add(a[i], 1);
		for(int i : vec[j]) bit.add(a[i], -1);
		// memset(bit.t, 0, sizeof(bit.t));
	}
	long long ans = 0;
	// for(int i = 1; i <= n; i++) printf("sub[%d] = %d\n", i, sub[i]);
	for(int i = 1; i <= n; i++) ans += bit.query(a[i] + 1, n) - sub[i], bit.add(a[i], 1);
	printf("%lld\n", ans);
	return 0;
}