#include <bits/stdc++.h>

const int N = 100 + 5;

int n;
int a[N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	bool flag = true;
	for(int i = 1; i <= n; i++) if(a[i] % 2 == 0) flag &= (a[i] % 3 == 0 || a[i] % 5 == 0);
	puts(flag ? "APPROVED" : "DENIED");
	return 0;
}