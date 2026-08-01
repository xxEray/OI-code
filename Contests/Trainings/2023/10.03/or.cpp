#include <bits/stdc++.h>

typedef long long LL;

int highbit(LL x) {
	for(int i = 63; i >= 0; i--) if(x >> i & 1) return i;
	return -1;
}

struct Node { LL l, r; };
std::vector<Node> vct;
void solve(LL l, LL r, LL base) {
	// printf("solve %lld %lld\n", l, r);
	if(!l && !r) { vct.push_back({base, base}); return; }
	int hl = highbit(l), hr = highbit(r);
	if(hl == hr) {
		LL common = l & ~((1LL << (highbit(l ^ r) + 1)) - 1);
		return solve(l ^ common, r ^ common, base | common);
	}
	vct.push_back({l | base, ((1LL << hr) - 1) | base});
	vct.push_back({l | (1LL << hr) | base, ((1LL << hr) - 1) | (1LL << hr) | base});
	solve(1LL << hr, r, base);
}

LL calc() {
	// for(auto &[l, r]: vct) printf("(%lld, %lld)\n", l, r);
	std::sort(vct.begin(), vct.end(), [&](Node x, Node y) { return x.l == y.l ? x.r > y.r : x.l < y.l; });
	int j = -1;
	for(int i = 0; i < (int)vct.size(); i++) if(!i || vct[i].r > vct[j].r) vct[++j] = vct[i];
	vct.erase(vct.begin() + j + 1, vct.end());
	std::sort(vct.begin(), vct.end(), [&](Node x, Node y) { return x.r < y.r; });
	LL ans = 0;
	for(int i = 0; i < (int)vct.size(); i++) ans += vct[i].r - std::max(i ? vct[i - 1].r : 0, vct[i].l - 1);
	return ans;
}

int main() {
#ifndef DEBUG
	freopen("or.in", "r", stdin);
	freopen("or.out", "w", stdout);
#endif
	LL l, r;
	scanf("%lld%lld", &l, &r);
	solve(l, r, 0);
	printf("%lld\n", calc());
	return 0;
}