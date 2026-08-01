#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 5.1e6 + 5;

int n;
char s[N];

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	int i = 1, j, k;
	int ans = 0;
	while(i <= n) {
		j = i + 1, k = i;
		while(j <= n && s[j] >= s[k]) {
			if(s[j] == s[k]) k++;
			else k = i;
			j++;
		}
		while(i <= k) ans ^= i + j - k - 1, i += j - k;
	}
	printf("%d\n", ans);
	return 0;
}