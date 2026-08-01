#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int a[N], b[N];
int n, m;

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= m; i++) scanf("%d", &a[i]);
		std::sort(a + 1, a + m + 1);
		for(int i = 0; i < m; i++) b[i] = a[i + 1] - a[i] - 1;
		b[m] = n - a[m];
		int sum = n - m;
		int id = 0, mx = b[0];
		for(int i = 1; i <= m; i++) if(b[i] >= mx) id = i, mx = b[i];
		puts((sum - mx >= mx || mx - (sum - mx) <= id) ? "YES" : "NO");
	}
	return 0;
}