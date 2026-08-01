#include <cstdio>
#include <algorithm>

const int N = 15 + 3;
const int M = 225 + 5;
const int S = (1 << 15) + 5;

char s[M][M];
int n, m;

int f[N][S][2];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	return 0;
}