#include <cstdio>
#include <algorithm>

const int N = 60000 + 5;
const int SQRTN = 244 + 5;
const int INF = 0x3f3f3f3f;

int n;

int f[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) f[i] = INF;
	f[0] = 0;
	for(int i = 1; i <= 245; i++)
		for(int j = i * i; j <= n; j++)
			f[j] = std::min(f[j], f[j - i * i] + 1);
	printf("%d\n", f[n]);
	return 0;
}