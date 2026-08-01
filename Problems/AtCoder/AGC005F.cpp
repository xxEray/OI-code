#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 924844033;

template<LL mod, LL g> struct NTT {
	int rev[N * 4];
	int limit;
	int init(int mx) {
		int w = 0;
		limit = 1;
		while(limit <= mx) limit <<= 1, w++; // w = log2(limit)
		for(int i = 0; i < limit; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (w - 1));
		return limit;
	}
	inline LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
	inline LL inv(LL x) { return qpow(x, mod - 2); }
	void trans(LL *a, int type) { // type = 1 / -1
		LL invg = inv(g);
		for(int i = 0; i < limit; i++) if(i < rev[i]) std::swap(a[i], a[rev[i]]);
		for(int i = 1; i < limit; i <<= 1) {
			LL wn = qpow(type == -1 ? invg : g, (mod - 1) / (i << 1));
			for(int j = 0; j < limit; j += (i << 1)) {
				LL w = 1;
				for(int k = 0; k < i; k++, w = w * wn % mod) {
					LL x = a[j + k], y = w * a[j + i + k] % mod;
					a[j + k] = (x + y) % mod;
					a[j + i + k] = (x - y + mod) % mod;
				}
			}
		}
		if(type == -1) for(int i = 0; i < limit; i++) (a[i] *= inv(limit)) %= mod;
	}
	int trans(LL *a, int n, int type) { int ret = init(n); trans(a, type); return ret; }
};
NTT<MOD, 5> ntt;

int n, m;
struct Edge { int to, nxt; } edge[N << 1];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

LL fac[N], invfac[N];
LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % MOD; if(!(y >>= 1)) return ret; x = x * x % MOD; } }
LL inv(LL x) { return qpow(x, MOD - 2); }
LL C(LL x, LL y) { return fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_factorial(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = inv(fac[mx]);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int sz[N], cnt[N];
void dfs(int u, int fa) {
	sz[u] = 1;
	for(int i = head[u]; i; i = edge[i].nxt) if(edge[i].to != fa) {
		int v = edge[i].to;
		dfs(v, u);
		sz[u] += sz[v];
		cnt[sz[v]]++, cnt[n - sz[v]]++;
	}
}

LL a[N * 4], b[N * 4];

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) { int u, v; scanf("%d%d", &u, &v); add_edge(u, v), add_edge(v, u); }
	get_factorial(n);
	dfs(1, 0);
	int limit = ntt.init((n + 1) * 2);
	for(int i = 0; i <= n; i++) a[n - i] = cnt[i] * fac[i] % MOD, b[i] = invfac[i];
	ntt.trans(a, 1), ntt.trans(b, 1);
	for(int i = 0; i < limit; i++) (a[i] *= b[i]) %= MOD;
	ntt.trans(a, -1);
	for(int k = 1; k <= n; k++) printf("%lld\n", (n * C(n, k) % MOD - invfac[k] * a[n - k] % MOD + MOD) % MOD);
	return 0;
}