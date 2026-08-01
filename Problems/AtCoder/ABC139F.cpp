#include <algorithm>
#include <cstdio>
#include <map>
#include <cmath>

typedef long long LL;

const int N = 100 + 5;

LL x[N], y[N];
int n;

std::map<int, std::pair<LL, LL>> f, tmp;

LL sqr(LL t) { return t * t; }

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld%lld", &x[i], &y[i]);
	f.insert({0, {0, 0}});
	for(int i = 1; i <= n; i++) {
		tmp = f;
		for(auto pj : tmp) {
			int j = pj.first;
			if(tmp.find(j + x[i]) == tmp.end()) f[j + x[i]] = {tmp[j].first + y[i], tmp[j].second + y[i]};
			else { auto &po = tmp[j], &pn = f[j + x[i]]; pn = {std::min(po.first + y[i], pn.first), std::max(po.second + y[i], pn.second)}; }
		}
	}
	LL ans = 0;
	for(auto p : f) ans = std::max({ans, sqr(p.first) + sqr(p.second.first), sqr(p.first) + sqr(p.second.second)});
	printf("%.10lf\n", sqrt(ans));
	return 0;
}