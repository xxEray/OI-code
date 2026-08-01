#include <bits/stdc++.h>

const int N = 3e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
char s[N];

int main() {
	scanf("%d%s", &n, s + 1);
	int mn = INF, cnt = 0, flag = true;
	for(int i = 1; i <= n; i++) {
		if(s[i] == '0' && cnt) mn = std::min(mn, flag ? cnt : (cnt + 1) / 2), cnt = 0;
		else if(s[i] == '1') cnt++;
		if(s[i] == '0') flag = false;
	}
	if(cnt) mn = std::min(mn, cnt);
	if(mn == INF) { puts("0"); return 0; }
	// printf("mn = %d\n", mn);
	cnt = 0;
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		if(s[i] == '0' && cnt) ans += (cnt + (2 * mn - 1) - 1) / (2 * mn - 1), /* printf("cnt = %d\n", cnt),  */cnt = 0;
		else if(s[i] == '1') cnt++;
	}
	if(cnt) ans += (cnt + (2 * mn - 1) - 1) / (2 * mn - 1); // , printf("cnt = %d\n", cnt);
	printf("%d\n", ans);
	return 0;
}