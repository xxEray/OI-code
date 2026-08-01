#include <bits/stdc++.h>

const int N = 5000 + 5;
const int INF = 0x3f3f3f3f;

int n;
char s[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%s", &n, s + 1);
		int cnt = 0;
		for(int i = 1; i <= n; i++)
			if(s[i] == '+') cnt++;
			else cnt--;
		printf("%d\n", std::abs(cnt));
	}
	return 0;
}