#include <cstdio>
#include <algorithm>

const int N = 4e5 + 5;

int cnt[N];
int n;

int main() {
		scanf("%d", &n);
		for(int i = 1; i < 4 * n; i++) { int x; scanf("%d", &x); cnt[x]++; }
		for(int i = 1; i <= n; i++) if(cnt[i] < 4) printf("%d\n", i);
	return 0;
}