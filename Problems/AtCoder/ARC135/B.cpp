#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 3e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

LL a[N], b[N], c[N];
int n;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n - 1; i++) c[i + 3] = a[i + 1] - a[i];
	for(int i = 4; i <= n + 2; i++) c[i] += c[i - 3];
	// for(int i = 1; i <= n + 2; i++) printf("%lld ", c[i]); puts("");
	LL mn1 = LLINF, mn2 = LLINF, mn3 = LLINF;
	for(int i = 1; i <= n + 2; i += 3) mn1 = std::min(mn1, c[i]);
	for(int i = 2; i <= n + 2; i += 3) mn2 = std::min(mn2, c[i]);
	for(int i = 3; i <= n + 2; i += 3) mn3 = std::min(mn3, c[i]);
	mn1 = -mn1, mn2 = -mn2, mn3 = -mn3;
	if(mn1 + mn2 + mn3 > a[1]) { puts("No"); return 0; }
	LL add1 = mn1, add2 = mn2, add3 = a[1] - mn1 - mn2;
	b[1] = add1, b[2] = add2, b[3] = add3;
	for(int i = 4; i <= n + 2; i += 3) b[i] = c[i] + add1;
	for(int i = 5; i <= n + 2; i += 3) b[i] = c[i] + add2;
	for(int i = 6; i <= n + 2; i += 3) b[i] = c[i] + add3;
	puts("Yes");
	for(int i = 1; i <= n + 2; i++) printf("%lld ", b[i]);
	return 0;
} /*
5
6 9 6 6 5

0 4 2 3  1 2 2
0 0 0 3 -3 0 2
*/