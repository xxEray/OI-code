#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 14;

char s[N];
int a[N];
int n, m;

int main() {
	scanf("%s%d", s + 1, &m);
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++) a[i] = s[i] - 'a' + 1;
	std::sort(a + 1, a + n + 1);
	for(int i = 1; i < m; i++) std::next_permutation(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) putchar(a[i] + 'a' - 1);
	puts("");
	return 0;
}