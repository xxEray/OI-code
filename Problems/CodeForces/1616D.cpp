#include <cstdio>
#include <algorithm>
using std::min;
using std::max;

const int N = 5e4 + 5;
const int INF = 0x3f3f3f3f;

int a[N];
int least, n;

int l[N], f[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		scanf("%d", &least);
		for(int i = 0; i <= n; i++) f[i] = INF, l[i] = 0;
		for(int i = 1; i <= n; i++) a[i] -= least;
		for(int i = 1; i <= n; i++) {
			int sum = a[i];
			for(int j = i + 1; j <= min(i + 2, n); j++) {
				sum += a[j];
				if(sum < 0) l[j] = max(l[j], i); // , printf("catch %d %d\n", i, j);
			}
		}
		for(int i = 1; i <= n; i++) l[i] = max(l[i], l[i - 1]); // , printf("l[%d] = %d\n", i, l[i]);
		f[0] = 0;
		for(int i = 1; i <= n; i++)
			if(i > 1 && l[i - 1] == l[i - 2]) f[i] = f[i - 1];
			else {
				for(int j = l[i - 1]; j < i; j++)
					f[i] = min(f[i], f[j] + 1);
			}
		// for(int i = 1; i <= n; i++) printf("f[%d] = %d\n", i, f[i]);
		int ans = INF;
		for(int i = l[n]; i <= n; i++) ans = min(ans, f[i]);
		printf("%d\n", n - ans);
	}
	return 0;
} /*
4
5
1 2 3 4 5
2
10
2 4 2 4 2 4 2 4 2 4
3
3
-10 -5 -10
-8
3
9 9 -3
5
*/