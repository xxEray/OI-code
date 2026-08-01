#include <cstdio>
#include <algorithm>

const int N = 100 + 5;
const int MAXA = 200 + 5;
const int INF = 0x3f3f3f3f;

int a[N];
int n;

bool prime[N * MAXA];
int reach[N][N * MAXA], last[N][N * MAXA], digit[N][N * MAXA];

void print(int i, int x) {
	if(x == 0) return;
	print(i - 1, last[i][x]), printf("%d ", digit[i][x]);
}

int main() {
	int T; scanf("%d", &T);
	for(int i = 2; i <= 20000; i++) prime[i] = true;
	for(int i = 2; i <= 20000; i++)
		for(int j = 2; j * j <= i; j++)
			if(i % j == 0) prime[i] = false;
	while(T--) {
		scanf("%d", &n);
		int mx = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), mx += a[i];
		for(int i = 0; i <= n; i++) for(int j = 0; j <= mx; j++) reach[i][j] = (j == 0 ? 0 : -INF), last[i][j] = digit[i][j] = 0;
		for(int i = 1; i <= n; i++) {
			for(int j = mx; j >= a[i]; j--)
				if(reach[j] < reach[j - a[i]] + 1)
					reach[i][j] = reach[i - 1][j - a[i]] + 1, last[i][j] = j - a[i], digit[i][j] = i;
		}
		int ansi = 0, ansind = 0;
		for(int i = 1; i <= n; i++) for(int j = 2; j <= mx; j++) if(!prime[j] && reach[i][j] > reach[ansi][ansind]) ansi = i, ansind = j;
		// for(int i = 1; i <= mx; i++) printf("last[%d] = %d, digit = %d\n", i, last[i], digit[i]);
		printf("%d\n", reach[ansi][ansind]);
		print(ansi, ansind);
		puts("");
	}
	return 0;
} /*
4
3
8 1 2
4
6 9 4 2
9
1 2 3 4 5 6 7 8 9
3
200 199 198

*/