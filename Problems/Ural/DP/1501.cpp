#include <cstdio>
#include <algorithm>

const int N = 1000 + 5;

int pre[N][2][2];
int n;

bool f[N][N];
int dppre[N][N];

inline int check(int x, int y) { return std::abs((pre[x][0][1] + pre[y][1][1]) - (pre[x][0][0] + pre[y][1][0])) <= 1; }

void print(int i, int j) {
	if(i == 0 && j == 0) return;
	if(dppre[i][j] == -1) print(i - 1, j), printf("1");
	else print(i, j - 1), printf("2");
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		char s[2];
		scanf("%1s", s);
		pre[i][0][0] = pre[i - 1][0][0], pre[i][0][1] = pre[i - 1][0][1];
		if(s[0] == '0') pre[i][0][0]++;
		else pre[i][0][1]++;
	}
	for(int i = 1; i <= n; i++) {
		char s[2];
		scanf("%1s", s);
		pre[i][1][0] = pre[i - 1][1][0], pre[i][1][1] = pre[i - 1][1][1];
		if(s[0] == '0') pre[i][1][0]++;
		else pre[i][1][1]++;
	}
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= n; j++) {
			if(!i && !j) { f[i][j] = true; continue; }
			if(!check(i, j)) { f[i][j] = false; continue; }
			if(check(i - 1, j) && f[i - 1][j]) { f[i][j] = true; dppre[i][j] = -1; }
			if(check(i, j - 1) && f[i][j - 1]) { f[i][j] = true; dppre[i][j] = 1; }
		}
	if(f[n][n] == false) { puts("Impossible"); return 0; }
	print(n, n);
	return 0;
}