#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N];

int l[N], k[N], r[N];

int go[21][N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		std::vector<int> q;
		for(int i = 1; i <= n; i++) {
			while(!q.empty() && a[q.back()] >= a[i]) q.pop_back();
			k[i] = (q.empty() ? 0 : q.back());
			q.push_back(i);
		}
		q.clear();
		for(int i = n; i >= 1; i--) {
			while(!q.empty() && a[q.back()] >= a[i]) q.pop_back();
			r[i] = (q.empty() ? n : q.back() - 1);
			q.push_back(i);
		}
		a[0] = INF;
		for(int j = 0; j <= 20; j++) for(int i = 0; i <= n; i++) go[j][i] = INF;
		for(int i = 0; i <= n; i++) go[0][i] = a[i];
		for(int j = 1; j <= 20; j++) for(int i = (1 << j); i <= n; i++) go[j][i] = std::max(go[j - 1][i], go[j - 1][i - (1 << (j - 1))]);
		// for(int j = 0; j <= 20; j++) for(int i = 0; i <= n; i++) printf("go[%d][%d] = %lld\n", j, i, go[j][i]);
		for(int i = 1; i <= n; i++) {
			int o = k[i];
			for(int j = 20; j >= 0; j--) if(go[j][o] <= a[i]) o -= (1 << j);
			l[i] = o + 1;
		}
		// for(int i = 1; i <= n; i++) printf("%d: l=%d, k=%d, r=%d\n", i, l[i], k[i], r[i]);
		LL ans = 0;
		for(int i = 1; i <= n; i++) ans += (LL)i * (i - 1) / 2;
		for(int i = 1; i <= n; i++) if(k[i]) ans -= (LL)(k[i] - l[i] + 1) * (r[i] - i + 1);
		printf("%lld\n", ans);
	}
	return 0;
}