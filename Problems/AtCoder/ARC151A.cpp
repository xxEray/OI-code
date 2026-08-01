#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

const int N = 2e5 + 5;

int n;
char s[N], t[N], ans[N];

std::vector<int> pos[2];

int main() {
	scanf("%d%s%s", &n, s + 1, t + 1);
	for(int i = 1; i <= n; i++)
		if(s[i] == t[i]) ans[i] = '0';
		else pos[s[i] - '0'].push_back(i);
	if((pos[0].size() + pos[1].size()) & 1) { puts("-1"); return 0; }
	int expect = (pos[0].size() + pos[1].size()) >> 1;
	for(int i = 0; i < std::min((int)pos[0].size(), expect); i++) ans[pos[0][i]] = '0';
	for(int i = expect; i < (int)pos[0].size(); i++) ans[pos[0][i]] = '1';
	for(int i = 0; i < std::min((int)pos[1].size(), expect); i++) ans[pos[1][i]] = '0';
	for(int i = expect; i < (int)pos[1].size(); i++) ans[pos[1][i]] = '1';
	ans[n + 1] = 0;
	puts(ans + 1);
	return 0;
}