#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;
LL a[N], c[N];

std::map<LL, LL> must, sum;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		must.clear(), sum.clear();
		scanf("%d", &n);
		LL sumall = 0, lb = 0, rb = 0;
		while(n--) {
			LL l, r, s = 0;
			scanf("%d%lld%lld", &m, &l, &r);
			lb += l, rb += r;
			for(int i = 1; i <= m; i++) scanf("%lld", &a[i]);
			for(int i = 1; i <= m; i++) scanf("%lld", &c[i]), s += c[i];
			sumall += r;
			for(int i = 1; i <= m; i++) {
				must[a[i]] += std::max(l - (s - c[i]), 0LL);
				sum[a[i]] += r - std::max(l, std::min(r, s - c[i]));
			}
		}
		LL ans = LLINF;
		for(LL v = lb; v <= rb; v++)
			if(!must.count(v)) { ans = 0; break; }
			else ans = std::min(ans, must[v] + std::max(v - (sumall - sum[v]), 0LL)); // , printf("%lld: ans = %lld\n", v, ans);
		printf("%lld\n", ans);
	}
	return 0;
}