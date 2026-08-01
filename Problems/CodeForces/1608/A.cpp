#include <cstdio>
#include <algorithm>

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		for(int i = 2; i <= n + 1; i++) printf("%d ", i);
		puts("");
	}
	return 0;
}