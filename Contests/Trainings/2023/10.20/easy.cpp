#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e6 + 5;

int n, K;
char s[N];

int main() {
#ifndef DEBUG
	freopen("easy.in", "r", stdin);
	freopen("easy.out", "w", stdout);
#endif
	scanf("%d%d%s", &n, &K, s + 1);
	LL sum = 0, cnt = 0, sum2 = 0;
	for(int i = 1; i <= 2 * n; i++)
		if(s[i] == 'B') cnt++;
		else sum += cnt;
	LL lower = n / K, upper = n / K + 1, cntu = n % K;
	sum2 += (LL)n * n;
	sum2 -= (K - cntu) * lower * lower + cntu * upper * upper;
	assert(sum2 % 2 == 0);
	printf("%lld\n", std::max(0LL, sum - sum2 / 2));
	return 0;
} /*
5 3
AABABABBAB
*/
