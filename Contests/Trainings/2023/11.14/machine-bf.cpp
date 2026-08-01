#include <bits/stdc++.h>

const int N = 100 + 5;

int n;
int a[N], b[N];

char s[N];
std::pair<int, int> e[N];
int p[N];

int main() {
	scanf("%s%d", s, &n);
	int len = strlen(s);
	for(int i = 0; i < len; i++) a[s[i] - 'a'] = true;
	for(int i = 1; i <= n; i++) {
		scanf("%s", s);
		e[i] = {s[0] - 'a', s[1] - 'a'};
	}
	for(int i = 1; i <= n; i++) p[i] = i;
	int ans = 0;
	do {
		for(int i = 0; i < 26; i++) b[i] = a[i];
		for(int i = 1; i <= n; i++) {
			auto [u, v] = e[p[i]];
			if(!b[u]) continue;
			b[u] = false, b[v] = true;
		}
		int cnt = 0;
		for(int i = 0; i < 26; i++) cnt += b[i];
		if(ans < cnt) {
			printf("cnt = %d:\n", cnt);
			for(int i = 1; i <= n; i++) printf("  %c->%c\n", e[p[i]].first + 'a', e[p[i]].second + 'a');
			ans = cnt;
		}
	} while(std::next_permutation(p + 1, p + n + 1));
	printf("%d\n", ans);
	return 0;
} /*
abcd 5
ab bc cd db ce
*/