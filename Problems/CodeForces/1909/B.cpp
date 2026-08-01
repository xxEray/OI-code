#include <bits/stdc++.h>

typedef long long LL;

const int N = 100 + 5;

int n;
LL a[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		LL k = 1;
		while(true) {
			LL v = a[1] % k;
			bool flag = false;
			for(int i = 1; i <= n; i++) flag |= (a[i] % k != v);
			if(flag) break;
			k <<= 1;
		}
		printf("%lld\n", k);
	}
	return 0;
}