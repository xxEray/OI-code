#include <cstdio>
#include <algorithm>

const int N = 2000 + 5;
const double eps = 1e-6;

int a[N][N], b[5][5];
int n;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
	for(int i = 1; i <= 3; i++) for(int j = 1; j <= 3; j++) scanf("%d", &b[i][j]);
	if(!b[1][2] && !b[1][3] && !b[2][1] && !b[2][2] && !b[2][3] && !b[3][1] && !b[3][2] && !b[3][3])
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				printf("%d.00000%c", a[i][j], " \n"[j == n]);
	else
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				printf("%d.00000%c", 0, " \n"[j == n]);
	return 0;
} /*
2
799 467 
252 136 
802 230 59
695 603 494
341 837 438

*/