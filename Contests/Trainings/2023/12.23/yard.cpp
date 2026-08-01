#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D, out[D], *O = out;
	char rdc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char c = rdc(), fl = 0;
		while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
		for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
		if(fl) x = -x;
	}
	void wrtc(char c) { (O == out + D ? fwrite(O = out, 1, D, stdout) : 0), *O++ = c; }
	template<typename T> void write(T x, char ch = 0) {
		static char c[60]; int top = 0;
		if(x < 0) wrtc('-'), x = -x;
		do c[++top] = x % 10, x /= 10; while(x);
		while(top) wrtc(c[top--] + '0');
		if(ch) wrtc(ch);
	}
	void flush() { fwrite(out, 1, O - out, stdout); }
	struct Flusher { ~Flusher() { flush(); } } flusher;
}
using FIO::write;
using FIO::read;

typedef long long LL;

const int N = 2e5 + 5;

int n, d;
int a[N];
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

std::vector<int> prime;
bool isprm[N];
int mx[N];
std::vector<std::pair<int, int>> fac[N];
void sieve() {
	for(int i = 2; i <= n; i++) isprm[i] = true;
	for(int i = 2; i <= n; i++) {
		if(isprm[i]) prime.emplace_back(i), fac[i].emplace_back(i, 1), mx[i] = 1;
		for(int p : prime) {
			if((long long)p * i > n) break;
			isprm[p * i] = false;
			if(i % p == 0) {
				fac[i * p] = fac[i];
				fac[i * p].front().second++;
				mx[i * p] = std::max(mx[i], fac[i * p].front().second);
				break;
			}
			mx[i * p] = mx[i];
			fac[i * p].emplace_back(p, 1);
			fac[i * p].insert(fac[i * p].end(), fac[i].begin(), fac[i].end());
		}
	}
}

std::vector<int> vct1[N];
std::vector<std::pair<int, int>> vct2[N];
int val[N];
LL ff[(1 << 20) + 5];
void preprocess() {
	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n; j += i)
			vct1[j].emplace_back(i);
	ff[0] = 1;
	for(int i = 1; i <= n; i++) {
		if(mx[i] > d) continue;
		int m = fac[i].size();
		std::vector<LL> tmp;
		tmp.reserve(m);
		for(int j = 0; j < m; j++) {
			LL v = 1;
			for(int _ = 0; _ < d + 1 - (int)fac[i][j].second; _++) {
				v *= fac[i][j].first;
				if(v > n) { v = -1; break; }
			}
			if(v != -1) tmp.emplace_back(v);
		}
		m = tmp.size();
		for(int j = 0; j < m; j++)
			for(int s = 0; s < (1 << j); s++)
				if(ff[s] != -1) {
					ff[(1 << j) | s] = tmp[j] * ff[s];
					if(ff[(1 << j) | s] > n) ff[(1 << j) | s] = -1;
					else vct2[i].emplace_back(ff[(1 << j) | s], (__builtin_popcount(s) & 1) ? -1 : 1);
				} else ff[(1 << j) | s] = -1;
	}
	for(int i = 1; i <= n; i++)
		if(mx[i] > d) val[i] = 0;
		else {
			for(const auto &[p, j] : fac[i]) val[i] ^= (j & 1);
			val[i] = (val[i] ? -1 : 1);
		}
}

int sz[N], hson[N];
std::vector<int> st[N];
void predfs(int u, int fa) {
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		predfs(v, u);
		sz[u] += sz[v];
		if(!hson[u] || sz[hson[u]] < sz[v]) hson[u] = v;
	}
	// printf("hson[%d] = %d\n", u, hson[u]);
}

LL sum[N], f[N];
int tin[N];
void dfs(int u, int fa) {
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa && edge[i].to != hson[u]) {
		int v = edge[i].to;
		dfs(v, u);
		for(int x : st[v]) for(int y : vct1[x]) tin[y] = 0;
	}
	f[u] = (2 * mx[a[u]] <= d), sum[u] = val[a[u]], st[u].emplace_back(a[u]);
	if(hson[u]) {
		dfs(hson[u], u);
		auto merge = [&](int x, int y) {
			if(st[y].size() > st[x].size()) st[x].swap(st[y]);
			st[x].insert(st[x].end(), st[y].begin(), st[y].end());
			st[y].clear(), st[y].shrink_to_fit();
		};
		f[u] += sum[u] * sum[hson[u]] + f[hson[u]];
		sum[u] += sum[hson[u]];
		for(const auto &[x, w] : vct2[a[u]]) f[u] -= tin[x] * w * val[a[u]];
		for(int x : vct1[a[u]]) tin[x] += val[a[u]];
		merge(u, hson[u]);
		for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa && edge[i].to != hson[u]) {
			int v = edge[i].to;
			f[u] += sum[u] * sum[v] + f[v];
			sum[u] += sum[v];
			for(int x : st[v]) for(const auto &[y, w] : vct2[x]) f[u] -= tin[y] * w * val[x];
			for(int x : st[v]) for(int y : vct1[x]) tin[y] += val[x];
			merge(u, v);
		}
	} else {
		for(int x : vct1[a[u]]) tin[x] += val[a[u]];
	}
	// printf("%d: f=%lld, sum=%lld\n", u, f[u], sum[u]);
}

int main() {
#ifndef DEBUG
	freopen("yard.in", "r", stdin);
	freopen("yard.out", "w", stdout);
#endif
	read(n), read(d);
	for(int i = 1; i < n; i++) { int u, v; read(u), read(v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) read(a[i]);
	sieve(), preprocess();
	predfs(1, 0);
	dfs(1, 0);
	for(int i = 1; i <= n; i++) write(f[i], '\n');
	return 0;
} /*
4 2
1 2
1 3
3 4
1 3 4 2
*/