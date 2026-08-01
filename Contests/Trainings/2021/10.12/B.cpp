#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e6 + 5;
const LL MOD = 1e9 + 7;

bool a[N];
int n, m;

int main() {
	scanf("%d%d", &n, &m);
	while(m--) { int x; scanf("%d", &x); a[x] = 1; }
	LL ans = 1, cnt = 1;
	for(int i = n; i >= 1; i--) (ans *= cnt) %= MOD, cnt += (a[i] ? -1 : 1);
	printf("%lld\n", ans);
	return 0;
}