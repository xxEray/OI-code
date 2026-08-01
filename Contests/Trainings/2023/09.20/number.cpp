#include <bits/stdc++.h>

typedef long long LL;

const int N = 20 + 3;

int n, K, Top;
int a[N];
LL mod;

namespace Solve_Case1 {
	void main() {
		printf("%lld\n", K * a[1] % mod);
	}
}

int main() {
#ifndef DEBUG
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
#endif
	scanf("%d%lld%d%d", &n, &mod, &K, &Top);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	if(Top == 1 && n == 1) Solve_Case1::main();
	return 0;
}