#include <cstdio>
#include <algorithm>
#include <vector>

int n, m;

std::vector<int> seq;
void dfs(int i, int j) {
	if(i == n + 1) {
		for(int v : seq) printf("%d ", v);
		puts("");
		return;
	}
	for(int k = j + 1; k <= m; k++) {
		seq.push_back(k);
		dfs(i + 1, k);
		seq.pop_back();
	}
}

int main() {
	scanf("%d%d", &n, &m);
	dfs(1, 0);
	return 0;
}