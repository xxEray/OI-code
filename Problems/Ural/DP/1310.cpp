#include <cstdio>
#include <algorithm>

#include "my/biginteger"

const int N = 100 + 5;

int n, m, base;
BigInteger kth;

BigInteger f[N][N];

#define MOD(x) (((x) % base + base) % base) // 兼容负数取模

int main() {
	scanf("%d%d%d", &n, &m, &base);
	std::cin >> kth;
	kth++;
	for(int i = 1; i <= m; i++) f[n][i % base]++;
	for(int i = n - 1; i >= 1; i--)
		for(int j = 0; j < base; j++)
			for(int k = 1; k <= m; k++)
				f[i][j] += f[i + 1][MOD(j - k)];
	// for(int i = 1; i <= n; i++)
	// 	for(int j = 0; j < base; j++)
	// 			printf("f[%d][%d] = %lld\n", i, j, f[i][j].to_ll());
	int mod = 0;
	BigInteger rest = kth;
	for(int i = 1; i < n; i++) {
		int j = 1;
		for(; j <= m; j++)
			if(f[i + 1][MOD(mod - j)] >= rest) break;
			else rest -= f[i + 1][MOD(mod - j)];
		printf("%d ", j);
		mod = MOD(mod - j);
	}
	int j = 1;
	for(; j <= m; j++) {
		if(j % base == mod) rest--;
		if(rest == 0) break;
	}
	printf("%d ", j);
	return 0;
}