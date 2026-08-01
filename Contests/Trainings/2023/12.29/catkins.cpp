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

const int N = 5e5 + 5;

int n, Q, encrypt_;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int fa[N], dfn[N], time_stamp;
void dfs(int u, int ff) {
	dfn[u] = ++time_stamp;
	std::vector<int> son;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != ff) son.emplace_back(edge[i].to);
	std::sort(son.begin(), son.end());
	for(int v : son) dfs(v, u);
	fa[dfn[u]] = dfn[ff];
}

struct SegNode { int v, ls, rs; } t[N * 30];
struct SegmentTree {
	static int copy(int x) { static int k = 0; k++; assert(k < N * 30); t[k] = t[x]; return k; }
	int add(int qind, int qv, int x, int l = 1, int r = n) {
		assert(1 <= qind && qind <= n);
		int y = copy(x);
		if(l == r) { t[y].v += qv; return y; }
		int mid = (l + r) >> 1;
		if(qind <= mid) t[y].ls = add(qind, qv, t[y].ls, l, mid);
		else t[y].rs = add(qind, qv, t[y].rs, mid + 1, r);
		t[y].v = t[t[y].ls].v + t[t[y].rs].v;
		return y;
	}
	int sum(int ql, int qr, int x, int y, int l = 1, int r = n) {
		assert(1 <= ql && ql <= qr && qr <= n);
		if(ql <= l && r <= qr) return t[y].v - t[x].v;
		int mid = (l + r) >> 1;
		if(qr <= mid) return sum(ql, qr, t[x].ls, t[y].ls, l, mid);
		else if(ql > mid) return sum(ql, qr, t[x].rs, t[y].rs, mid + 1, r);
		else return sum(ql, qr, t[x].ls, t[y].ls, l, mid) + sum(ql, qr, t[x].rs, t[y].rs, mid + 1, r);
	}
	int rmost(int qr, int x, int y, int l = 1, int r = n) {
		assert(1 <= qr && qr <= n);
		if(l == r) return t[y].v - t[x].v ? l : 0;
		int mid = (l + r) >> 1;
		if(qr <= mid) return rmost(qr, t[x].ls, t[y].ls, l, mid);
		if(t[t[y].rs].v - t[t[x].rs].v) {
			int ret = rmost(qr, t[x].rs, t[y].rs, mid + 1, r);
			if(ret) return ret;
		}
		return rmost(qr, t[x].ls, t[y].ls, l, mid);
	}
} seg;
int ver[N];

int solve(std::vector<std::pair<int, int>> &vct) {
	if(vct.empty()) return 0;
	std::vector<int> endpoints;
	if(vct.front().first > 1) endpoints.emplace_back(1);
	int ans = 0;
	for(auto [l, r] : vct) endpoints.emplace_back(l), endpoints.emplace_back(r + 1), ans += r - l + 1;
	for(auto [l, r] : vct) {
		ans -= seg.sum(l, r, ver[l - 1], ver[r]);
		// printf("[%d, %d]:\n", l, r);
		int k = l - 1;
		while(k) {
			int p = seg.rmost(k, ver[l - 1], ver[r]);
			// printf("p = %d\n", p);
			if(!p) break;
			auto it = std::upper_bound(vct.begin(), vct.end(), std::make_pair(p, n + 1));
			if(it != vct.begin() && (--it)->second >= p) {
				ans -= seg.sum(it->first, it->second, ver[l - 1], ver[r]);
			}
			auto it2 = std::upper_bound(endpoints.begin(), endpoints.end(), p);
			assert(it2 != endpoints.begin());
			k = *--it2 - 1;
			// printf("k = %d, ans = %d\n", k, ans);
		}
	}
	return ans;
}

int main() {
#ifndef DEBUG
	freopen("catkins.in", "r", stdin);
	freopen("catkins.out", "w", stdout);
#endif
	read(n), read(Q), read(encrypt_);
	for(int i = 1; i < n; i++) { int u, v; read(u), read(v); add_edge(u, v), add_edge(v, u); }
	dfs(1, 0);
	// printf("fa: "); for(int i = 1; i <= n; i++) printf("%d ", fa[i]); puts("");
	ver[1] = ver[0];
	for(int i = 2; i <= n; i++) ver[i] = seg.add(fa[i], 1, ver[i - 1]);
	int lastans = 0;
	while(Q--) {
		int K;
		read(K);
		std::vector<std::pair<int, int>> vct;
		while(K--) {
			int l, r;
			read(l), read(r);
			if(encrypt_) l ^= lastans, r ^= lastans;
			vct.emplace_back(l, r);
		}
		lastans = solve(vct) - 1;
		write(lastans, '\n');
	}
	return 0;
}