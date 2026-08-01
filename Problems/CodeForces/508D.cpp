#include <bits/stdc++.h>

const int N = 300 * 300 + 5;

int n;
int ind[N], oud[N];
std::vector<int> to[N];

std::vector<int> seq;
void dfs(int u) {
	// printf("dfs %d\n", u);
	while(!to[u].empty()) {
		int v = to[u].back();
		to[u].pop_back();
		dfs(v);
	}
	// printf("dfs %d out\n", u);
	seq.push_back(u);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		char s[3];
		scanf("%s", s);
		to[s[1] * 300 + s[2]].push_back(s[0] * 300 + s[1]);
		oud[s[1] * 300 + s[2]]++, ind[s[0] * 300 + s[1]]++;
	}
	int st = 0, ed = 0, flag = true;
	for(int i = 1; i <= 90000; i++)
		if(oud[i] == ind[i] + 1) flag &= !st, st = i;
		else if(ind[i] == oud[i] + 1) flag &= !ed, ed = i;
		else if(ind[i] != oud[i]) flag = false;
	// printf("st = %d, ed = %d\n", st, ed);
	if(!st) for(int i = 1; i <= 90000; i++) if(ind[i]) { st = i; break; }
	if(!flag) { puts("NO"); return 0; }
	// for(int i = 1; i <= 90000; i++)
	// 	for(int j : to[i])
	// 		printf("%d %d\n", j, i);
	// printf("st = %d\n", st);
	dfs(st);
	// for(int x : seq) printf("%d ", x);
	// puts("");
	if((int)seq.size() != n + 1) { puts("NO"); return 0; }
	puts("YES");
	putchar(seq.front() / 300);
	for(int x : seq) putchar(x % 300);
	return 0;
} /*
4
aba
bab
cdc
dcd
*/