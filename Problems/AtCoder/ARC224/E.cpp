#include <bits/stdc++.h>
#include <cassert>

typedef long long LL;

const int N = 1e6 + 5;

int n;
char s[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		int ans = 0;
		std::vector<char> stk;
		for(int i = 1; i <= n; i++) {
			if(s[i] == 'A') stk.emplace_back('A');
			else if(s[i] == 'B') {
				while(!stk.empty() && stk.back() == '|') stk.pop_back();
				if(!stk.empty()) stk.back() = '|'; // 'A' => '|'
				else ans++;
			} else {
				while(!stk.empty() && stk.back() == 'A') stk.pop_back();
				if(!stk.empty()) stk.pop_back(); // pop '|'
				else ans++;
			}
			// printf(" i = %d, ans = %d\n", i, ans);
		}
		printf("%d\n", ans);
	}
	return 0;
}