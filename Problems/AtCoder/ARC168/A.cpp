#include <bits/stdc++.h>

const int N = 2.5e5 + 5;

int n;
char s[N];

int main() {
	scanf("%d%s", &n, s + 1);
	n--;
	long long ans = 0;
	for(int i = 1; i <= n; ) {
		if(s[i] == '<') { i++; continue; }
		int j = i;
		int cnt = 0;
		while(j <= n && s[j] == '>') cnt++, j++;
		ans += (long long)cnt * (cnt + 1) / 2;
		i = j;
	}
	printf("%lld\n", ans);
	return 0;
}