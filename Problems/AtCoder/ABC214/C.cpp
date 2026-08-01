#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 4e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

LL s[N], t[N];
int n;

LL ans[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &s[i]), s[i + n] = s[i];
	for(int i = 1; i <= n; i++) scanf("%lld", &t[i]), t[i + n] = t[i];
	for(int i = 1; i <= n * 2; i++) ans[i] = t[i];
	for(int i = 2; i <= n * 2; i++) ans[i] = std::min(ans[i], ans[i - 1] + s[i - 1]);
	for(int i = 1; i <= n; i++) printf("%lld\n", std::min(ans[i], ans[i + n]));
	return 0;
} /*
3
4 1 1
3 10 1

*/