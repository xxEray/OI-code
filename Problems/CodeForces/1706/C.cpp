#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

LL a[N];
int n;

LL f[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for(int i = 1; i <= n; i++) f[i] = LLINF;
		for(int i = 2; i <= n; i++) {
			f[i] = std::min(f[i], f[i - 2] + std::max(std::max(a[i - 1], a[i + 1]) + 1 - a[i], 0LL));
			if(i & 1) f[i] = std::min(f[i], f[i - 3] + std::max(std::max(a[i - 1], a[i + 1]) + 1 - a[i], 0LL));
		}
		printf("%lld\n", (n & 1) ? f[n - 1] : std::min(f[n - 2], f[n - 1]));
	}
	return 0;
}