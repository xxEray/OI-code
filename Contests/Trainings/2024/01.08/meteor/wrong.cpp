#include <bits/stdc++.h>

typedef long long LL;

int main() {
	int n;
	scanf("%d", &n);
	LL ans = (LL)n * n * n * n;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			for(int k = 0; k < n; k++)
				ans -= ((i ^ j ^ k) < n);
	printf("%lld\n", ans);
	return 0;
}