#include <bits/stdc++.h>

const int N = 10 + 5;

int n;
int a[N];

int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) a[i] = i;
	do {
		bool flag = true;
		for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) flag &= ((gcd(i, j) == 1) == (gcd(a[i], a[j]) == 1));
		if(flag) {
			for(int i = 1; i <= n; i++) printf("%d ", a[i]);
			puts("");
		}
	} while(std::next_permutation(a + 1, a + n + 1));
	return 0;
}