#include <bits/stdc++.h>

const int N = 100 + 5;

int n, m;
int a[N], b[N];
char s[N][N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(s[i][j] == 'o') b[i] += a[j];
	for(int i = 1; i <= n; i++) {
		std::vector<int> vct;
		for(int j = 1; j <= m; j++) if(s[i][j] == 'x') vct.push_back(a[j]);
		int mx = 0;
		for(int j = 1; j < i; j++) mx = std::max(mx, b[j]);
		for(int j = i + 1; j <= n; j++) mx = std::max(mx, b[j] + 1);
		std::sort(vct.begin(), vct.end(), std::greater<int>());
		int j = 0, sum = b[i];
		while(sum < mx) sum += vct[j], j++;
		printf("%d\n", j);
	}
	return 0;
}