#include <bits/stdc++.h>

const int N = 500 + 5;

int n;
char s[N];

int w[N][N];
int f[N][N];

int main() {
	srand(time(0));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) s[i] = ((i & 1) ? '(' : ')');
	puts(s + 1);
	for(int i = 1; i <= n; i++) {
		int sum = 0;
		for(int j = i; j <= n; j++) {
			sum += (s[j] == '(' ? 1 : -1);
			if(sum < 0) break;
			w[i][j] = (sum == 0);
		}
	}
	for(int len = 1; len <= n; len++)
		for(int i = 1; i + len - 1 <= n; i++) {
			int j = i + len - 1;
			w[i][j] += w[i + 1][j] + w[i][j - 1] - w[i + 1][j - 1];
		}
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= i; j++)
			for(int k = 0; k < i; k++)
				f[i][j] = std::min(f[i][j], f[k][j - 1] + w[k + 1][i]);
	for(int k = 1; k <= n; k++) if(f[n][k]) printf("K = %d, ans = %d\n", k, f[n][k]);
	return 0;
}