#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int a[N];
int n;

// 0:UU  1:DD  2:UD
int f[N][3][4];
int belong[N];

void updt(int &f, int &last, int nf, int nl, bool cmp) { if(f != nf && (f > nf) == cmp) f = nf, last = nl; }

void getans(int i, int j, int k) {
	belong[i] = k + 1;
	if(i == 1) return;
	else if(f[i][j][k + 2] == 1) getans(i - 1, j, k);
	else if(f[i][j][k + 2] == 2) getans(i - 1, j, !k);
	else exit(1);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	// 0
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= 1; j++)
			f[i][0][j] = INF;
	f[1][0][0] = f[1][0][1] = -INF;
	for(int i = 2; i <= n; i++)
		for(int j = 0; j <= 1; j++) {
			if(a[i - 1] < a[i]) updt(f[i][0][j], f[i][0][j + 2], f[i - 1][0][j], 1, 1);
			if(f[i - 1][0][!j] < a[i]) updt(f[i][0][j], f[i][0][j + 2], a[i - 1], 2, 1);
		}
	if(f[n][0][0] < INF) getans(n, 0, 0);
	else if(f[n][0][1] < INF) getans(n, 0, 1);
	// 1
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= 1; j++)
			f[i][1][j] = -INF;
	f[1][1][0] = f[1][1][1] = INF;
	for(int i = 2; i <= n; i++)
		for(int j = 0; j <= 1; j++) {
			if(a[i - 1] > a[i]) updt(f[i][1][j], f[i][1][j + 2], f[i - 1][1][j], 1, 0);
			if(f[i - 1][1][!j] > a[i]) updt(f[i][1][j], f[i][1][j + 2], a[i - 1], 2, 0);
		}
	if(f[n][1][0] > -INF) getans(n, 1, 0);
	else if(f[n][1][1] > -INF) getans(n, 1, 1);
	// 2: 0-min 1-max
	for(int i = 0; i <= n; i++) {
		f[i][2][0] = -INF;
		f[i][2][1] = INF;
	}
	f[1][2][0] = INF, f[1][2][1] = -INF;
	for(int i = 2; i <= n; i++) {
		if(a[i - 1] < a[i]) updt(f[i][2][0], f[i][2][2], f[i - 1][2][0], 1, 0);
		if(f[i - 1][2][1] < a[i]) updt(f[i][2][0], f[i][2][2], a[i - 1], 2, 0);
		if(a[i - 1] > a[i]) updt(f[i][2][1], f[i][2][3], f[i - 1][2][1], 1, 1);
		if(f[i - 1][2][0] > a[i]) updt(f[i][2][1], f[i][2][3], a[i - 1], 2, 1);
	}
	// for(int i = 1; i <= n; i++)
	// 	printf("f[%d] = {%d, %d}\n", i, f[i][2][0], f[i][2][1]);
	if(f[n][2][0] > -INF) getans(n, 2, 0);
	else if(f[n][2][1] < INF) getans(n, 2, 1);
	//
	if(belong[1] == 0) puts("Fail");
	else {
		int cnt1 = 0, cnt2 = 0;
		for(int i = 1; i <= n; i++)
			if(belong[i] == 1) cnt1++;
			else cnt2++;
		if(cnt1 == n) cnt2 = 1, cnt1 = n - 1, belong[1] = 2;
		if(cnt2 == n) cnt1 = 1, cnt2 = n - 1, belong[1] = 1;
		printf("%d %d\n", cnt1, cnt2);
		for(int i = 1; i <= n; i++) if(belong[i] == 1) printf("%d ", a[i]);
		puts("");
		for(int i = 1; i <= n; i++) if(belong[i] == 2) printf("%d ", a[i]);
	}
	return 0;
} /*
6
4 6 2 1 5 3
*/