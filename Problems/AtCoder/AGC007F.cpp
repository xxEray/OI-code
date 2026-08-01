#include <bits/stdc++.h>

const int N = 1e6 + 5;

int n;
char s[N], t[N];

int last[N][30];
int prv[N];

int main() {
	scanf("%d%s%s", &n, s + 1, t + 1);
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < 26; j++) last[i][j] = last[i - 1][j];
		last[i][s[i] - 'a'] = i;
	}
	for(int i = n, j = n; i >= 1; i--) {
		j = std::min(j, i);
		prv[i] = last[j][t[i] - 'a'];
		j = prv[i];
	}
	for(int i = 1; i <= n; i++) if(!prv[i]) { puts("-1"); return 0; }
	std::vector<int> vct{1};
	for(int i = 2; i <= n; i++) if(prv[i] == i) vct.emplace_back(i);
	vct.emplace_back(n + 1);
	int ans = 0;
	for(int i = 0; i < (int)vct.size() - 1; i++) {
		std::unordered_set<int> st;
		for(int j = vct[i] + 1; j <= vct[i + 1] - 1; j++) st.emplace(t[j]);
		ans = std::max(ans, (int)st.size());
	}
	printf("%d\n", ans);
	return 0;
}