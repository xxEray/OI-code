#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1e3 + 5;

char a[N][N];
int n;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%s", a[i] + 1);
	bool flag = true;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
		if(i == j) flag &= a[i][j] == '-';
		else if(a[i][j] == 'W') flag &= a[j][i] == 'L';
		else if(a[i][j] == 'L') flag &= a[j][i] == 'W';
		else if(a[i][j] == 'D') flag &= a[j][i] == 'D';
	puts(flag ? "correct" : "incorrect");
	return 0;
}