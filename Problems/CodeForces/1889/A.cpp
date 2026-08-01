#include <bits/stdc++.h>

const int N = 100 + 5;

int n;
char s[N];

std::deque<int> q;
std::vector<int> ans;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%s", &n, s + 1);
		int cnt[2] = {};
		for(int i = 1; i <= n; i++) cnt[s[i] - '0']++;
		if((n & 1) || cnt[0] != cnt[1]) { puts("-1"); continue; }
		q.clear();
		for(int i = 1; i <= n; i++) q.push_back(s[i] - '0');
		ans.clear();
		int st = 0;
		while(!q.empty()) {
			if(q.front() != q.back()) { q.pop_front(), q.pop_back(), st++; }
			else if(q.front()) {
				ans.push_back(st);
				q.push_front(1), q.pop_back();
				st++;
			} else {
				ans.push_back(st + (int)q.size());
				q.pop_front(), q.push_back(0);
				st++;
			}
		}
		printf("%d\n", (int)ans.size());
		for(int x : ans) printf("%d ", x);
		puts("");
	}
	return 0;
}