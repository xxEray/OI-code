#include <bits/stdc++.h>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
int a[N], b[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
		std::set<int> st;
		std::map<int, int> cnt;
		std::map<int, std::vector<int>> mp;
		for(int i = 1; i <= n; i++) st.insert(a[i]), cnt[a[i]]++;
		st.insert(INF);
		for(int i = 1; i <= m; i++) mp[*st.lower_bound(b[i])].push_back(b[i]);
		for(auto &[_, v] : mp) std::sort(v.begin(), v.end(), std::greater<>());
		for(int x : mp[INF]) printf("%d ", x);
		for(int i = 1; i <= n; i++) {
			cnt[a[i]]--, printf("%d ", a[i]);
			if(!cnt[a[i]]) for(int x : mp[a[i]]) printf("%d ", x);
		}
		puts("");
	}
	return 0;
}