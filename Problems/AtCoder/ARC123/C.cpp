#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 20 + 5;

char s[N];
int n;

int f[N][30][10];

void updt(int &a, int b) { if(a > b) a = b; }

int main() {
	int T;
	if(scanf("%d", &T) != 1) return 0;
	while(T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		for(int i = 1; i <= n; i++) s[i] -= '0';
		memset(f, 0x3f, sizeof(f));
		for(int i = 1; i <= 7; i++)
			for(int j = i; j <= 3 * i; j++)
				if(j % 10 == s[n])
					f[n][j / 10][i] = i;
		for(int i = n; i >= 2; i--)
			for(int j = 0; j <= 25; j++)
				for(int k = 0; k <= 7; k++)
					for(int k2 = 0; k2 <= k; k2++)
						for(int j2 = k2; j2 <= k2 * 3; j2++)
							if((j + j2) % 10 == s[i - 1])
								updt(f[i - 1][(j + j2) / 10][k2], f[i][j][k]);
		int ans = 0x3f3f3f3f;
		for(int i = 0; i <= 7; i++) ans = std::min(ans, f[1][0][i]);
		printf("%d\n", ans);
	}
	return 0;
} /*
1
456
*/