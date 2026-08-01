#include <bits/stdc++.h>

const std::vector<std::array<int, 3>> permu = {{1, 6, 9}, {1, 9, 6}, {6, 1, 9}, {9, 6, 1}};

bool is_square(int x) {
	int y = round(sqrt(x));
	return y * y == x;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		for(int i = 0; i <= (n - 3) / 2; i++) {
			putchar('1');
			for(int _ = 1; _ <= i; _++) putchar('0');
			putchar('6');
			for(int _ = 1; _ <= i; _++) putchar('0');
			putchar('9');
			for(int _ = 1; _ <= n - 3 - 2 * i; _++) putchar('0');
			putchar(' ');
		}
		for(int i = 0; i <= (n - 3) / 2; i++) {
			putchar('9');
			for(int _ = 1; _ <= i; _++) putchar('0');
			putchar('6');
			for(int _ = 1; _ <= i; _++) putchar('0');
			putchar('1');
			for(int _ = 1; _ <= n - 3 - 2 * i; _++) putchar('0');
			putchar(' ');
		}
		if(n == 1) printf("1");
		else if(n == 3) printf("196");
		else {
			printf("61009");
			for(int _ = 1; _ <= n - 5; _++) putchar('0');
		}
		puts("");
	}
	return 0;
}