#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int n, c;
int a[N], b[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = n; i >= 1; i--) a[i] = a[i] ^ a[i - 1];
		int c = 0;
		for(int i = 1; i <= n; i++) if(a[i]) c++, a[c] = a[i], b[c] = i;
		n = c;

	}
	return 0;
} /*
x x x x x x x x x x x x
[             ]
*/