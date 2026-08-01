#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>
using std::vector;
using std::string;

const int N = 50 + 5;

vector<int> to[N];
int n;
bool need[N];

void dfs(int u, int fa) {
	if(fa) assert(*std::lower_bound(to[u].begin(), to[u].end(), fa) == fa), to[u].erase(std::lower_bound(to[u].begin(), to[u].end(), fa));
	for(int v : to[u]) if(u != fa) dfs(v, u);
	if(to[u].size() <= 1) need[u] = (u == 1);
	else {
		need[u] = false;
		for(int i = 0; i < (int)to[u].size() - 1; i++) need[to[u][i]] = true;
	}
}

class TPS {
public:
	int minimalBeacons(vector<string> linked) {
		n = linked.size();
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(linked[i - 1][j - 1] == 'Y') to[i].push_back(j);
		if(n == 1) return 0;
		dfs(1, 0);
		int ans = 0;
		for(int i = 1; i <= n; i++) ans += need[i], need[i] && printf("%d!\n", i);
		return ans;
	}
};

int main() {
	TPS T;
	printf("%d\n", T.minimalBeacons(
{"NNYNNNNNNN",
 "NNNNNYNNNN",
 "YNNYNNYNNN",
 "NNYNYNNYNN",
 "NNNYNYNNYN",
 "NYNNYNNNNY",
 "NNYNNNNNNN",
 "NNNYNNNNNN",
 "NNNNYNNNNN",
 "NNNNNYNNNN"}
));
	return 0;
} /*
2 6
6 10
6 5
5 9
5 4
4 8
4 3
3 7
3 1
*/