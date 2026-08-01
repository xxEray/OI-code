#include <cstdio>
#include <algorithm>
#include <set>

const int N = 2e5 + 5;

int n, m, Q;

int sm[N], bg[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		if(u > v) std::swap(u, v);
		bg[u]++, sm[v]++;
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) ans += (bg[i] == 0);
	scanf("%d", &Q);
	while(Q--) {
		int type, u, v;
		scanf("%d", &type);
		if(type == 1) {
			scanf("%d%d", &u, &v);
			if(u > v) std::swap(u, v);
			ans -= !bg[u]++;
			sm[v]++;
		} else if(type == 2) {
			scanf("%d%d", &u, &v);
			if(u > v) std::swap(u, v);
			ans += !--bg[u];
			sm[v]++;
		} else printf("%d\n", ans);
	}
	return 0;
}