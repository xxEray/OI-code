#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, K;
struct Segment { int l, r; } a[N];

LL solve1() {
	std::vector<Segment> vct;
	LL ret = 0;
	for(int i = 1; i <= n; i++) vct.push_back(a[i]);
	std::sort(vct.begin(), vct.end(), [&](Segment x, Segment y) { return x.r - x.l > y.r - y.l; });
	for(int i = 0; i < K - 1; i++) ret += vct[i].r - vct[i].l;
	int mxl = -INF, mnr = INF;
	for(int i = K - 1; i < n; i++) mxl = std::max(mxl, vct[i].l), mnr = std::min(mnr, vct[i].r);
	ret += std::max(mnr - mxl, 0);
	// printf("%lld\n", ret);
	return ret;
}

LL solve2() {
	std::sort(a + 1, a + n + 1, [&](Segment x, Segment y) { return x.r == y.r ? x.l > y.l : x.r < y.r; });
	std::vector<LL> b, d;
	std::vector<Segment> c;
	int mxl = -1;
	for(int i = 1; i <= n; i++) {
		if(mxl >= a[i].l) b.push_back(a[i].r - a[i].l);
		else c.push_back(a[i]);
		mxl = std::max(mxl, a[i].l);
	}
	std::sort(b.begin(), b.end(), [&](LL x, LL y) { return x > y; });
	std::sort(c.begin(), c.end(), [&](Segment x, Segment y) { return x.l < y.l; });
	// for(auto p : c) printf("[%d, %d] ", p.l, p.r);
	// puts("");
	// for(auto x : b) printf("%lld ", x);
	// puts("");
	for(int i = 1; i < (int)b.size(); i++) b[i] += b[i - 1];
	int sz = c.size();
	for(int i = 0; i < sz - 1; i++) d.push_back(c[i + 1].r - c[i].l);
	std::sort(d.begin(), d.end(), [&](LL x, LL y) { return x > y; });
	for(int i = 1; i < (int)d.size(); i++) d[i] += d[i - 1];
	int szb = b.size(), szd = d.size();
	LL ans = 0;
	for(int i = 0; i < K; i++) if(i - 1 < szb && K - i - 2 < szd)
		ans = std::max(ans, (i >= 1 ? b[i - 1] : 0) + (K - i >= 2 ? d[K - i - 2] : 0) + c[0].r - c[sz - 1].l);
	return ans;
}

int main() {
	// freopen("lunatic.in", "r", stdin);
	// freopen("lunatic.out", "w", stdout);
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].l, &a[i].r);
	LL ans = std::max(solve1(), solve2());
	printf("%lld\n", ans);
	return 0;
} /*
7 3
14424 40061 x
21703 31232 x
24681 49472 x
26504 28027
26768 43700 x
27857 39991 x
29444 39896

*/