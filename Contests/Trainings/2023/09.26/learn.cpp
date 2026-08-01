#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D;
	char rdc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char c = rdc(), fl = 0;
		while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
		for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
		if(fl) x = -x;
	}
}
using FIO::read;

const int N = 1e6 + 5;

int n, m;
struct Node { int v, id; };
int now[N];
std::vector<Node> a[N];
std::vector<int> b[N];

int d[N];
int ans;

int main() {
#ifndef DEBUG
	freopen("learn.in", "r", stdin);
	freopen("learn.out", "w", stdout);
#endif
	read(n), read(m);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
		int x;
		read(x);
		if(x) d[i]++, a[j].push_back({x, i});
	}
	for(int i = 1; i <= n; i++) b[i].resize(m + 1);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) read(b[i][j]);
	for(int i = 1; i <= m; i++) std::sort(a[i].begin(), a[i].end(), [&](Node x, Node y) { return x.v > y.v; });
	std::vector<int> q;
	for(int i = 1; i <= n; i++) if(!d[i]) q.push_back(i);
	while(!q.empty()) {
		int u = q.back();
		q.pop_back();
		ans++;
		for(int j = 1; j <= m; j++) {
			now[j] += b[u][j];
			if(now[j] > 1000000000) now[j] = 1000000000;
			while(!a[j].empty() && a[j].back().v <= now[j]) {
				d[a[j].back().id]--;
				if(d[a[j].back().id] == 0) q.push_back(a[j].back().id);
				a[j].pop_back();
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}