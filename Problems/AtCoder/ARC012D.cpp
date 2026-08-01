#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

typedef long long LL;

const int N = 2e6 + 5;

int n, t;
LL mod;

LL c[N];
bool isprm[N];
std::vector<int> prime;
int d[N];
void sieve(int mx) {
	for(int i = 2; i <= mx; i++) isprm[i] = true;
	for(int i = 2; i <= mx; i++) {
		if(isprm[i]) { prime.push_back(i); d[i] = i; }
		for(int p : prime) {
			if((LL)p * i > mx) break;
			isprm[p * i] = false;
			d[p * i] = p;
			if(i % p == 0) break;
		}
	}
}

LL qpow(LL x, LL y) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }

int main() {
	sieve(2e6);
	scanf("%d%d%lld", &n, &t, &mod);
	for(int i = 1; i <= n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x = std::abs(x), y = std::abs(y);
		if(x + y > t || ((t - (x + y)) & 1)) { puts("0"); return 0; }
		int p = (t - x - y) / 2;
		// C(t, i + j) * C(t, i + j + x)
		c[t] += 2, c[p]--, c[p + x + y]--, c[p + x]--, c[p + y]--;
	}
	for(int i = t; i >= 1; i--) c[i] += c[i + 1];
	for(int i = 2; i <= t; i++) {
		int x = i;
		LL v = c[i];
		c[i] = 0;
		while(x > 1) {
			int y = d[x];
			c[y] += v;
			x /= y;
		}
	}
	LL ans = 1;
	for(int i = 2; i <= t; i++) assert(c[i] >= 0 && (isprm[i] || c[i] == 0)), (ans *= qpow(i, c[i])) %= mod;
	printf("%lld\n", ans);
	return 0;
}