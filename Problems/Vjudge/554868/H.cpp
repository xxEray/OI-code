#include <cstdio>
#include <algorithm>
#include <vector>
#include <bits/extc++.h>
using namespace __gnu_pbds;\

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;

int n, m;
struct Node { int x, y; } a[N];

tree<int, null_type, std::less<int>, rb_tree_tag, tree_order_statistics_node_update> treap;

bool t[N];
std::vector<int> erased, modified;

LL fac[2 * N], invfac[2 * N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL C(LL x, LL y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = qpow(fac[mx], MOD - 2);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int main() {
	get_factorial(400000);
	for(int i = 1; i <= 200000; i++) treap.insert(i);
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= m; i++) scanf("%d%d", &a[i].x, &a[i].y);
		int cnt = 0;
		for(int i = m; i >= 1; i--) {
			int x = *treap.find_by_order(a[i].y), y = *treap.find_by_order(a[i].y + 1);
			treap.erase(x), erased.push_back(x);
			cnt += !t[y];
			t[y] = true, modified.push_back(y);
		}
		printf("%lld\n", C(2 * n - 1 - cnt, n));
		for(int x : erased) treap.insert(x);
		for(int x : modified) t[x] = false;
		erased.clear(), modified.clear();
	}
	return 0;
}