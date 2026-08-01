#include <bits/stdc++.h>

typedef unsigned long long ull;

const int N = 1000 + 5;

int n, Q;
int a[N];

int cnt[N];

ull f[2 * N], g[2 * N];

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	while(Q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		for(int i = l; i <= r; i++) cnt[a[i]]++;
		for(int i = 1000 - n; i <= 1000 + n; i++) f[i] = 0;
		f[1000] = 1;
		for(int i = 1; i <= n; i++) if(cnt[i]) {
			for(int j = 1000 - n; j <= 1000 + n; j++)
				g[j] = f[j] * (cnt[i] >= 64 ? (ull)-2 : (1ull << cnt[i]) - 2) + f[j - 1] + f[j + 1];
			std::swap(f, g);
		}
		printf("%llu\n", f[1000]);
		for(int i = l; i <= r; i++) cnt[a[i]]--;
	}
	return 0;
} /*
12 1
1 1 4 5 1 4 6 6 6 6 6 6
2 6

*/