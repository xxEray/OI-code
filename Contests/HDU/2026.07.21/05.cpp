#include <bits/stdc++.h>

const int N = 1e5 + 5;

int main() {
	// freopen("05.txt", "w", stdout);
	int T; scanf("%d", &T);
	while(T--) {
		int K;
		scanf("%d", &K);
		std::vector<char> ans;
		int now = 1;
		while(K) {
			if(K >= now) {
				ans.emplace_back('a');
				K -= now;
				now++;
			} else {
				ans.emplace_back('a');
				K--, now = 1;
				if(K) {
					ans.emplace_back('b');
					K--, now++;
				}
			}
		}
		if(now == 1) ans.emplace_back('b');
		else ans.emplace_back('a');
		printf("%d %d\n", (int)ans.size(), 2);
		for(char c : ans) putchar(c);
		puts("");
	}
	return 0;
}