#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

std::vector<LL> fac;

int size(LL x) { int ret = 0; while(x) ret++, x &= x - 1; return ret; }

int main() {
	LL ret = 1;
	for(int i = 1; i <= 14; i++) ret *= i, fac.push_back(ret);
	int T; scanf("%d", &T);
	while(T--) {
		LL sum;
		scanf("%lld", &sum);
		int ans = 1000;
		for(int s = 0; s < (1 << 14); s++) {
			ret = sum;
			for(int j = 0; j < 14; j++) if(s >> j & 1) ret -= fac[j];
			if(ret >= 0) ans = std::min(ans, size(s) + size(ret));
		}
		printf("%d\n", ans);
	}
	return 0;
}