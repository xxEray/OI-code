#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 50 + 5;

char s[N], t[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s%s", s, t);
		if(!strcmp(t, "a")) puts("1");
		else if(strstr(t, "a") != NULL) puts("-1");
		else printf("%lld\n", 1LL << strlen(s));
	}
	return 0;
}