#include <cstdio>
#include <algorithm>

const int N = 500 + 5;

int a[N], pos[N];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), pos[a[i]] = i;
		int p1 = 0, p2 = 0;
		for(int i = 1; i <= n; i++) if(a[i] != i) { p1 = i, p2 = pos[i]; break; }
		if(p1 && p2) std::reverse(a + p1, a + p2 + 1);
		for(int i = 1; i <= n; i++) printf("%d ", a[i]);
		puts("");
	}
	return 0;
}