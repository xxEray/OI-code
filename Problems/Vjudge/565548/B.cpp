#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, m, K;
std::vector<int> to[N];

int d[N];

std::vector<int> ans;
std::set<int> st, prest;

bool linked[N];

int main() {
	// freopen("graph.in", "r", stdin);
	// freopen("graph.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &K);
	int copyK = K;
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); to[u].push_back(v), d[v]++; }
	for(int i = 1; i <= n; i++) if(!d[i]) st.insert(i);
	while(!st.empty() || !prest.empty()) {
		if(st.empty()) st.insert(*prest.rbegin()), prest.erase(--prest.end());
		int u = *st.begin();
		if(st.size() >= 2 && K) {
			linked[u] = true;
			st.erase(st.begin()), prest.insert(u);
			K--;
		} else if(K && !prest.empty() && *prest.rbegin() > u) {
			linked[u] = true;
			st.erase(st.begin()), prest.insert(u);
			st.insert(*prest.rbegin()), prest.erase(--prest.end());
			K--;
		} else {
			st.erase(st.begin()), ans.push_back(u);
			for(int v : to[u]) if(d[v]) {
				d[v]--;
				if(!d[v]) st.insert(v);
			}
		}
	}
	// printf("ans.size() = %d\n", (int)ans.size());
	assert((int)ans.size() == n);
	for(int x : ans) printf("%d ", x);
	printf("\n%d\n", copyK - K);
	for(int i = 1; i < n; i++) if(linked[ans[i]]) printf("%d %d\n", ans[i - 1], ans[i]);
	return 0;
} /*
5 3 1
2 1
3 4
4 5
*/