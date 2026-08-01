#include <bits/stdc++.h>

const int N = 50 + 5;

int n, m;
int a[N], b[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
		long long suma = 0, sumb = 0;
		for(int i = 1; i <= n; i++) suma += a[i];
		for(int i = 1; i <= m; i++) sumb += b[i];
		if(suma > sumb) puts("Tsondu");
		else if(suma < sumb) puts("Tenzing");
		else puts("Draw");
	}
	return 0;
}