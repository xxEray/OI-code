#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1e4 + 5;

char s[N];
int n;

int cnt[N];

bool check() {
	for(int i = 1; i <= n; i++) if(cnt[i] != 1) return false;
	int inda = 0;
	for(int i = 1; i <= n; i++) if(s[i] == 'a') inda = i;
	for(int i = inda - 1; i >= 1; i--) if(s[i + 1] >= s[i]) return false;
	for(int i = inda + 1; i <= n; i++) if(s[i - 1] >= s[i]) return false;
	return true;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		for(int i = 1; i <= n; i++) cnt[i] = 0;
		for(int i = 1; i <= n; i++) cnt[s[i] - 'a' + 1]++;
		if(check()) puts("YES");
		else puts("NO");
	}
	return 0;
}