#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;
int a[N], b[N], p[N], q[N];

std::set<int> st;
std::vector<std::pair<int, int>> ans;

bool check(int i) { return p[i] != i && a[i] > b[p[i]] && a[p[i]] > b[p[p[i]]] && (b[p[p[i]]] < b[p[i]] || (b[p[p[i]]] == b[p[i]] && p[p[i]] > p[i])); }

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &p[i]), q[p[i]] = i;
	for(int i = 1; i <= n; i++) if(check(i)) st.insert(i);
	while(!st.empty()) {
		int i = *st.begin();
		st.erase(st.begin());
		int j = p[i];
		ans.push_back({i, j});
		std::swap(p[i], p[j]);
		q[p[i]] = i, q[p[j]] = j;
		// printf("swap(%d, %d)\n", i, j);
		if(st.count(j)) st.erase(j);
		if(check(i)) st.insert(i);
		if(check(q[i])) st.insert(q[i]);
	}
	for(int i = 1; i <= n; i++) if(p[i] != i) { puts("-1"); return 0; }
	printf("%d\n", (int)ans.size());
	for(const auto &[x, y] : ans) printf("%d %d\n", x, y);
	return 0;
}