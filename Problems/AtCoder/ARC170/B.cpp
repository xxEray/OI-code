#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n;
int a[N];

int last[13];
int nxt[N][13];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int j = 1; j <= 10; j++) nxt[n + 1][j] = nxt[n][j] = n + 1;
	for(int i = n - 1; i >= 1; i--) {
		for(int j = 1; j <= 10; j++) nxt[i][j] = nxt[i + 1][j];
		nxt[i][a[i + 1]] = i + 1;
	}
	LL ans = 0;
	int hisr = n + 1;
	for(int i = n; i >= 1; i--) {
		int r = n + 1;
		for(int j = -10; j <= 10; j++) if(1 <= a[i] + 2 * j && a[i] + 2 * j <= 10) r = std::min(r, nxt[nxt[i][a[i] + j]][a[i] + 2 * j]);
		hisr = std::min(hisr, r);
		ans += n - hisr + 1;
	}
	printf("%lld\n", ans);
	return 0;
}