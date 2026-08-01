#include <bits/stdc++.h>

const int N = 2e6 + 5;

int n;
char s[N];

int f[N][2];

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++) s[i] -= '0';
	std::reverse(s + 1, s + n + 1);
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for(int i = 1; i <= 2 * n; i++) for(int j : {0, 1})
		for(int k1 = 0; k1 <= 9; k1++) {
			int k2 = k1 - j - s[i];
			if(0 <= k2 && k2 <= 9) f[i][0] = std::min(f[i][0], f[i - 1][j] + k1 + k2);
			k2 += 10;
			if(0 <= k2 && k2 <= 9) f[i][1] = std::min(f[i][1], f[i - 1][j] + k1 + k2);
		}
	printf("%d\n", f[2 * n][0]);
	return 0;
}