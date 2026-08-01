#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n;
int a[N];

int prv[N], nxt[N];

int cnt[5];
std::set<int> st[5];

bool distinct(int x, int y, int z) { return ((1 << a[x]) | (1 << a[y]) | (1 << a[z])) == 7; }

int main() {
#ifndef DEBUG
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) prv[i] = (i == 1 ? n : i - 1), nxt[i] = (i == n ? 1 : i + 1), cnt[a[i]]++;
	for(int i = 1; i <= n; i++) if(distinct(i, prv[i], nxt[i])) st[a[i]].emplace(i);
	std::vector<std::pair<int, int>> ans;
	while(true) {
		int x;
		if(cnt[0] > 1 && !st[0].empty()) x = *st[0].begin(), cnt[0]--, st[0].erase(st[0].begin());
		else if(cnt[1] > 1 && !st[1].empty()) x = *st[1].begin(), cnt[1]--, st[1].erase(st[1].begin());
		else if(cnt[2] > 1 && !st[2].empty()) x = *st[2].begin(), cnt[2]--, st[2].erase(st[2].begin());
		else break;
		ans.emplace_back(prv[x], nxt[x]);
		if(distinct(prv[prv[x]], prv[x], x)) st[a[prv[x]]].erase(prv[x]);
		if(distinct(nxt[nxt[x]], nxt[x], x)) st[a[nxt[x]]].erase(nxt[x]);
		nxt[prv[x]] = nxt[x], prv[nxt[x]] = prv[x];
		if(distinct(prv[prv[x]], prv[x], nxt[x])) st[a[prv[x]]].emplace(prv[x]);
		if(distinct(nxt[nxt[x]], nxt[x], prv[x])) st[a[nxt[x]]].emplace(nxt[x]);
	}
	if((int)ans.size() < n - 3) puts("no");
	else {
		puts("yes");
		for(auto [x, y] : ans) printf("%d %d\n", x, y);
	}
	return 0;
} /*
5
0 0 1 2 1
*/