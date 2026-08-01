#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, K;
int a[N];
int prv[N], nxt[N];

struct cmp { bool operator()(int x, int y) const { return a[x] == a[y] ? x < y : a[x] < a[y]; }; };

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &K);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		n--;
		for(int i = 1; i <= n; i++) a[i] = a[i + 1] - a[i];
		for(int i = 1; i <= n; i++) prv[i] = i - 1, nxt[i] = i + 1;
		prv[0] = 0, nxt[n + 1] = n + 1, nxt[0] = 1, prv[n + 1] = n;
		std::set<int, cmp> st;
		for(int i = 1; i <= n; i++) st.emplace(i);
		int ans = 0;
		while(K--) {
			int i = *st.begin();
			st.erase(st.begin());
			ans += a[i];
			if(prv[i] >= 1 && nxt[i] <= n) {
				a[i] = a[prv[i]] + a[nxt[i]] - a[i];
				st.erase(prv[i]), nxt[prv[prv[i]]] = i, prv[i] = prv[prv[i]];
				st.erase(nxt[i]), prv[nxt[nxt[i]]] = i, nxt[i] = nxt[nxt[i]];
				st.emplace(i);
			} else {
				if(prv[i] >= 1) st.erase(prv[i]), nxt[prv[prv[i]]] = nxt[i], prv[nxt[i]] = prv[prv[i]];
				if(nxt[i] <= n) st.erase(nxt[i]), prv[nxt[nxt[i]]] = prv[i], nxt[prv[i]] = nxt[nxt[i]];
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}