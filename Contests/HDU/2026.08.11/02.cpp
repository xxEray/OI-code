// auto input
#include <bits/stdc++.h>

const int N = 3e6 + 5;
const int INF = 0x3f3f3f3f;

const int mask[2][2] = {{1, 2}, {4, 8}};

int n;
char a[N];

int f[N][2][16];

void chkmin(int &x, int y) { if(x > y) x = y; }

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s", a + 1);
		n = strlen(a + 1);
		for(int i = 0; i <= n; i++) memset(f[i], 0x3f, sizeof(f[i]));
		for(int i = 1; i <= n; i++) {
			chkmin(f[i][a[i] - '0'][0], 1);
			for(int s = 0; s < 16; s++) {
				chkmin(f[i][0][s], f[i - 1][0][s]), chkmin(f[i][1][s], f[i - 1][1][s]);
				chkmin(f[i][a[i] - '0'][s | mask[0][a[i] - '0']], f[i - 1][0][s] + 1);
				chkmin(f[i][a[i] - '0'][s | mask[1][a[i] - '0']], f[i - 1][1][s] + 1);
			}
			// for(int s = 0; s < 16; s++) printf("f[%d][][%d] = {%d, %d}\n", i, s, f[i][0][s], f[i][1][s]);
		}
		int ansmsk = 0;
		for(int i = 1; i < n; i++) ansmsk |= mask[a[i] - '0'][a[i + 1] - '0'];
		printf("%d\n", std::min(f[n][0][ansmsk], f[n][1][ansmsk]));
	}
	return 0;
} /*
2
1010100
00011101011010
*/