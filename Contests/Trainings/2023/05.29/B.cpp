#include <bits/stdc++.h>

#define SZ(x) ((int)(x).size())

const int N = 1e5 + 5;
const int M = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m, Q;
std::vector<int> to[N];
struct Query { int x, id; std::vector<int> r; } q[N];

int sqrtn;

int t[N], out[N];
std::vector<std::pair<int, int>> f[N], tmp, tmp2;
std::vector<int> qr[N];
int g[N];

int main() {
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); to[v].push_back(u); }
	while(sqrtn * sqrtn <= n) sqrtn++;
	for(int i = 1; i <= Q; i++) {
		int k, x; scanf("%d%d", &q[i].x, &k);
		while(k--) scanf("%d", &x), q[i].r.push_back(x);
		q[i].id = i;
		if(SZ(q[i].r) <= sqrtn) qr[q[i].x].push_back(i);
		else qr[0].push_back(i);
	}
	tmp.reserve(sqrtn);
	for(int i = 1; i <= n; i++) {
		f[i].reserve(sqrtn);
		for(int j : to[i]) {
			tmp.clear();
			tmp2 = f[j];
			while(SZ(tmp) <= sqrtn && (!f[i].empty() || !f[j].empty())) {
				std::pair<int, int> x;
				if(f[j].empty() || (!f[i].empty() && f[i].back().second > f[j].back().second + 1)) x = f[i].back(), f[i].pop_back();
				else x = {f[j].back().first, f[j].back().second + 1}, f[j].pop_back();
				if(t[x.first]) continue;
				else t[x.first] = true, tmp.push_back(x);
			}
			f[j] = tmp2;
			f[i].swap(tmp);
			for(auto x : f[i]) t[x.first] = false;
			std::reverse(f[i].begin(), f[i].end());
		}
		if(SZ(f[i]) < sqrtn) f[i].insert(f[i].begin(), {i, 0});
		f[i].shrink_to_fit();
		for(int j : qr[i]) {
			for(int x : q[j].r) t[x] = true;
			std::pair<int, int> ans = {0, 0};
			for(auto x : f[i]) if(!t[x.first]) ans = x;
			out[q[j].id] = (ans.first ? ans.second : -1);
			for(int x : q[j].r) t[x] = false;
		}
	}
	for(int j : qr[0]) {
		for(int x : q[j].r) t[x] = true;
		for(int i = 1; i <= n; i++) g[i] = (t[i] ? -INF : 0);
		for(int i = 1; i <= n; i++)
			for(int ii : to[i])
				g[i] = std::max(g[i], g[ii] + 1);
		out[q[j].id] = (g[q[j].x] < 0 ? -1 : g[q[j].x]);
		for(int x : q[j].r) t[x] = false;
	}
	for(int i = 1; i <= Q; i++) printf("%d\n", out[i]);
	return 0;
}
