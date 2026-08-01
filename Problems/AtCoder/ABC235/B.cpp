#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int a[N];
int n;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) if(a[i + 1] <= a[i] || i == n) { printf("%d\n", a[i]); break; }
	return 0;
}