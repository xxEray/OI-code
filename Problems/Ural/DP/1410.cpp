#include <cstdio>
#include <algorithm>
#include <cstring>

typedef unsigned long long ull;

const int N = 1e4 + 5;
const int SIZE = 100 + 5;

int a[N];
int n;

int f[N];

char tmp[SIZE];

int main() {
	scanf("%*[^a-zA-Z]");
	for(n = 0; scanf("%[a-zA-Z]%*[^a-zA-Z]", tmp) == 1;) a[++n] = strlen(tmp);
	f[0] = 0, f[1] = a[1], f[2] = std::max(a[1], a[2]);
	for(int i = 3; i <= n; i++) f[i] = std::max(f[i - 1], std::max(f[i - 2], f[i - 3]) + a[i]);
	printf("%d\n", f[n]);
	return 0;
} /*

*/