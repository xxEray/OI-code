#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const int M = 2e5 + 5;
const int NN = 200 + 5;
const LL MOD = 1e9 + 7;

int n, m, Type;
struct Edge { int to, nxt; } edge[M];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

LL ansd = 1;
int sz[N], vis[N], dfn[N], low[N], stk[N], bl[N];
int scc, time_stamp, top;
void tarjan(int u) {
	dfn[u] = low[u] = ++time_stamp;
	vis[u] = 1;
	stk[top++] = u;
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(vis[v] == 0) tarjan(v), low[u] = std::min(low[u], low[v]);
		else if(vis[v] == 1) low[u] = std::min(low[u], low[v]);
	}
	if(low[u] == dfn[u]) {
		scc++;
		do {
			top--;
			vis[stk[top]] = 2;
			bl[stk[top]] = scc;
			sz[scc]++;
		} while(stk[top] != u);
	}
}

bool isprm[N];
int mf[N]; // min factor
std::vector<int> prime;
void sieve(int mx) {
	for(int i = 2; i <= mx; i++) isprm[i] = true;
	for(int i = 2; i <= mx; i++) {
		if(isprm[i]) prime.push_back(i), mf[i] = i;
		for(int p : prime) {
			if(p * i > mx) break;
			isprm[p * i] = false;
			mf[p * i] = p;
			if(i % p == 0) break;
		}
	}
}

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }
LL lcm(LL x, LL y) { return x / gcd(x, y) * y; }
int cntall[N];

int dep[N], f[N];
void dfs(int u) {
	for(int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if(bl[v] != bl[u]) continue;
		if(dep[v]) f[bl[u]] = gcd(f[bl[u]], std::abs(dep[u] - dep[v] + 1));
		else dep[v] = dep[u] + 1, dfs(v);
	}
}

LL lcmall;
struct Matrix {
	std::bitset<NN> a[NN];
	static Matrix E() {
		Matrix x;
		for(int i = 1; i <= n; i++) x.a[i][i] = 1;
		return x;
	}
};
Matrix mat;
bool operator==(const Matrix &x, const Matrix &y) {
	for(int i = 1; i <= n; i++) if(x.a[i] != y.a[i]) return false;
	return true;
}
Matrix operator*(const Matrix &x, const Matrix &y) {
	Matrix z;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(x.a[i][j]) z.a[i] |= y.a[j];
	return z;
}
Matrix qpow(Matrix x, LL y) { Matrix ret = Matrix::E(); while(true) { if(y & 1) ret = ret * x; if(!(y >>= 1)) return ret; x = x * x; } }

int main() {
#ifndef DEBUG
	freopen("lost.in", "r", stdin);
	freopen("lost.out", "w", stdout);
#endif
	sieve(1e5);
	scanf("%d%d%d", &n, &m, &Type);
	for(int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		if(Type) mat.a[u][v] = 1;
	}
	for(int i = 1; i <= n; i++) if(!vis[i]) tarjan(i);
	// printf("bl: "); for(int i = 1; i <= n; i++) printf("%d ", bl[i]); puts("");
	for(int i = 1; i <= n; i++) if(!dep[i]) dep[i] = 1, dfs(i);
	// for(int i = 1; i <= scc; i++) printf("f[%d] = %d\n", i, f[i]);
	if(Type) {
		lcmall = 1;
		for(int i = 1; i <= scc; i++) if(f[i]) lcmall = lcm(lcmall, f[i]);
		// printf("lcmall = %lld\n", lcmall);
		int l = 1, r = n * n * n;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(qpow(mat, mid) == qpow(mat, mid + lcmall)) r = mid;
			else l = mid + 1;
		}
		printf("%d ", l);
	}
	for(int i = 1; i <= scc; i++) {
		int val = f[i];
		while(val > 1) {
			int p = mf[val];
			int c = 0;
			while(val % p == 0) c++, val /= p;
			cntall[p] = std::max(cntall[p], c);
		}
	}
	for(int i = 1; i <= 100000; i++) (ansd *= qpow(i, cntall[i])) %= MOD;
	printf("%lld\n", ansd);
	return 0;
} /*
5 5 1
1 2
2 3
3 4
4 5
5 3
*/