#include <cstdio>
#include <algorithm>

const int N = 100 + 5;
const int INF = 0x3f3f3f3f;

char s[N];
int n, A, B;

int f[N][N];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d%s", &n, &A, &B, s + 1);
		if(B >= 0) printf("%d\n", (A + B) * n);
		else {
			for(int i = 1; i <= n; i++)
				for(int j = i; j <= n; j++)
					f[i][j] = INF;
			for(int i = 1; i <= n; i++) f[i][i] = 1;
			for(int i = 1; i <= n; i++)
				for(int j = i; j <= n && s[i] == s[j]; j++)
					f[i][j] = 1;
			for(int len = 1; len <= n; len++)
				for(int i = 1; i + len - 1 <= n; i++) {
					int j = i + len - 1;
					for(int k = i; k < j; k++) {
						f[i][j] = std::min(f[i][j], f[i][k] + f[k + 1][j]);
						if(s[k] == s[j]) f[i][j] = std::min(f[i][j], f[i][k] + f[k + 1][j - 1]);
					}
				}
			// for(int i = 1; i <= n; i++)
			// 	for(int j = i + 1; j <= n; j++)
			// 		printf("f[%d][%d] = %d\n", i, j, f[i][j]);
			printf("%d\n", A * n + B * f[1][n]);
		}
	}
	return 0;
}