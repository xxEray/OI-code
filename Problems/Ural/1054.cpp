#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 31 + 4;

int a[N];
int n;

bool flg = true;
int dfs(int mx, int frm, int to, int tmp) {
	if(mx == 0) return 0;
	// a[mx] must be either frm or to
	if(a[mx] == tmp) { flg = false; return 0; }
	else if(a[mx] == frm) return dfs(mx - 1, frm, tmp, to);
	else return (1 << (mx - 1)) + dfs(mx - 1, tmp, to, frm);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int ret = dfs(n, 1, 2, 3);
	if(flg) printf("%d\n", ret);
	else puts("-1");
	return 0;
} /*
3
1 1 1
*/