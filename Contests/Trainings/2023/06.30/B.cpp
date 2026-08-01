#include <bits/stdc++.h>

std::vector<int> ans;

struct Node { int base, i, j; };
std::vector<Node> swps;
int swapbit(int x, int i, int j) {
	if(i == j) return x;
	int vi = (x >> i & 1), vj = (x >> j & 1);
	x &= ~(1 << i), x &= ~(1 << j);
	x |= vi << j, x |= vj << i;
	return x;
}
void insert(int x) {
	for(int i = (int)swps.size() - 1; i >= 0; i--) x = (swapbit(x, swps[i].i, swps[i].j) ^ swps[i].base);
	ans.push_back(x);
}
void dfs(int i, int s, int t) {
	// printf("dfs(%d, %d, %d) | ", i, s, t);
	// for(auto &p : swps) printf("(%d, %d, %d) ", p.base, p.i, p.j);
	// puts("");
	t ^= s;
	if(i <= 1) {
		assert(t == 1 || t == 2 || t == 3);
		if(t == 1) insert(s), insert(s ^ 2), insert(s ^ 3), insert(s ^ 1);
		else if(t == 2) insert(s), insert(s ^ 1), insert(s ^ 3), insert(s ^ 2);
		else insert(s), insert(s ^ 1), insert(s ^ 3);
		return;
	}
	assert(t);
	int j = i;
	while(j >= 0 && !(t >> j & 1)) j--;
	t = swapbit(t, i, j), swps.push_back({s, i, j});
	assert(t >> i & 1);
	j = i - 1;
	while(j >= 0 && (t >> j & 1)) j--;
	if(j == -1) j = 0;
	t &= ~(1 << i);
	dfs(i - 1, 0, t ^ (1 << j));
	swps.back().base ^= (1 << swps.back().j);
	dfs(i - 1, t ^ (1 << j), t);
	swps.pop_back();
}

int main() {
	int n, s, t;
	scanf("%d%d%d", &n, &s, &t);
	if(s == t) { printf("0\n%d\n", s); return 0; }
	dfs(n - 1, s, t);
	// assert((int)ans.size() == (1 << n) - !(__builtin_popcount(s ^ t) & 1));
	// for(int i = 0; i < (int)ans.size() - 1; i++) assert(__builtin_popcount(ans[i] ^ ans[i + 1]) == 1);
	printf("%d\n", (int)ans.size() - 1);
	for(int x : ans) printf("%d ", x);
	puts("");
	return 0;
} /*
0 1 3 2 6 4 5 7 15 11 9 13 9 13 15 11 30 22 20 28 24 16 18 26 18 26 24 16 20 28 30 22
00000
00001
00011
00010
00110
00100
00101
00111
01111
01011
01001
01101
*/