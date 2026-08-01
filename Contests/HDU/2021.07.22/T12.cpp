#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1e5 + 5;

char s[N];

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%s", s);
		int n = strlen(s);
		for(int i = 0; i < n; i++)
			if(!strncmp(s + i, "114514", 6))
				{ puts("AAAAAA"); goto EndWhile; }
		puts("Abuchulaile");
		EndWhile: continue;
	}
	return 0;
}