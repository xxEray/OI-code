// warning off, sanitize on
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#ifdef DEBUG
#include "stl_printer.h"
#endif

typedef long long LL;

const int N = 1e5 + 5;

int n, K;
char s[N];

LL value(int x, int y) {
	auto div_upper = [](int p, int q) { return (p + q - 1) / q; };
	auto calc = [](int p) { return p <= 0 ? 0LL : 20LL * p + 5LL * p * (p + 1) / 2; };
	int p = (x - y) % (y + 1);
	LL ret = p * calc(div_upper(x - y, y + 1)) + (y + 1 - p) * calc((x - y) / (y + 1));
	// printf("value %d %d = %lld\n", x, y, ret);
	return ret;
}
struct Node {
	int cnt, split;
	LL profit() const { return value(cnt, split) - value(cnt, split + 1); }
};
struct cmp {
	bool operator()(const Node &x, const Node &y) const { return x.profit() < y.profit(); }
};

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%s", &n, &K, s + 1);
		std::vector<int> vct;
		int cnt = 0;
		for(int i = 1; i <= n; i++)
			if(s[i] == '0') cnt++;
			else {
				if(cnt) vct.emplace_back(cnt);
				cnt = 0;
			}
		if(cnt) vct.emplace_back(cnt);
		// printf("vct = %s\n", tostring(vct).c_str());
		std::priority_queue<Node, std::vector<Node>, cmp> q;
		LL ans = 0;
		for(int x : vct) q.push({x, 0}), ans += value(x, 0);
		while(!q.empty() && K--) {
			auto nd = q.top();
			// printf("nd = {%d, %d}\n", nd.cnt, nd.split);
			q.pop();
			ans -= nd.profit();
			nd.split++;
			if(nd.split < nd.cnt) q.emplace(nd);
		}
		printf("%lld\n", ans);
	}
	return 0;
}