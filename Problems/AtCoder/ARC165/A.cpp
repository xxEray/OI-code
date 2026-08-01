#include <bits/stdc++.h>

const int N = 1e5 + 5;

bool isprm[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		bool flag = false;
		for(int i = 2; i * i <= n; i++) if(n % i == 0) {
			while(n % i == 0) n /= i;
			flag = (n == 1 ? false : true);
			break;
		}
		puts(flag ? "Yes" : "No");
	}
	return 0;
}