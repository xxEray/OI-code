#include <cstdio>
#include <algorithm>
#include <map>

const int N = 2000 + 5;
const int HASH_MAX = 0xffff + 1;

struct Node { int val, id; } a[N];
bool operator<(const Node &lhs, const Node &rhs) { return lhs.val < rhs.val; }
bool operator==(const Node &lhs, const Node &rhs) { return lhs.val == rhs.val; }
int n;

std::map<int, int> mp;

int f[N][N], last[N][N];

void print(int x, int y) {
	if(last[x][y]) print(last[x][y], x);
	else printf("%d ", a[x].id);
	printf("%d ", a[y].id);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i].val), a[i].id = i;
	std::sort(a + 1, a + n + 1);
	n = std::unique(a + 1, a + n + 1) - a - 1;
	for(int i = 1; i <= n; i++) mp[a[i].val] = i;
	int mx = 0, mxi, mxj;
	for(int i = 1; i <= n; i++)
		for(int j = i + 1; j <= n; j++) {
			auto it = mp.find((a[i].val << 1) - a[j].val);
			if(it == mp.end()) { f[i][j] = 2; continue; }
			f[i][j] = f[it->second][i] + 1;
			last[i][j] = it->second;
			if(f[i][j] > mx) mx = f[i][j], mxi = i, mxj = j;
		}
	printf("%d\n", mx);
	print(mxi, mxj);
	return 0;
}