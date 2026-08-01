#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;
char s[N];

int out[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%s", &n, s + 1);
		int sum = 0, now = 1, cnt[3] = {0, 0, 0};
		for(int i = 1; i <= n; i++) {
			sum += (s[i] == '(' ? 1 : -1);
			if(sum > 0) now = 1;
			if(sum < 0) now = 2;
			out[i] = now, cnt[now]++;
		}
		if(sum) puts("-1");
		else if(!cnt[1] || !cnt[2]) {
			puts("1");
			for(int i = 1; i <= n; i++) printf("1 ");
			puts("");
		} else {
			puts("2");
			for(int i = 1; i <= n; i++) printf("%d ", out[i]);
			puts("");
		}
	}
	return 0;
}