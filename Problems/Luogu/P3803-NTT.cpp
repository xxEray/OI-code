#include <cstdio>
typedef long long LL;
const int N = 4e6 + 5; // 2 * (n + m)
template<LL mod, LL g> struct NTT {
	int rev[N];
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

const int MOD = 998244353;

LL a[N], b[N];
int n, m;

NTT<MOD, 3> ntt;

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 0; i <= m; i++) scanf("%lld", &b[i]);
	int limit = ntt.init(n + m);
	ntt.trans(a, 1);
	ntt.trans(b, 1);
	for(int i = 0; i < limit; i++) (a[i] *= b[i]) %= MOD;
	ntt.trans(a, -1);
	for(int i = 0; i <= n + m; i++) printf("%lld ", a[i]);
	return 0;
}