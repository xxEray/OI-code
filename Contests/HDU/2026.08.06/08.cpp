#include <bits/stdc++.h>

const int N = 1e7 + 5;

int n, K;
char s[N], t[N];

int cnt[30];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		memset(cnt, 0, sizeof(cnt));
		scanf("%d%d%s%s", &n, &K, s + 1, t + 1);
		for(int i = 1; i <= n; i++) cnt[s[i] - 'a']++;
		for(int i = 1; i <= n; i++) cnt[t[i] - 'a']--;
		bool flag = true;
		for(int i = 0; i < 26; i++) flag &= (cnt[i] == 0);
		if(!flag) { puts("No"); continue; }
		if(2 * K > n) {
			if(s[1] != t[1]) std::swap(s[1], s[n]);
			for(int i = 1; i <= n; i++) flag &= (s[i] == t[i]);
			puts(flag ? "Yes" : "No");
			continue;
		}
		for(int i = 2; i <= K - 1; i++) flag &= (s[i] == t[i]);
		for(int i = n - K + 2; i <= n - 1; i++) flag &= (s[i] == t[i]);
		if(!flag) { puts("No"); continue; }
		if(s[1] == t[1] && s[n] == t[n]) { puts("Yes"); continue; }
		if(s[n] == t[1] && s[1] == t[n]) { puts("Yes"); continue; }
		bool has[2] = {false, false};
		for(int i = K; i <= n - K + 1; i++) {
			if(!has[0] && s[i] == t[1]) has[0] = true;
			else if(!has[1] && s[i] == t[n]) has[1] = true;
		}
		if(has[0] && has[1]) puts("Yes");
		else puts("No");
	}
	return 0;
} /*
4
3 3
abc
cba
10 2
cutesafari
eutcasafir
3 1
aab
abb
10 3
safaricute
caieasuftr
*/