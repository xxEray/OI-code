#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int S1 = 900 + 5;
const int S2 = 8100 + 5;
const int N = 100 + 5;

const int INF = 0x3f3f3f3f;

int f[S1][S2];
int pre[S1][S2];

void solve() {
	for(int i = 0; i <= 900; i++)
		for(int j = 0; j <= 8100; j++)
			f[i][j] = INF;
	f[0][0] = 0;
	for(int i = 1; i <= 900; i++)
		for(int j = 1; j <= 8100; j++)
			for(int k = 1; k <= 9; k++) {
				int x = i - k, y = j - k * k;
				if(x >= 0 && y >= 0 && f[i][j] > f[x][y] + 1)
					f[i][j] = f[x][y] + 1, pre[i][j] = k;
			}
}

void getnums(std::vector<int> &nums, int i, int j) {
	if(i < 1 && j < 1) return;
	getnums(nums, i - pre[i][j], j - pre[i][j] * pre[i][j]);
	nums.push_back(pre[i][j]);
}

void answer(int s1, int s2) {
	if(s1 > 900 || s2 > 8100) { puts("No solution"); return; }
	if(f[s1][s2] > 100) { puts("No solution"); return; }
	std::vector<int> nums;
	getnums(nums, s1, s2);
	std::sort(nums.begin(), nums.end());
	for(int x : nums) printf("%d", x);
	puts("");
}

int main() {
	int T;
	scanf("%d", &T);
	solve();
	while(T--) {
		int s1, s2;
		scanf("%d%d", &s1, &s2);
		answer(s1, s2);
	}
	return 0;
} /*
4
9 81
12 9
6 10
7 9
*/