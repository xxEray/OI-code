#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int n, L;
int a[N];

int main() {
	scanf("%d%d", &n, &L);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int sum = 0;
	for(int i = 1; i <= n; i++) {
		if(a[i] == 2 && L - sum <= 1) { puts("No"); return 0; }
		sum += a[i] + 1;
	}
	puts("Yes");
	return 0;
}