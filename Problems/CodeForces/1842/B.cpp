#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, X;
int a[N], b[N], c[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &X);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
		for(int i = 1; i <= n; i++) scanf("%d", &c[i]);
		int va = 0, vb = 0, vc = 0;
		for(int i = 1; i <= n; i++)
			if(((va | a[i]) & X) == (va | a[i])) va |= a[i];
			else break;
		for(int i = 1; i <= n; i++)
			if(((vb | b[i]) & X) == (vb | b[i])) vb |= b[i];
			else break;
		for(int i = 1; i <= n; i++)
			if(((vc | c[i]) & X) == (vc | c[i])) vc |= c[i];
			else break;
		puts((va | vb | vc) == X ? "Yes" : "No");
	}
	return 0;
}