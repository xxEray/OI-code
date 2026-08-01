#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

typedef long long LL;

const int N = 2e5 + 5;

int n;
struct Node { LL x, y; } a[N];

std::vector<std::pair<LL, LL>> ans;
std::multiset<std::pair<LL, LL>> st1, st2;

bool solve(LL r, LL c, LL s) {
	// printf("solve %d %d %lld\n", r, c, s);
	if(st1.empty()) return true;
	if(st1.size() == 1) return st1.begin()->first == r && st1.begin()->second == c;
	if(st1.rbegin()->first == r) {
		LL x = st1.rbegin()->first, y = st1.rbegin()->second;
		st1.erase(st1.find({x, y})), st2.erase(st2.find({y, x}));
		bool ret = solve(r, c - y, s - (LL)x * y);
		st1.insert({x, y}), st2.insert({y, x});
		return ret;
	} else if(st2.rbegin()->first == c) {
		LL x = st2.rbegin()->second, y = st2.rbegin()->first;
		st1.erase(st1.find({x, y})), st2.erase(st2.find({y, x}));
		bool ret = solve(r - x, c, s - (LL)x * y);
		st1.insert({x, y}), st2.insert({y, x});
		return ret;
	}
	return false;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		ans.clear();
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			a[i] = {x, y};
		}
		LL sum = 0;
		for(int i = 1; i <= n; i++) sum += (LL)a[i].x * a[i].y;
		st1.clear(), st2.clear();
		for(int i = 1; i <= n; i++) st1.insert({a[i].x, a[i].y}), st2.insert({a[i].y, a[i].x});
		if(sum % st1.rbegin()->first == 0) {
			LL x = st1.rbegin()->first, y = st1.rbegin()->second;
			st1.erase(st1.find({x, y})), st2.erase(st2.find({y, x}));
			if(solve(x, sum / x - y, sum - (LL)x * y)) ans.push_back({x, sum / x});
		}
		std::vector<std::pair<LL, LL>> out[2];
		st1.clear(), st2.clear();
		for(int i = 1; i <= n; i++) st1.insert({a[i].x, a[i].y}), st2.insert({a[i].y, a[i].x});
		if(sum % st2.rbegin()->first == 0) {
			LL x = st2.rbegin()->second, y = st2.rbegin()->first;
			st1.erase(st1.find({x, y})), st2.erase(st2.find({y, x}));
			if(solve(sum / y - x, y, sum - (LL)x * y)) ans.push_back({sum / y, y});
		}
		if(ans.size() == 2 && ans[0] == ans[1]) ans.pop_back();
		printf("%d\n", (int)ans.size());
		for(auto p : ans) printf("%lld %lld\n", p.first, p.second);
	}
	return 0;
} /*
4
3
1 2
3 5
1 3
3
1 1
1 1
1 1
1
10 10
4
3 2
5 5
2 2
8 7
*/