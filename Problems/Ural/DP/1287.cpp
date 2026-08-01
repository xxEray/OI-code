#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1400 + 5;

char s[N][N];
int n;

int f1[N][N], f2[N][N], f3[N][N], f4[N][N];

int getans(char c) {
	memset(f1, 0, sizeof(f1));
	memset(f1, 0, sizeof(f2));
	memset(f1, 0, sizeof(f3));
	memset(f1, 0, sizeof(f4));
	int ret = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) {
			f1[i][j] = (s[i][j] == c ? f1[i][j - 1] + 1 : 0), ret = std::max(ret, f1[i][j]);
			f2[i][j] = (s[i][j] == c ? f2[i - 1][j] + 1 : 0), ret = std::max(ret, f2[i][j]);
			f3[i][j] = (s[i][j] == c ? f3[i - 1][j - 1] + 1 : 0), ret = std::max(ret, f3[i][j]);
			f4[i][j] = (s[i][j] == c ? f4[i - 1][j + 1] + 1 : 0), ret = std::max(ret, f4[i][j]);
		}
	return ret;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	int ans_s = getans('s'), ans_S = getans('S');
	if(ans_s == ans_S) putchar('?');
	else if(ans_s < ans_S) putchar('S');
	else putchar('s');
	printf("\n%d", std::max(ans_s, ans_S));
	return 0;
}