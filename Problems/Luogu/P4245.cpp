#include <cstdio>
#include <algorithm>

typedef long long LL;
const int N = 4e5 + 5;
const LL P1 = 469762049;
const LL P2 = 998244353;
const LL P3 = 1004535809;

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

LL a[N], b[N], ca[N], cb[N], ans1[N], ans2[N], ans3[N];
int n, m;
LL P;

LL qpow(LL x, LL y, LL mod) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }
LL inv(LL x, LL mod) { return qpow(x, mod - 2, mod); }

NTT<P1, 3> ntt1;
NTT<P2, 3> ntt2;
NTT<P3, 3> ntt3;

int main() {
	scanf("%d%d%lld", &n, &m, &P);
	for(int i = 0; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 0; i <= m; i++) scanf("%lld", &b[i]);
	int limit = ntt1.init(n + m);
	ntt2.init(n + m), ntt3.init(n + m);
	for(int i = 0; i <= limit; i++) ca[i] = a[i], cb[i] = b[i];
	ntt1.trans(ca, 1), ntt1.trans(cb, 1);
	for(int i = 0; i <= limit; i++) ans1[i] = ca[i] * cb[i] % P1;
	ntt1.trans(ans1, -1);
	for(int i = 0; i <= limit; i++) ca[i] = a[i], cb[i] = b[i];
	ntt2.trans(ca, 1), ntt2.trans(cb, 1);
	for(int i = 0; i <= limit; i++) ans2[i] = ca[i] * cb[i] % P2;
	ntt2.trans(ans2, -1);
	for(int i = 0; i <= limit; i++) ca[i] = a[i], cb[i] = b[i];
	ntt3.trans(ca, 1), ntt3.trans(cb, 1);
	for(int i = 0; i <= limit; i++) ans3[i] = ca[i] * cb[i] % P3;
	ntt3.trans(ans3, -1);
	for(int i = 0; i <= n + m; i++) {
		// 三个质数可以手推 CRT
		// 看着这个推也可以 https://www.cnblogs.com/Memory-of-winter/p/10223844.html
		LL out = 0;
		LL tmp = ans1[i] + (ans2[i] - ans1[i] + P2) % P2 * inv(P1, P2) % P2 * P1;
		out = (tmp + (ans3[i] - tmp % P3 + P3) % P3 * inv(P1 * P2 % P3, P3) % P3 * P1 % P * P2 % P) % P;
		printf("%lld ", out);
	}
	puts("");
	return 0;
}