#include <cstdio>

typedef long long LL;

const int N = 1e4 + 5;
const int MOD = 1e9 + 9;

int n;

bool isprm[N];
LL f[N][11][11];

#define isprime(i, j, k) (isprm[(i) * 100 + (j) * 10 + (k)])

int main() {
	scanf("%d", &n);
	for(int i = 2; i <= 999; i++) isprm[i] = true;
	for(int i = 2; i <= 999; i++)
		if(isprm[i]) for(int j = i * 2; j <= 999; j += i) isprm[j] = false;
	for(int i = 2; i <= 99; i++) isprm[i] = false;
	for(int i = 1; i <= 9; i++)
		for(int j = 0; j <= 9; j++)
			for(int k = 0; k <= 9; k++)
				if(isprime(i, j, k)) f[3][j][k]++;
	for(int i = 4; i <= n; i++)
		for(int j = 0; j <= 9; j++)
			for(int k = 0; k <= 9; k++)
				for(int r = 0; r <= 9; r++)
					if(isprime(j, k, r))
						f[i][k][r] = (f[i][k][r] + f[i - 1][j][k]) % MOD;
	LL ans = 0;
	for(int i = 0; i <= 9; i++)
		for(int j = 0; j <= 9; j++)
			ans = (ans + f[n][i][j]) % MOD;
	printf("%lld\n", ans);
	return 0;
}