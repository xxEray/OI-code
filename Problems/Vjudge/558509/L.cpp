#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;
int a[N], pos[N];

int b[N], c[N];

int f[N];

void solve() {
	for(int i = 1; i <= n; i++) b[i] = c[i] = 0, pos[a[i]] = i;
	std::set<int> st;
	for(int i = 1; i <= n; i++) {
		auto it = st.lower_bound(pos[i]);
		b[pos[i]] = (it == st.begin() ? 0 : *--it);
		st.insert(pos[i]);
	}
	st.clear();
	for(int i = n; i >= 1; i--) {
		auto it = st.lower_bound(pos[i]);
		c[pos[i]] = (it == st.end() ? 0 : *it);
		st.insert(pos[i]);
	}
	// for(int i = 1; i <= n; i++) printf("%d: b=%d, c=%d\n", i, b[i], c[i]);
	std::set<std::pair<int, int>> st2;
	for(int i = 1; i <= n; i++) {
		if(b[pos[i]]) st2.insert({b[pos[i]], pos[i]});
		if(!c[pos[i]]) continue;
		auto it = st2.lower_bound({c[pos[i]], 0});
		if(it != st2.end()) f[pos[i]] = std::min(f[pos[i]], it->second - 1);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) f[i] = n;
	solve();
	for(int i = 1; i <= n; i++) a[i] = n + 1 - a[i];
	solve();
	// for(int i = 1; i <= n; i++) printf("%d: f=%d\n", i, f[i]);
	int mn = n;
	long long ans = 0;
	for(int i = n; i >= 1; i--) mn = std::min(mn, f[i]), ans += std::max(mn - i + 1, 0);
	printf("%lld\n", ans);
	return 0;
}