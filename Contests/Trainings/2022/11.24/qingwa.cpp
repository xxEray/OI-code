#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int M = 1e5 + 5;
const LL MOD = 998244353;

int n, m;

int dfs(int b, const std::vector<int> &A, const std::vector<int> &B) {
	if(A.empty() && B.empty()) return 0;
	printf("dfs %d [", b);
	for(int x : A) printf("%d ", x);
	printf("\b] [");
	for(int x : B) printf("%d ", x);
	printf("\b]\n");
	std::vector<int> nA[2], nB[2];
	for(int x : A) nA[x >> b & 1].push_back(x);
	for(int x : B) nB[x >> b & 1].push_back(x);
	if(b == 0) {
		if(m & 1) return A.size() + B.size();
		else return std::max(nA[0].size() + nB[0].size(), nA[1].size() + nB[1].size());
	} else {
		if(m >> b & 1) {
			int v1 = dfs(b - 1, nA[0], nB[1]), v2 = dfs(b - 1, nA[1], nB[0]);
			return std::max({v1 + (int)std::max(nA[1].size(), nB[0].size()), v2 + (int)std::max(nA[0].size(), nB[1].size()), v1 + v2});
			// return std::max({(int)(nA[0].size() + nB[0].size()), (int)(nA[1].size() + nB[1].size()), v1, v2});
		} else return std::max(dfs(b - 1, nA[0], nB[0]), dfs(b - 1, nA[1], nB[1]));
	}
}

int solve(int b, const std::vector<int> &vct) {
	if(vct.empty()) return 0;
	std::vector<int> nxt[2];
	for(int x : vct) nxt[x >> b & 1].push_back(x);
	if(m < (1 << b)) return std::max(solve(b - 1, nxt[0]), solve(b - 1, nxt[1]));
	else return dfs(b - 1, nxt[0], nxt[1]);
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		std::vector<int> vct;
		for(int i = 1; i <= n; i++) { int x; scanf("%d", &x); vct.push_back(x); }
		printf("%d\n", solve(30, vct));
	}
	return 0;
}