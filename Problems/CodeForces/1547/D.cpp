#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 2e5 + 5;

int a[N], b[N];
int n;

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = 0;
		for(int i = 0; i <= 30; i++) {
			bool flag = 0;
			for(int j = 1; j <= n; j++) {
				if(flag == 0 && (a[j] & (1 << i))) flag = 1;
				if(j > 1 && flag && !(a[j] & (1 << i))) b[j] |= 1 << i;
			}
		}
		for(int i = 1; i <= n; i++) printf("%d ", b[i]);
		puts("");
	}
	return 0;
}