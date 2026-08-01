#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL MOD = 1e9 + 7;

int n;
int a[N];

LL fac[N], invfac[N];
LL qpow(LL x, LL y) {
	LL ret = 1;
	for(; y; (x *= x) %= MOD, y >>= 1) if(y & 1) (ret *= x) %= MOD;
	return ret;
}
LL C(int x, int y) { return x < 0 || y < 0 || x < y ? 0 : fac[x] * invfac[y] % MOD * invfac[x - y] % MOD; }
void get_fac(int mx) {
	fac[0] = 1;
	for(int i = 1; i <= mx; i++) fac[i] = fac[i - 1] * i % MOD;
	invfac[mx] = qpow(fac[mx], MOD - 2);
	for(int i = mx; i >= 1; i--) invfac[i - 1] = invfac[i] * i % MOD;
}

int main() {
	get_fac(2e5);
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		LL ans = 0;
		std::vector<std::pair<int, int>> seq;
		int cnt = 0;
		for(int i = 1; i <= n; i++) {
			if(a[i] == a[i - 1]) cnt++;
			else {
				if(i > 1) seq.emplace_back(a[i - 1], cnt);
				cnt = 1;
			}
		}
		seq.emplace_back(a[n], cnt);
		int sz = seq.size();
		std::vector<LL> val, pre(sz), suf(sz);
		// length = even
		LL prod = 1;
		for(auto [v, cn] : seq) {
			LL sum = 0;
			for(int j = 0; j <= cn; j += 2) sum += C(cn, j);
			val.emplace_back(sum % MOD);
			(prod *= sum % MOD) %= MOD;
		}
		ans += prod;
		// length = odd
		if(seq[0].first == -1) {
			pre[1] = val[1];
			for(int i = 2; i < sz; i++) pre[i] = pre[i - 1] * val[i] % MOD;
			suf[sz - 1] = val[sz - 1];
			for(int i = sz - 2; i >= 0; i--) suf[i] = suf[i + 1] * val[i] % MOD;
			LL base = 0;
			for(int j = 1; j <= seq[0].second; j += 2) base += C(seq[0].second, j);
			base %= MOD;
			for(int i = 1; i + 1 < sz; i++)
				if(seq[i].first + 1 == seq[i + 1].first) {
					LL suml = 0, sumr = 0;
					for(int j = 1; j <= seq[i].second; j += 2) suml += C(seq[i].second, j);
					for(int j = 1; j <= seq[i + 1].second; j += 2) sumr += C(seq[i + 1].second, j);
					LL ret = (suml % MOD) * (sumr % MOD) % MOD * base % MOD;
					if(i - 1 >= 1) (ret *= pre[i - 1]) %= MOD;
					if(i + 2 < sz) (ret *= suf[i + 2]) %= MOD;
					ans += ret;
				}
		}
		ans %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
}