#include <cstdio>
#include <algorithm>
#include <iostream>
#include "biginteger"

const int N = 50 + 5;
const int S = 1000 + 5;

int n, s;

BigInteger f[N][S];

int main() {
	scanf("%d%d", &n, &s);
	if(s & 1) { puts("0"); return 0; }
	s /= 2;
	f[0][0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= s; j++)
			for(int k = 0; k <= std::min(9, j); k++)
				f[i][j] += f[i - 1][j - k];
	// for(int i = 0; i <= n; i++)
	// 	for(int j = 0; j <= s; j++)
	// 		printf("f[%d][%d] = %lld\n", i, j, f[i][j]);
	std::cout << f[n][s] * f[n][s];
	return 0;
}