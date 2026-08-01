#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>

const int N = 2e5 + 5;

int n;
std::vector<int> sons[N], origin, seq;
std::multiset<int> st;

bool check(int x) {
	int m = origin.size();
	st.clear();
	for(int v : origin) st.insert(v);
	for(int i = n; i >= n - (x - m) + 1; i--) {
		assert(!st.empty());
		int v = *st.rbegin();
		st.erase(std::prev(st.end()));
		st.insert(v - 1);
	}
	seq.clear();
	seq.push_back(0);
	while(!st.empty()) seq.push_back(*st.begin()), st.erase(st.begin());
	m = (int)seq.size() - 1;
	int ret = 0;
	for(int i = 1; i <= m; i++)
		ret = std::max(ret, seq[i] - 1 + m - i + 1);
	return ret <= x;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i <= n; i++) sons[i].clear();
		for(int i = 2; i <= n; i++) { int x; scanf("%d", &x); sons[x].push_back(i); }
		origin.clear();
		origin.push_back(1); // vertex 1
		for(int i = 1; i <= n; i++) if(!sons[i].empty()) origin.push_back(sons[i].size());
		std::sort(origin.begin(), origin.end());
		// for(int v : origin) printf("%d ", v);
		int l = 1, r = n;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(check(mid)) r = mid;
			else l = mid + 1;
		}
		// printf("\t\t\t%d\n", l);
		printf("%d\n", l);
	}
	return 0;
} /*
5
6
1 1 1 1 1
*/