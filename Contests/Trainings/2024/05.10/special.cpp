#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n;
int cnt0[N], cnt1[N];
int ff[N];

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

struct cmp { bool operator()(int x, int y) const {
	if((LL)cnt1[x] * cnt0[y] == (LL)cnt1[y] * cnt0[x]) return x < y;
	else return (LL)cnt1[x] * cnt0[y] < (LL)cnt1[y] * cnt0[x];
} };
std::set<int, cmp> st;

int main() {
#ifndef DEBUG
	freopen("special.in", "r", stdin);
	freopen("special.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 2; i <= n; i++) scanf("%d", &ff[i]);
	for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); x ? cnt1[i]++ : cnt0[i]++; };
	LL ans = 0;
	for(int i = 2; i <= n; i++) st.emplace(i);
	while(!st.empty()) {
		int u = *st.begin();
		st.erase(st.begin());
		int v = find(ff[u]);
		// printf("u = %d, v = %d\n", u, v);
		if(v > 1) st.erase(v);
		ans += (LL)cnt1[v] * cnt0[u], cnt0[v] += cnt0[u], cnt1[v] += cnt1[u];
		fa[u] = v;
		if(v > 1) st.emplace(v);
	}
	printf("%lld\n", ans);
	return 0;
} /*
6
1 1 2 3 3
0 1 1 0 0 0
*/