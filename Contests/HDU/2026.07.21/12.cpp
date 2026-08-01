#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;
const int MX = 2e9;

int n, m;
LL K;
int x[N], y[N];

LL temp[N];
LL u[N], v[N], ucopy[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%lld%d", &n, &K, &m);
		for(int i = 1; i <= n; i++) v[i] = 0;
		for(int i = 1; i <= n; i++) scanf("%lld", &u[i]), ucopy[i] = u[i];
		for(int i = 1; i <= m; i++) scanf("%d", &y[i]);
		for(int i = 1; i <= m; i++) scanf("%d", &x[i]); // 没反，代码中认为 v[x[]] => u[y[]]
		LL nowK;
		for(nowK = 1; nowK <= 2000000000; nowK *= K) {
			bool flag = true;
			for(int i = 1; i <= n; i++) flag &= (u[i] == 0);
			if(flag) break;
			for(int i = 1; i <= n; i++) temp[i] = (u[i] % K + K) % K, v[i] += temp[i] * nowK;
			for(int i = 1; i <= m; i++) u[y[i]] -= K * temp[x[i]];
			for(int i = 1; i <= n; i++) u[i] -= temp[i], u[i] /= K;
				// if(u[i] >= 0) u[i] /= K;
				// else u[i] = (u[i] - K + 1) / K;
			// printf("nowK = %lld\n", nowK);
			// printf("u: "); for(int i = 1; i <= n; i++) printf("%lld ", u[i]); puts("");
			// printf("v: "); for(int i = 1; i <= n; i++) printf("%lld ", v[i]); puts("");
		}
		bool flag = true;
		// for(int i = 1; i <= n; i++) flag &= (u[i] == 0);
		// if(!flag) { puts("No Solution"); continue; }
		// for(int i = 1; i <= m; i++) if(u[x[i]] == -1) flag = false;
		// if(!flag) { puts("No Solution"); continue; }
		// for(int i = 1; i <= n; i++) if(u[i] == -1) v[i] -= nowK;
		for(int i = 1; i <= n; i++) {
			if(v[i] > 1000000000) v[i] -= nowK;
			if(v[i] < -1000000000) flag = false;
		}
		if(!flag) { puts("No Solution"); continue; }
		// printf("v: "); for(int i = 1; i <= n; i++) printf("%lld ", v[i]); puts("");
		for(int i = 1; i <= n; i++) u[i] = v[i];
		for(int i = 1; i <= m; i++) u[y[i]] += v[x[i]] * K;
		for(int i = 1; i <= n; i++) flag &= (u[i] == ucopy[i]);
		if(!flag) { puts("No Solution"); continue; }
		for(int i = 1; i <= n; i++) printf("%lld ", v[i]);
		puts("");
	}
	return 0;
}