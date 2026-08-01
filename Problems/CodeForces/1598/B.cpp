#include <cstdio>
#include <algorithm>
#include <bitset>

const int N = 1000 + 5;

int a[N][10];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= 5; j++)
				scanf("%1d", &a[i][j]);
		bool ok = false;
		for(int i = 1; i <= 5; i++)
			for(int j = 1; j <= 5; j++) {
				if(i == j) continue;
				int cnti = 0, cntj = 0, cntij = 0;
				for(int k = 1; k <= n; k++)
					cnti += (a[k][i] && !a[k][j]), cntj += (a[k][j] && !a[k][i]), cntij += (a[k][i] && a[k][j]);
				if(cnti + cntj + cntij < n) continue;
				if(cnti + cntij >= n / 2 && cntj + cntij >= n / 2) ok = true;
			}
		puts(ok ? "YES" : "NO");
	}
	return 0;
}