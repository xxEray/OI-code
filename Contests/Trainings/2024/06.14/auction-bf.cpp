#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, Q;
int a[N];

std::bitset<N> bs;

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%1d", &a[i]);
	while(n >= 1 && a[n] == 0) n--;
	bs[n] = 1, bs[n + 1] = 1;
	printf("bs[%d]: ", n); for(int j = 1; j <= n; j++) printf("%d", (int)bs[j]); puts(""); 
	for(int i = n - 1; i >= 1; i--) {
		if(a[i]) {
			bs = ~bs;
			bs[i] = 1;
		} else {
			bs &= bs >> 1;
		}
		bs[i - 1] = 0, bs[n + 1] = 1;
		printf("bs[%d]: ", i); for(int j = 1; j <= n; j++) printf("%d", (int)bs[j]); puts(""); 
	}
	// printf("bs: "); for(int j = 1; j <= n; j++) printf("%d", (int)bs[j]); puts(""); 
	while(Q--) {
		int k;
		scanf("%d", &k);
		printf("%d\n", (int)bs[std::min(k, n)]);
	}
	return 0;
} /*
5 5
01010
1
2
3
4
5
*/