#include <bits/stdc++.h>

const int N = 1e6 + 5;

int n;
int a[N], b[N], c[N];

struct cmp { bool operator()(int x, int y) const { return a[x] == a[y] ? x < y : a[x] < a[y]; } };
std::set<int, cmp> st;

int main() {
	int T; scanf("%d", &T);
	bool type = false;
	while(T--) {
		if(type) {
			int m;
			scanf("%d", &m);
			while(m--) { int x, y; scanf("%d%d", &x, &y); c[x] = b[x] = a[x] = y; }
		} else {
			scanf("%d", &n);
			for(int i = 1; i <= n; i++) scanf("%d", &a[i]), c[i] = b[i] = a[i];
			type = true;
		}
		st.clear();
		for(int i = 1; i <= n; i++) st.emplace(i);
		while(st.size() > 1) {
			int u = *st.rbegin();
			st.erase(--st.end());
			int v = *st.begin();
			if(a[v] < b[v]) {
				for(int i = 1; i <= n; i++) std::swap(a[i], b[i]);
				for(int i = 1; i <= n; i++) if(i != v) b[i] = -1;
				break;
			}
			st.erase(st.begin());
			a[u] -= a[v];
			st.emplace(u);
		}
		// printf("st: "); for(int x : st) printf("%d ", x); puts("");
		st.clear();
		// printf("a: "); for(int i = 1; i <= n; i++) printf("%d ", a[i]); puts("");
		// printf("b: "); for(int i = 1; i <= n; i++) printf("%d ", b[i]); puts("");
		for(int i = 1; i <= n; i++) st.emplace(i);
		while(st.size() > 1) {
			int u = *st.rbegin();
			st.erase(--st.end());
			int v = *st.begin();
			st.erase(st.begin());
			if(a[u] - a[v] == b[u]) { st.emplace(u), st.emplace(v); break; }
			a[u] -= a[v];
			st.emplace(u);
		}
		printf("%d\n", (int)st.size());
		for(int i = 1; i <= n; i++) a[i] = b[i] = c[i];
	}
	return 0;
}