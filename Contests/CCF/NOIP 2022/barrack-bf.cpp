#include <bits/stdc++.h>
#include <atcoder/dsu>

int n, m;
std::vector<std::pair<int, int>> e;

int main() {
	// freopen("D:/Useless/Temp/barrack/barrack2.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int u, v; scanf("%d%d", &u, &v); e.push_back({u, v}); }
	int ans = 0;
	for(int s = 1; s < (1 << n); s++) for(int t = 0; t < (1 << m); t++) {
		bool flag = true;
		for(int cut = 0; cut < m; cut++) {
			atcoder::dsu dsu(n + 1);
			for(int i = 0; i < m; i++) if((t >> i & 1) || i != cut) dsu.merge(e[i].first, e[i].second);
			int last = 0;
			for(int i = 1; i <= n; i++) if(s >> (i - 1) & 1) {
				if(last) flag &= dsu.same(last, i);
				else last = i;
			}
		}
		if(flag) {
			ans++;
			// printf("s=%d t=%d\n", s, t);
		}
	}
	printf("%d\n", ans);
	return 0;
}