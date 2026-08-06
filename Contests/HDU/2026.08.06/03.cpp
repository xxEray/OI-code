#include <bits/stdc++.h>
using std::cin;
using std::cout;

typedef long long LL;

const int N = 2e6 + 5;
const int MXV = 1e7 + 5;
const int B = 1000;

int n;
LL a[N];

bool isprm[MXV];
std::vector<int> prime;
int factor[MXV];
void sieve(int mx) {
	for(int i = 2; i <= mx; i++) isprm[i] = true;
	for(int i = 2; i <= mx; i++) {
		if(isprm[i]) prime.push_back(i), factor[i] = i;
		for(int p : prime) {
			if((LL)p * i > mx) break;
			isprm[i * p] = false;
			factor[i * p] = p;
			if(i % p == 0) break;
		}
	}
}

LL ans[B + 5];

LL phi(LL x, LL y) {
	std::vector<int> vct;
	while(x > 1) vct.emplace_back(factor[x]), x /= factor[x];
	while(y > 1) vct.emplace_back(factor[y]), y /= factor[y];
	std::sort(vct.begin(), vct.end()), vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
	LL ret = x * y;
	for(LL z : vct) ret = ret / z * (z - 1);
	return ret;
}

int main() {
	freopen("out.txt", "w", stdout);
	std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	sieve(1e7);
	int T; cin >> T;
	while(T--) {
		cin >> n;
		for(int i = 1; i <= n; i++) cin >> a[i];
		std::sort(a + 1, a + n + 1, std::greater<LL>());
		for(LL x = 1; x <= 10000000; x++) {
			LL ret = 0;
			for(int j = 1; j <= std::min(n, 5); j++)
				ret = std::max(ret, phi(x, a[j]));
			ans[x % B] += x / B * ret;
		}
		for(int i = 0; i < B; i++) cout << ans[i] << '\n';
	}
	return 0;
}