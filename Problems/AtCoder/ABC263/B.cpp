#include <cstdio>
#include <algorithm>

const int N = 50 + 5;

int n;
int dep[N];

int main() {
	scanf("%d", &n);
	for(int i = 2; i <= n; i++) { int p; scanf("%d", &p); dep[i] = dep[p] + 1; }
	printf("%d\n", dep[n]);
	return 0;
}