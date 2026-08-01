#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 5;

int n, m;
LL K;
LL u[N], v[N];
int x[N], y[N];

LL u2[N];

int main() {
	scanf("%d%lld%d", &n, &K, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &u[i]);
	for(int i = 1; i <= m; i++) scanf("%d", &y[i]);
	for(int i = 1; i <= m; i++) scanf("%d", &x[i]); // 没反，代码中认为 v[x[]] => u[y[]]
	for(int i = 1; i <= n; i++) scanf("%lld", &v[i]);
	for(int i = 1; i <= n; i++) u2[i] = v[i];
	for(int i = 1; i <= m; i++) u2[y[i]] += v[x[i]] * K;
	bool flag = true;
	for(int i = 1; i <= n; i++) flag &= u[i] == u2[i];
	if(flag) puts("Accepted");
	else {
		puts("Wrong, u2:");
		for(int i = 1; i <= n; i++) printf("%lld ", u2[i]);
		puts("");
		return 1;
	}
	return 0;
}