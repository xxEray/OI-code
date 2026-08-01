#include <bits/stdc++.h>

const int N = 1 << 20 | 5;

char s[N];
bool vis[300];
int n;

int prv[N], nxt[N];

int main() {
#ifndef DEBUG
	std::freopen("string.in", "r", stdin);
	std::freopen("string.out", "w", stdout);
#endif
	int T;
	std::scanf("%d", &T);
	while(T--) {
		std::scanf("%s", s + 1);
		n = std::strlen(s + 1);
		int ret = 0;
		for(int i = 0; i < 300; i++) vis[i] = false;
		for(int i = 1; i <= n; i++) ret -= vis[s[i]] - (!vis[s[i]]), vis[s[i]] = !vis[s[i]], prv[i] = ret;
		ret = 0;
		for(int i = 0; i < 300; i++) vis[i] = false;
		for(int i = n; i >= 1; i--) ret -= vis[s[i]] - (vis[s[i]] = !vis[s[i]]), nxt[i] = ret;
		long long ans = 0;
		for(int i = 1; i <= n; i++)
			for(int j = i; j < n; j += i) {
				if(std::strncmp(s + 1, s + j - i + 1, i)) break;
				for(int k = 1; k < i; k++)
					if(prv[k] <= nxt[j + 1]) ans++;
			}
		std::printf("%lld\n", ans);
	}
	return 0;
} /*
5
kkkkkkkkkkkkkkkkkkkk
lllllllllllllrrlllrr
cccccccccccccxcxxxcc
ccccccccccccccaababa
ggggggggggggggbaabab
*/
