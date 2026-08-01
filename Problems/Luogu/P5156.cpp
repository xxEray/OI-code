#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

typedef long long LL;

const int N = 1e5 + 5;

int n;
LL m;

int a[N];

int g[N];
LL f[N];

struct BIT_max {
	int t[N];
	void add(int x, int v) { while(x <= n) t[x] = std::max(t[x], v), x += x & -x; }
	int query(int r) { int ret = 0; while(r) ret = std::max(ret, t[r]), r -= r & -r; return ret; }
} bit_max;
void trim(LL &x) { if(x > m + 1) x = m + 1; }
struct BIT_sum {
	LL t[N];
	void add(int x, LL v) { x = n - x + 1; while(x <= n) trim(t[x] += v), x += x & -x; }
	void clear(int x) { x = n - x + 1; while(x <= n) t[x] = 0, x += x & -x; }
	LL query(int r) { r = n - r + 1; LL ret = 0; while(r) trim(ret += t[r]), r -= r & -r; return ret; }
} bit_sum;

std::vector<int> level[N];
bool out[N];

int main() {
	freopen("itout.in", "r", stdin);
	freopen("itout.out", "w", stdout);
	scanf("%d%lld", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) g[i] = bit_max.query(a[i] - 1) + 1, bit_max.add(a[i], g[i]);
	for(int i = 1; i <= n; i++) level[g[i]].push_back(i);
	int lis = 0;
	for(int i = 1; i <= n; i++) lis = std::max(lis, g[i]);
	for(int i : level[lis]) f[i] = 1;
	for(int i = lis - 1; i >= 1; i--) {
		std::vector<int> tmp;
		tmp.insert(tmp.end(), level[i].begin(), level[i].end()), tmp.insert(tmp.end(), level[i + 1].begin(), level[i + 1].end());
		std::sort(tmp.begin(), tmp.end(), [&](int x, int y) { return x > y; });
		for(int j : tmp)
			if(g[j] == i) f[j] = bit_sum.query(a[j] + 1);
			else bit_sum.add(a[j], f[j]);
		for(int j : tmp) bit_sum.clear(a[j]);
	}
	// for(int i = 1; i <= n; i++) printf("%d\n", g[i]);
	// puts("");
	// for(int i = 1; i <= n; i++) printf("%lld\n", f[i]);
	// puts("");
	for(int i = 1; i <= n; i++) out[i] = true;
	int k = 0;
	for(int i = 1; i <= lis; i++) {
		int j;
		for(auto it = level[i].begin(); it != level[i].end(); it++) {
			j = *it;
			if(j < k) continue;
			if(a[k] > a[j]) continue;
			if(f[j] < m) m -= f[j];
			else break;
		}
		out[j] = false;
		k = j;
	}
	printf("%d\n", n - lis);
	std::vector<int> ans;
	for(int i = 1; i <= n; i++) if(out[i]) ans.push_back(a[i]);
	std::sort(ans.begin(), ans.end());
	for(int v : ans) printf("%d\n", v);
	return 0;
}