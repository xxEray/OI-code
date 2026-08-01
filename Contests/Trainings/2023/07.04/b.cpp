#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e5 + 5;

int n, K;
int a[N];

std::vector<int> ans[2];

int vis[25 * N];

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int pre = 0;
	if(n > 25) {
		for(int i = n; i >= K + 1; i--)
			if(pre + a[i] > 200000) pre -= a[i], ans[0].push_back(i);
			else pre += a[i], ans[1].push_back(i);
	} else K = n;
	int U = (1 << K) - 1;
	int s1 = 0, s2 = 0;
	for(int s = 0; s <= U; s++) {
		int sum = 0;
		for(int i = 1; i <= K; i++) if(s >> (i - 1) & 1) sum += a[i];
		if(sum >= pre && vis[sum - pre]) { s1 = s, s2 = vis[sum - pre]; break; }
		vis[sum] = s;
	}
	if(!s1) { puts("-1"); return 0; }
	int t = s1 & s2;
	s1 &= ~t, s2 &= ~t;
	for(int i = 1; i <= K; i++) if(s1 >> (i - 1) & 1) ans[0].push_back(i);
	for(int i = 1; i <= K; i++) if(s2 >> (i - 1) & 1) ans[1].push_back(i);
	printf("%d ", (int)ans[0].size()); for(int x : ans[0]) printf("%d ", x); puts("");
	printf("%d ", (int)ans[1].size()); for(int x : ans[1]) printf("%d ", x); puts("");
	return 0;
} /*
9 7
8 1 10 22 75 121 4 73 335
*/