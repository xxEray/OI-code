#include <bits/stdc++.h>

const int N = 30000 + 5;

int n, Q;

int fa[N], w[N], end[N];
int find(int x) {
	if(x == fa[x]) return x;
	int t = find(fa[x]);
	w[x] += w[fa[x]], fa[x] = t;
	return t;
}

int main() {
	scanf("%d", &Q);
	n = 30000;
	for(int i = 1; i <= n; i++) fa[i] = i, w[i] = 0, end[i] = i;
	while(Q--) {
		char s[3]; int i, j;
		scanf("%s%d%d", s, &i, &j);
		if(s[0] == 'M') {
			i = find(i), j = find(j);
			if(i == j) continue;
			fa[i] = end[j], end[j] = end[i], w[i] = 1;
		} else if(s[0] == 'C') {
			if(find(i) != find(j)) printf("-1\n");
			else printf("%d\n", std::max(0, std::abs(w[i] - w[j]) - 1));
		}
	}
	return 0;
}