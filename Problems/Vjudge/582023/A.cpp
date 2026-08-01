#include <bits/stdc++.h>

typedef long long LL;

const int N = 5e4 + 5;
const int D = 1e4;

int n, Q;
int p, c;
int a[N];

LL qpow(LL x, LL y, LL mod) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }

int getphi(int x) {
	int v = x;
	for(int i = 2; (LL)i * i <= x; i++) if(x % i == 0) {
		v = v / i * (i - 1);
		while(x % i == 0) x /= i;
	}
	if(x > 1) v = v / x * (x - 1);
	return v;
}

int cn;
int phi[45];
int cnt[N];
int f[N][45], g[N];
std::set<int> st;

int power1[45][D + 5], power2[45][D + 5];

struct BIT {
	int t[N];
	void add(int x, int v) { while(x <= n) (t[x] += v) %= p, x += x & -x; }
	int query(int r) const { int ret = 0; while(r) (ret += t[r]) %= p, r -= r & -r; return ret; }
	int query(int l, int r) const { return (query(r) - query(l - 1) + p) % p; }
} bit;

inline int getpow(int y, int modid) { return (LL)power1[modid][y / D] * power2[modid][y % D] % phi[modid]; }

int main() {
	scanf("%d%d%d%d", &n, &Q, &p, &c);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), bit.add(i, a[i]), g[i] = a[i];
	for(int i = 1; i <= n; i++) st.insert(i);
	int q = p;
	phi[0] = q;
	while(q > 1) q = phi[++cn] = getphi(q);
	// printf("cn = %d\n", cn);
	// printf("phi: "); for(int i = 0; i <= cn; i++) printf("%d ", phi[i]); puts("");
	for(int j = 0; j <= cn; j++) for(int i = 0; i <= D; i++) power1[j][i] = qpow(c, i * D, phi[j]), power2[j][i] = qpow(c, i, phi[j]);
	for(int i = 1; i <= n; i++) for(int j = 0; j <= cn; j++) f[i][j] = (a[i] < phi[j] ? a[i] : a[i] % phi[j] + phi[j]);
	while(Q--) {
		int t, l, r;
		scanf("%d%d%d", &t, &l, &r);
		if(t == 0) {
			std::vector<int> to_erase;
			for(auto it = st.lower_bound(l); it != st.end() && *it <= r; it++) {
				int i = *it;
				g[i] = (powl(c, g[i]) > 1e9 ? 1e9 : qpow(c, g[i], 1e9 + 7));
				for(int j = 0; j <= cn; j++) f[i][j] = getpow(f[i][j + 1], j) + (g[i] >= phi[j]) * phi[j];
				bit.add(i, (f[i][0] - a[i] + p) % p), a[i] = f[i][0] % p;
				cnt[i]++;
				if(cnt[i] >= cn + 1) to_erase.push_back(i);
			}
			for(int x : to_erase) st.erase(x);
		} else printf("%d\n", bit.query(l, r));
	}
	return 0;
}