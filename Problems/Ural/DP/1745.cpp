#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1000 + 5;
const int LEN = 10000 + 5;

struct Node { int bl, br, len, id; } a[N];
int n;

bool operator<(const Node &a, const Node &b) {
	if(a.bl == 0) return b.bl == 0 ? false : true;
	if(a.br == 0) return b.br == 0 ? false : false;
	if(a.br - a.bl > 0 && b.br - b.bl <= 0) return true;
	if(a.br - a.bl <= 0 && b.br - b.bl > 0) return false;
	if(a.br - a.bl > 0) return a.bl < b.bl;
	if(a.br - a.bl <= 0) return a.br > b.br;
	printf("Error! compare between (%d, %d) and (%d, %d) fail!\n", a.bl, a.br, b.bl, b.br);
	exit(1);
}

char s[LEN];

int f[N][LEN], g[N][LEN];
int pre[N][LEN];

void print(int i, int j) {
	if(i == 0) return;
	if(pre[i][j] == 1) print(i - 1, j);
	else if(pre[i][j] == 2) print(i - 1, j - a[i].bl + a[i].br), printf("%d ", a[i].id);
	else printf("Error! pre[%d][%d] = 0", i, j), exit(1);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%s", s);
		int l = 0, r = 0, len = strlen(s);
		for(int i = 0; i < len; i++)
			if(s[i] == '(') l++;
			else if(s[i] == ')') {
				if(l > 0) l--;
				else r++;
			}
		a[i].bl = r, a[i].br = l, a[i].len = len, a[i].id = i;
	}
	std::sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) {
		putchar('{');
		for(int j = 1; j <= a[i].bl; j++) putchar(')');
		for(int j = 1; j <= a[i].br; j++) putchar('(');
		putchar('}');
		putchar(i == n ? '\n' : ' ');
	}
	f[0][0] = 0, g[0][0] = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= 10000; j++)
			if(j - a[i].bl + a[i].br < 0 ||
				f[i - 1][j] > f[i - 1][j - a[i].bl + a[i].br] + a[i].len) {
				f[i][j] = f[i - 1][j];
				g[i][j] = g[i - 1][j];
				pre[i][j] = 1;
			} else {
				f[i][j] = f[i - 1][j - a[i].bl + a[i].br] + a[i].len;
				g[i][j] = g[i - 1][j - a[i].bl + a[i].br] + 1;
				pre[i][j] = 2;
			}
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= 6; j++)
			// if(f[i][j])
				printf("f[%d][%d] = {%d, %d}\n", i, j, f[i][j], g[i][j]);
	printf("%d %d\n", f[n][0], g[n][0]);
	print(n, 0);
	return 0;
}