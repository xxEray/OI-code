#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 998244353;
const LL inv2 = (MOD + 1) / 2;

int n;
int a[N];

std::vector<int> occur[N];

bool vis[N];
int bl[N];

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), occur[a[i]].push_back(i);
	int appear = 0;
	for(int i = 1; i <= 200000; i++) appear += !occur[i].empty();
	int cnt = 0;
	bool flag = true;
	std::deque<int> q;
	for(int i = 1; i <= n; i++) {
		if(q.empty()) cnt++;
		bl[i] = cnt;
		if(vis[a[i]]) flag &= q.front() == a[i], q.pop_front(), vis[a[i]] = false;
		else q.push_back(a[i]), vis[a[i]] = true;
		// printf("bl[%d] = %d\n", i, bl[i]);
		// printf("q: "); for(int x : q) printf("%d ", x); puts("");
	}
	flag &= q.empty();
	for(int i = 1; i <= cnt; i++) fa[i] = i;
	for(int i = 1; i <= 200000; i++)
		for(int j = 1; j < (int)occur[i].size(); j++)
			merge(bl[occur[i][j - 1]], bl[occur[i][j]]);
	int component = 0;
	for(int i = 1; i <= cnt; i++) component += (find(i) == i);
	if(flag) printf("%lld\n", (qpow(2, appear) - qpow(2, component) + MOD) * inv2 % MOD);
	else printf("%lld\n", qpow(2, appear - 1));
	return 0;
} /*
8
1 3 1 2 2 3 3 3
*/