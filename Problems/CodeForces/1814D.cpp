#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 3000 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
LL K;
struct Node { LL k, b; } a[N];
LL b[N];

int tin[N];
int cnt[N][4005], tmp[4005];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%lld", &n, &K);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i].k);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i].b);
		for(int i = 1; i <= n; i++) b[i] = a[i].k * a[i].b;
		std::sort(b + 1, b + n + 1);
		int tot = 0;
		for(int i = 1; i <= 2000; i++) tin[i] = 0;
		for(int i = 1; i <= n; i++) tin[a[i].k]++;
		for(int i = 1; i <= n; i++) for(int j = 0; j <= 4000; j++) cnt[i][j] = 0;
		for(int i = K + 1; i <= 2000; i++) tot += (bool)tin[i];
		for(int i = 1; i <= n; i++)
			for(int j = K + 1; j <= 2000; j++) if(tin[j]) {
				LL v = a[i].k * a[i].b;
				v = v / j * j;
				cnt[i][a[i].k * a[i].b - v + 2000]++;
				v -= j;
				if(v >= a[i].k * a[i].b - 2000) cnt[i][a[i].k * a[i].b - v + 2000]++;
				v -= j;
				if(v >= a[i].k * a[i].b - 2000) cnt[i][a[i].k * a[i].b - v + 2000]++;
				v = a[i].k * a[i].b / j * j + j;
				cnt[i][a[i].k * a[i].b - v + 2000]++;
				v += j;
				if(v <= a[i].k * a[i].b + 2000) cnt[i][a[i].k * a[i].b - v + 2000]++;
			}
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j <= 4000; j++) tmp[j] = cnt[i][j];
			int sum = 0;
			for(int j = 0; j <= 4000; j++) {
				if(j - K - 1 >= 0) sum -= tmp[j - K - 1];
				sum += tmp[j];
				cnt[i][j] = (sum == tot);
			}
		}
		int ans = 0;
		for(int i = 1; i <= n; i++)
			for(int j = 0; j <= 2000; j++) {
				LL v = a[i].k * a[i].b - j;
				if(!cnt[i][a[i].k * a[i].b - v + 2000]) continue;
				if(v <= 0) continue;
				ans = std::max(ans, (int)(std::upper_bound(b + 1, b + n + 1, v + K) - std::lower_bound(b + 1, b + n + 1, v)));
				// printf("l = %lld, ans = %d\n", v, ans);
			}
		printf("%d\n", n - ans);
	}
	return 0;
} /*
1
1
13 3
7 5 7 8 9 8 8 3 9 8 7 1 6
3 10 1 6 3 5 1 6 5 4 4 2 4
*/