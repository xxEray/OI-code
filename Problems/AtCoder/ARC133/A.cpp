#include <cstdio>
#include <algorithm>

const int N = 2e5 + 5;

int a[N];
int n;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int x = a[n];
	for(int i = 1; i < n; i++) if(a[i] > a[i + 1]) { x = a[i]; break; }
	for(int i = 1; i <= n; i++) if(a[i] != x) printf("%d ", a[i]);
	return 0;
}