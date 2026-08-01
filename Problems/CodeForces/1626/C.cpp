#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 100 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

LL a[N], b[N];
int n;

LL f[N];

LL sum(LL x) { return x * (x + 1) / 2; }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		memset(f, 0x3f, sizeof(f));
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
		f[0] = 0;
		for(int i = 1; i <= n; i++) {
			LL len = 0;
			for(int j = i; j >= 1; j--) {
				len = std::max(len, b[j] + (a[i] - a[j]));
				if(a[i] - len >= a[j - 1]) f[i] = std::min(f[i], f[j - 1] + sum(len));
			}
		}
		// for(int i = 1; i <= n; i++) printf("f[%d] = %lld\n", i, f[i]);
		printf("%lld\n", f[n]);
	}
	return 0;
} /*
3
1
6
4
2
4 5
2 2
3
5 7 9
2 1 2

*/