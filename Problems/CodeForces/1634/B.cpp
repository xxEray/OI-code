#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 1e5 + 5;

LL a[N];
int n; LL A, B;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%lld%lld", &n, &A, &B);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		LL ret = A;
		for(int i = 1; i <= n; i++) ret ^= a[i];
		if((ret & 1) == (B & 1)) puts("Alice");
		else puts("Bob");
	}
	return 0;
}