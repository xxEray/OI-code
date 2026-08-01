#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1e4 + 5;

char s[30];
int n;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		if(n == 2) { printf("%c\n", s[2]); continue; }
		char mn = '9';
		for(int i = 1; i <= n; i++) mn = std::min(mn, s[i]);
		printf("%c\n", mn);
	}
	return 0;
}