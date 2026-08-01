#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e5 + 5;

int n, w;
LL a[N];

LL b[N];
int tmp[100];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &w);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), b[i] = (1LL << (w + 1)) - 1;
		LL ans = 0;
		for(int k = w; k >= 0; k--) {
			for(int j = 0; j <= w + 1; j++) tmp[j] = 0;
			for(int i = 1; i <= n; i++) if(b[i] & ~(a[i] >> k)) tmp[w + 1 - __builtin_ctzll(b[i] & ~(a[i] >> k))]++;
			for(int j = 0; j <= w; j++) tmp[j + 1] += tmp[j] >> 1, tmp[j] &= 1;
			if(tmp[w + 1]) {
				for(int i = 1; i <= n; i++) b[i] &= ~(a[i] >> k);
			} else {
				ans |= (1LL << k);
			}
			// printf("k = %d: ", k); for(int i = 1; i <= n; i++) printf("%lld ", b[i]); puts("");
		}
		printf("%lld\n", ans);
	}
	return 0;
} /*
3
3 4
9 10 12
4 3
7 7 7 7
7 3
5 2 0 1 3 1 4
*/