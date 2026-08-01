#include <cstdio>

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		int odd = 0, even = 0;
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n * 2; i++) {
			int x;
			scanf("%d", &x);
			if(x & 1) odd++;
			else even++;
		}
		puts(odd == even ? "Yes" : "No");
	}
	return 0;
}