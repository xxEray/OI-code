#include <cstdio>
#include <algorithm>

const int N = 1000 + 5;

char s[N];
int n, m;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%s", &n, &m, s + 1);
		bool flag = true;
		for(int i = 1; i <= n; i++) flag &= s[i] == s[n - i + 1];
		if(m == 0 || flag) puts("1");
		else puts("2");
	}
	return 0;
}