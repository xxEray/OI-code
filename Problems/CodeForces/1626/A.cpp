#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 52 + 5;

char s[N];
int n;

int cnt[300];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		for(int i = 'a'; i <= 'z'; i++) cnt[i] = 0;
		for(int i = 1; i <= n; i++) cnt[s[i]]++;
		for(int i = 'a'; i <= 'z'; i++) if(cnt[i] == 2) putchar(i);
		for(int i = 'a'; i <= 'z'; i++) if(cnt[i] == 1) putchar(i);
		for(int i = 'a'; i <= 'z'; i++) if(cnt[i] == 2) putchar(i);
		puts("");
	}
	return 0;
}