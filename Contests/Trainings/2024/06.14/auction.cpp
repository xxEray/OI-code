#include <bits/stdc++.h>

const int N = 1e6 + 5;
const int INF = 0x3f3f3f3f;

int n, Q;
int a[N];

std::set<std::pair<int, int>> st;
std::set<std::pair<int, int>> qg, qs;

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%1d", &a[i]);
	while(n >= 1 && a[n] == 0) n--;
	int type = 1, lv = 0, rv = 0;
	st.emplace(n, n), qs.emplace(0, n);
	for(int i = n - 1; i >= 1; i--) {
		if(a[i]) {
			type = !type;
			if(type) {
				if(st.begin()->first + lv == i + 1) {
					auto val = *st.begin();
					qs.erase({val.second - val.first, val.first});
					st.erase(st.begin());
					st.emplace(i - lv, val.second);
					qs.emplace(val.second - (i - lv), i - lv);
				} else {
					auto val = *st.begin();
					st.emplace(i - lv, i - rv);
					qs.emplace((i - rv) - (i - lv), i - lv);
					qg.emplace(val.first - (i - rv), i - lv);
				}
			}
		} else {
			if(type) {
				if(st.rbegin()->second + rv == n) {
					auto val = *st.rbegin();
					qs.erase({val.second - val.first, val.first});
					st.erase(--st.end());
					st.emplace(val.first, val.second + 1);
					qs.emplace(val.second + 1 - val.first, val.first);
				}
				rv--;
				while(!qs.empty() && qs.begin()->first + rv - lv == -1) {
					int lp = qs.begin()->second;
					qs.erase(qs.begin());
					auto md = st.lower_bound({lp, 0});
					if(md != st.begin()) {
						auto l = std::prev(md);
						qg.erase(qg.lower_bound({md->first - l->second, l->first}));
					}
					if(std::next(md) != st.end()) {
						auto r = std::next(md);
						qg.erase(qg.lower_bound({r->first - md->second, md->first}));
					}
					if(std::next(md) != st.end() && md != st.begin()) {
						auto l = std::prev(md);
						auto r = std::next(md);
						qg.emplace(r->first - l->second, l->first);
					}
					st.erase(md);
				}
			} else {
				lv--;
				if(st.begin()->first + lv == i - 1) {
					auto val = *st.begin();
					qs.erase({val.second - val.first, val.first});
					st.erase(st.begin());
					st.emplace(i - lv, val.second + 1);
					qs.emplace(val.second + 1 - (i - lv), i - lv);
				} else if(st.begin()->first + lv > i) {
					auto val = *st.begin();
					st.emplace(i - lv, i - rv);
					qs.emplace((i - rv) - (i - lv), i - lv);
					qg.emplace(val.first - (i - rv), i - lv);
				}
				while(!qg.empty() && qg.begin()->first + lv - rv == 1) {
					int l = qg.begin()->second;
					qg.erase(qg.begin());
					auto it = st.upper_bound({l, INF});
					it--;
					l = it->first;
					qs.erase({it->second - it->first, it->first});
					st.erase(it);
					it = st.lower_bound({l, 0});
					auto val = *it;
					qs.erase({it->second - it->first, it->first});
					st.erase(it);
					st.emplace(l, val.second);
					qs.emplace(val.second - l, l);
				}
			}
		}
	}
	if(n == 0) type = 0;
	while(Q--) {
		int k;
		scanf("%d", &k);
		k = std::min(k, n);
		auto it = st.upper_bound({k - lv, INF});
		if(it != st.begin() && std::prev(it)->first + lv <= k && k <= std::prev(it)->second + rv) printf("%d\n", type);
		else printf("%d\n", !type);
	}
	return 0;
}