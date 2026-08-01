#include <cstdio>
#include <algorithm>

const int N = 50 + 5;

char a[N], b[N];
int n, m;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%s%s", &n, &m, a + 1, b + 1);
		bool flag = true, fl = false;
		for(int i = 1; i <= m - 1; i++) flag &= a[n - i + 1] == b[m - i + 1];
		for(int i = 1; i <= n - m + 1; i++) fl |= a[i] == b[1];
		puts(flag && fl ? "Yes" : "No");
	}
	return 0;
}