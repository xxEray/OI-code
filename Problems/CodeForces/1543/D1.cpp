#include <cstdio>
#include <algorithm>
 
int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		int n, k;
		scanf("%d%d", &n, &k);
		int x = 0;
		for(int i = 0; i < n; i++) {
			printf("%d\n", i ^ x);
			fflush(stdout);
			int status;
			scanf("%d", &status);
			if(status == 0) x ^= i ^ x;
			else break;
		}
	}
	return 0;
}