#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2e5 + 5;

LL a[N];
int n; LL m;
int vis[N];
LL pre[N];

int main() {
	scanf("%d%lld", &n, &m);
	for(int i = 0; i < n; i++) scanf("%lld", &a[i]);
	LL sum = 0, cnt = 0;
	LL sz;
	while(cnt < m) {
		// printf("%lld ", sum);
		vis[sum % n] = cnt, pre[cnt] = sum;
		sum += a[sum % n];
		if(vis[sum % n]) {
			sz = cnt - vis[sum % n] + 1;
			break;
		}
		cnt++;
	}
	if(cnt == m) { printf("%lld\n", sum); return 0; }
	LL rest = pre[cnt - sz + 1];
	// printf("sum = %lld, sz = %lld, cnt = %lld, rest = %lld\n", sum, sz, cnt, rest);
	sum -= rest, m -= cnt - sz + 1;
	sum *= m / sz, m %= sz;
	sum += rest;
	while(m--) sum += a[sum % n];
	printf("%lld\n", sum);
	return 0;
} /*
5 30
1 3 2 4 5
*/