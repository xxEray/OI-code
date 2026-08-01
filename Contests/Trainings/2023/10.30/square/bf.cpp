#include <bits/stdc++.h>

typedef long long LL;

const int N = 5000 + 5;

int n;
bool flag[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		memset(flag, 0, sizeof(flag));
		scanf("%d", &n);
		for(int i = 1; (LL)(i * i - 1) / 2 <= n; i++) {
			for(int j = 1; j <= n; j++) if((LL)i * i - j > j && (LL)i * i - j <= n) flag[j] = true;
		}
		LL ans = 0;
		for(int i = 1; i <= n; i++) if(!flag[i]) ans += i;
		printf("%lld\n", ans);
	}
	return 0;
}