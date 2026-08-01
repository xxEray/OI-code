#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n;
char s[N], t[N];

int main() {
	scanf("%d%s", &n, s + 1);
	strcpy(t + 1, s + 1);
	for(int i = 1; i <= n; i++) {
		int ans = 0;
		strcpy(s + 1, t + 1);
		int now = i;
		while(1 <= now && now <= n) {
			ans++;
			if(s[now] == 'L') s[now] = 'R', now--;
			else s[now] = 'L', now++;
		}
		printf("%d ", ans);
	}
	puts("");
	return 0;
}
