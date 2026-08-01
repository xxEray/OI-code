#include <cstdio>
#include <algorithm>

const int N = 3e5 + 5;

int c[N];
int n;

int a[N], b[N], la, lb;

#define find(arr, x) (std::upper_bound(arr + 1, arr + l##arr + 1, (x)) - arr)

bool memf[N][2], memg[N][2];

int g(int x, int y);
int f(int x, int y) {
	// if(memf[x][y]) return memf[x][y];
	if(x == la && a[la] >= b[lb]) return memf[x][y] = 1;
	if(x > la) return 2;
	return memf[x][y] = std::min(f(x + 1, y) ^ 1, g(find(b, a[x]), y) ^ 1);
}
int g(int x, int y) {
	// if(memg[x][y]) return memg[x][y];
	if(x == lb && b[lb] >= a[la]) return memg[x][y] = 1;
	if(x > lb) return 2;
	return memg[x][y] = std::min(g(x + 1, y) ^ 1, f(find(a, b[x]), y) ^ 1);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &c[i]);
	a[++la] = c[1];
	for(int i = 2; i <= n; i++)
		if(c[i] > c[i - 1]) a[++la] = c[i];
		else break;
	b[++lb] = c[n];
	for(int i = n - 1; i >= 1; i--)
		if(c[i] > c[i + 1]) b[++lb] = c[i];
		else break;
	if(f(1, 0) == 1 || g(1, 1) == 1) puts("Alice");
	else puts("Bob");
	// for(int i = 1; i <= la; i++) printf("f(%d) = %d, %d\n", i, memf[i][0], memf[i][1]);
	// for(int i = 1; i <= lb; i++) printf("g(%d) = %d, %d\n", i, memg[i][0], memg[i][1]);
	return 0;
} /*
9
1 2 5 6 9 8 7 4 3
*/