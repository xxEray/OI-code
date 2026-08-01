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

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, Q;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

template<int R, int C> struct Matrix { int a[R][C]; };
template<int R, int Q, int C> Matrix<R, C> operator*(const Matrix<R, Q> &x, const Matrix<Q, C> &y) {
	Matrix<R, C> z;
	for(int i = 0; i < R; i++) for(int j = 0; j < C; j++) z.a[i][j] = -INF;
	for(int i = 0; i < R; i++) for(int j = 0; j < Q; j++) for(int k = 0; k < C; k++) z.a[i][k] = std::max(z.a[i][k], x.a[i][j] + y.a[j][k]);
	return z;
}
const Matrix<1, 3> initial = {{{-INF, -INF, 0}}};
Matrix<3, 3> trans[N];
int fa[N], dep[N];
void dfs(int u) {
	dep[u] = dep[fa[u]] + 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa[u]) {
		int v = edge[i].to;
		fa[v] = u;
		dfs(v);
	}
}
int gofa[19][N];
Matrix<3, 3> goprod[19][N];
void binary_lifting() {
	for(int i = 1; i <= n; i++) gofa[0][i] = fa[i], goprod[0][i] = trans[i];
	for(int j = 1; j <= 18; j++)
		for(int i = 1; i <= n; i++) {
			gofa[j][i] = gofa[j - 1][gofa[j - 1][i]];
			goprod[j][i] = goprod[j - 1][i] * goprod[j - 1][gofa[j - 1][i]];
		}
}

int main() {
#ifndef DEBUG
	freopen("path.in", "r", stdin);
	freopen("path.out", "w", stdout);
#endif
	read(n), read(Q);
	for(int i = 1; i < n; i++) { int u, v; read(u), read(v); add_edge(u, v), add_edge(v, u); }
	for(int i = 1; i <= n; i++) {
		int v;
		read(v);
		trans[i].a[0][0] = 0, trans[i].a[0][1] = -INF, trans[i].a[0][2] = -INF;
		trans[i].a[1][0] = v, trans[i].a[1][1] = 0, trans[i].a[1][2] = -INF;
		trans[i].a[2][0] = -INF, trans[i].a[2][1] = -v, trans[i].a[2][2] = 0;
	}
	dfs(1), binary_lifting();
	while(Q--) {
		int u, v;
		read(u), read(v);
		Matrix<1, 3> ret = initial;
		for(int i = 18; i >= 0 && dep[u] >= dep[v]; i--) if((dep[u] - dep[v] + 1) >> i & 1) {
			ret = ret * goprod[i][u];
			u = gofa[i][u];
		}
		// printf("[%d %d %d]\n", ret.a[0][0], ret.a[0][1], ret.a[0][2]);
		write(std::max(ret.a[0][0], 0), '\n');
	}
	return 0;
} /*
5 2
1 2
2 3
3 4
4 5
1 5 4 2 3
4 1
5 3
*/