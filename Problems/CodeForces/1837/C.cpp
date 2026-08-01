#include <bits/stdc++.h>

const int N = 3e5 + 5;

int n;
char s[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		s[n + 1] = '1';
		bool flag = false;
		for(int i = n + 1; i >= 1; i--)
			if(s[i] == '1') flag = true;
			else if(s[i] == '0') flag = false;
			else s[i] = (flag ? '1' : '0');
		for(int i = 1; i <= n; i++) putchar(s[i]);
		puts("");
	}
	return 0;
}