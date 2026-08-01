#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 1e16;

int n, fbdn;
struct Node { int type, v, cost; } a[N];

LL tag[N];
std::map<int, LL> f[N];
std::multiset<LL> st[N];

int main() {
	scanf("%d%d", &n, &fbdn);
	std::vector<int> stk;
	for(int i = 1; i <= n; i++) {
		char tmp[5];
		scanf("%s", tmp);
		if(!strcmp(tmp, "set")) a[i].type = 0, scanf("%d%d", &a[i].v, &a[i].cost);
		else if(!strcmp(tmp, "if")) a[i].type = 1, scanf("%d", &a[i].v), stk.push_back(i);
		else if(!strcmp(tmp, "end")) a[i].type = 2, a[i].v = stk.back(), stk.pop_back();
	}
	assert(stk.empty());
	tag[0] = LLINF, f[0][0] = -LLINF, st[0].insert(f[0][0]);
	for(int i = 1; i <= n; i++) {
		if(a[i].type == 0) {
			tag[i] = tag[i - 1], f[i - 1].swap(f[i]);
			tag[i] += a[i].cost;
			if(a[i].v == fbdn) {
				st[i].swap(st[i - 1]);
			} else {
				LL old = (f[i].count(a[i].v) ? f[i][a[i].v] : -(LL)4e18);
				f[i][a[i].v] = std::min(f[i][a[i].v], *st[i - 1].begin() + tag[i - 1] - tag[i]);
				st[i].swap(st[i - 1]);
				if(old > -(LL)4e18) st[i].erase(st[i].find(old));
				st[i].insert(f[i][a[i].v]);
				if(f[i].count(fbdn)) st[i].erase(st[i].find(f[i][fbdn]));
				f[i][fbdn] -= a[i].cost;
				st[i].insert(f[i][fbdn]);
			}
		} else if(a[i].type == 1) {
			tag[i] = LLINF;
			if(a[i].v != fbdn) {
				f[i][a[i].v] = (f[i - 1].count(a[i].v) ? f[i - 1][a[i].v] : 0) + tag[i - 1] - tag[i];
				st[i].insert(f[i][a[i].v]);
				if(f[i - 1].count(a[i].v)) st[i - 1].erase(st[i - 1].find(f[i - 1][a[i].v]));
				f[i - 1][a[i].v] += LLINF;
				st[i - 1].insert(f[i - 1][a[i].v]);
			}
		} else {
			f[i].swap(f[a[i].v - 1]), st[i].swap(st[a[i].v - 1]), tag[i] = tag[a[i].v - 1];
			if(f[i - 1].size() > f[i].size()) f[i - 1].swap(f[i]), st[i - 1].swap(st[i]), std::swap(tag[i - 1], tag[i]);
			for(auto &p : f[i - 1]) {
				if(f[i].count(p.first)) st[i].erase(st[i].find(f[i][p.first]));
				f[i][p.first] = std::min(f[i][p.first], p.second + tag[i - 1] - tag[i]);
				st[i].insert(f[i][p.first]);
			}
			f[i - 1].clear(), st[i - 1].clear();
		}
		assert(st[i].size() == f[i].size());
		// printf("%d(%lld): ", i, tag[i]);
		// for(auto &p : f[i]) printf("(%d, %lld) ", p.first, p.second);
		// printf("| "); for(LL x : st[i]) printf("%lld ", x);`!
		// puts("");
	}
	LL ans = LLINF;
	for(auto &p : f[n]) ans = std::min(ans, tag[n] + p.second);
	printf("%lld\n", ans);
	return 0;
}