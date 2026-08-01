#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 3e5 + 5;

char s[N];
int n;
char ch;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%s", &n, s);
		ch = s[0], s[0] = 0;
		scanf("%s", s + 1);
		bool flag = true;
		for(int i = 1; i < n; i++) flag &= (s[i] == ch);
		if(flag && s[n] == ch) puts("0");
		else if(flag && s[n] != ch) printf("1\n%d\n", n - 1);
		else if(!flag && s[n] == ch) printf("1\n%d\n", n);
		else {
			bool ok = false;
			for(int i = 2; i < n && !ok; i++) {
				flag = true;
				for(int j = i; j <= n; j += i) flag &= (s[j] == ch);
				if(flag) printf("1\n%d\n", i), ok = true;
			}
			if(!ok) printf("2\n%d %d\n", n, n - 1);
		}
	}
	return 0;
}