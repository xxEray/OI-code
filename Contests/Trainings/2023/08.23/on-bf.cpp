#include <bits/stdc++.h>

typedef long long LL;

const int N = 60000 + 5;
const int MAXA = 40000 + 5;
const int MAXK = 40 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, K, coeficient;
LL a[N];

LL sum[N];

LL f1000[MAXK][1005];
int cnt[MAXA];

int main() {
	scanf("%d%d%d", &n, &K, &coeficient);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	LL base = std::accumulate(a + 1, a + n + 1, 0LL);
	base *= base;
	for(int i = 1; i <= n; i++) base -= a[i] * a[i];
	base /= 2;
	if(!coeficient) { printf("%lld\n", base); return 0; }
	for(int i = 1; i <= n; i++) sum[i] = sum[i - 1] + std::abs(a[i] - a[i - 1]) + (a[i] ^ a[i - 1]);
	if(n <= 1000) {
		memset(f1000, 0x3f, sizeof(f1000));
		f1000[0][0] = 0;
		for(int k = 1; k <= K; k++) for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) cnt[a[j]] = 0;
			LL s = 0;
			for(int j = i; j >= 1; j--) {
				s -= cnt[a[j]] * cnt[a[j]];
				cnt[a[j]]++;
				s += cnt[a[j]] * cnt[a[j]];
				f1000[k][i] = std::min(f1000[k][i], f1000[k - 1][j - 1] + (sum[i] - sum[j]) * s);
			}
		}
		for(int i = 1; i <= K; i++) for(int j = i; j <= n; j++) printf("f[%d][%d] = %lld\n", i, j, f1000[i][j]);
		printf("%lld\n", base + f1000[K][n]);
		return 0;
	}
	return 0;
}