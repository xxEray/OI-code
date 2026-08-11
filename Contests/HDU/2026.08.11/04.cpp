#include <bits/stdc++.h>
using std::cin;
using std::cout;

typedef unsigned long long ull;

const int N = 2e5 + 5;

int n;
std::vector<int> to[N];

int rt;

ull random(ull x) {
	auto f = [](ull y) -> ull { return (ull)y * y * y * 16810086 + 11335577; };
	return f(x) + f(x >> 32);
}

ull f[N], g[N];

int fa[N];
void dfs1(int u) {
	f[u] = 1027;
	for(int v : to[u]) if(v != fa[u]) {
		fa[v] = u;
		dfs1(v);
		f[u] += random(f[v]);
	}
}

void dfs2(int u) {
	ull hsh = 1027 + (u == rt ? 0 : random(g[u]));
	for(int v : to[u]) if(v != fa[u]) hsh += random(f[v]);
	for(int v : to[u]) if(v != fa[u]) {
		g[v] = hsh - random(f[v]);
		dfs2(v);
	}
}

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

bool del[N];
bool ans[N];

int main() {
	std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while(T--) {
		cin >> n;
		for(int i = 1; i <= n; i++) to[i].clear(), ans[i] = false, del[i] = false;
		for(int i = 1; i < n; i++) {
			int u, v;
			cin >> u >> v;
			to[u].emplace_back(v), to[v].emplace_back(u);
		}
		for(int i = 1; i <= n; i++) {
			int sz = 0, u = 0, v = 0;
			for(int d : to[i]) if(!del[d]) sz++, (u == 0 ? u : v) = d;
			if(sz != 2) continue;
			to[u].emplace_back(v);
			to[v].emplace_back(u);
			del[i] = true;
		}
		for(int u = 1; u <= n; u++) {
			std::vector<int> tmp;
			for(int v : to[u]) if(!del[v]) tmp.emplace_back(v);
			to[u].swap(tmp);
		}
		for(rt = 1; rt <= n; rt++) if(!del[rt]) break;
		dfs1(rt), g[rt] = 0, dfs2(rt);
		for(int u = 1; u <= n; u++) if(!del[u]) {
			std::vector<ull> vct;
			for(int v : to[u]) if(v != fa[u]) vct.emplace_back(f[v]);
			if(u != rt) vct.emplace_back(g[u]);
			std::sort(vct.begin(), vct.end());
			ull last = 0; int cnt = 0, gc = 0;
			for(ull v : vct)
				if(cnt == 0) last = v, cnt++;
				else if(last == v) cnt++;
				else gc = gcd(cnt, gc), cnt = 1, last = v;
			gc = gcd(cnt, gc);
			ans[gc] = true;
		}
		for(int i = 1; i <= n; i++) if(!del[i] && i != rt && f[i] == g[i]) { ans[2] = true; break; }
		for(int i = 1; i <= n; i++)
			for(int j = i + i; j <= n; j += i)
				ans[i] |= ans[j];
		int cnt = 0;
		for(int i = 1; i <= n; i++) cnt += ans[i];
		cout << cnt << '\n';
		for(int i = 1; i <= n; i++) if(ans[i]) cout << i << ' ';
		cout << '\n';
	}
	return 0;
} /*
2
10
1 2
2 3
3 4
4 5
2 7
4 6
3 8
8 9
8 10
8
1 2
1 3
1 4
1 5
1 6
1 7
2 8
*/