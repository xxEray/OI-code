#include <cstdio>
#include <algorithm>

const int N = 50 + 5;

int a[N];
int n, m;

int cnt[N];
char s[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= m; i++) s[i] = 'B', cnt[i] = 0;
		for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); cnt[std::min(x, m - x + 1)]++; }
		for(int i = 1; i <= m; i++)
			if(cnt[i] == 1) s[i] = 'A';
			else if(cnt[i] >= 2) s[i] = s[m - i + 1] = 'A';
		s[m + 1] = '\0';
		printf("%s\n", s + 1);
	}
	return 0;
}