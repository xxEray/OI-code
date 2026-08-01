#include <bits/stdc++.h>

const int N = 1.1e7 + 5;

int n;
char s[N << 1];

int f[N << 1];

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 2 * n; i >= 2; i -= 2) s[i] = s[i >> 1];
	for(int i = 2 * n + 1; i >= 1; i -= 2) s[i] = '#';
	for(int i = 1, k = 0; i <= 2 * n + 1; i++) {
		int j = i;
		if(k + f[k] - 1 >= i) j = std::min(k + f[k] - 1, i + f[2 * k - i] - 1);
		while(j < 2 * n + 1 && s[j + 1] == s[2 * i - j - 1]) j++;
		f[i] = j - i + 1;
		if(i + f[i] >= k + f[k]) k = i;
	}
	// printf("s = %s\n", s + 1);
	// for(int i = 1; i <= 2 * n + 1; i++) printf("f[%d] = %d\n", i, f[i]);
	int ans = 0;
	for(int i = 1; i <= 2 * n + 1; i++) ans = std::max(ans, (2 * f[i] - 1) / 2);
	printf("%d\n", ans);
	return 0;
}