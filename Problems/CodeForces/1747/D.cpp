#include <cstdio>
#include <algorithm>
#include <map>
#include <set>

const int N = 2e5 + 5;

int a[N];
int n, Q;

int sum[N], pre[N];
int nxt[N], prv[N];

std::map<int, std::set<int>> mp[2];

int calc(int l, int r) {
	if((r - l + 1) & 1) {
		if(pre[r] == pre[l - 1]) return 1;
		else return 3;
	} else {
		if(pre[l - 1] != pre[r]) return 3;
		const auto &st = mp[!(r & 1)][pre[r]];
		auto it = st.upper_bound(l - 1);
		if(it != st.end() && *it <= r) return 2;
		else return 3;
	}
}

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), pre[i] = pre[i - 1] ^ a[i];
	prv[0] = 0, nxt[n + 1] = n + 1;
	for(int i = 1; i <= n; i++) prv[i] = (a[i] == 0 ? prv[i - 1] : i);
	for(int i = n; i >= 1; i--) nxt[i] = (a[i] == 0 ? nxt[i + 1] : i);
	for(int i = 1; i <= n; i++) mp[i & 1][pre[i]].insert(i);
	while(Q--) {
		int l0, r0;
		scanf("%d%d", &l0, &r0);
		int l = nxt[l0], r = prv[r0];
		if(l > r) { puts("0"); continue; }
		int ans = calc(l, r);
		if(l0 <= l - 1) ans = std::min(ans, calc(l - 1, r));
		if(r0 >= r + 1) ans = std::min(ans, calc(l, r + 1));
		if(l0 <= l - 1 && r0 >= r + 1) ans = std::min(ans, calc(l - 1, r + 1));
		printf("%d\n", ans == 3 ? -1 : ans);
	}
	return 0;
}