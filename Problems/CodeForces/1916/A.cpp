#include <bits/stdc++.h>

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int n, K, prod = 1, flag = true;
		scanf("%d%d", &n, &K);
		for(int i = 1; i <= n; i++) {
			int x;
			scanf("%d", &x);
			prod *= x;
			if(2023 % prod) flag = false, prod = 1;
		}
		if(!flag) puts("NO");
		else {
			puts("YES");
			printf("%d ", 2023 / prod);
			K--;
			while(K--) printf("1 ");
			puts("");
		}
	}
	return 0;
}