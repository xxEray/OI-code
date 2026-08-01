#include <bits/stdc++.h>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int n, K;
std::string str;

int pre[30];
int g[N][30];
int solve() {
	// for(int j = 1; j < 26; j++) g[0][j] = INF;
	for(int i = 1; i <= n; i++) {
		pre[str[i]] = i;
		std::vector<int> vct;
		for(int j = 0; j < 26; j++) if(pre[j]) vct.push_back(pre[j]);
		std::sort(vct.begin(), vct.end(), std::greater<>());
		for(int j = 0; j < (int)vct.size() - 1; j++) vct[j] = vct[j + 1] + 1;
		vct[(int)vct.size() - 1] = 1;
		for(int j = 0; j < 26; j++) {
			g[i][j] = INF;
			for(int k = 0; k < (int)vct.size(); k++) if(j - k >= 0)
				g[i][j] = std::min(g[i][j], g[vct[k] - 1][j - k] + 1);
			// if(g[i][j] < INF) printf("g[%d][%d] = %d\n", i, j, g[i][j]);
		}
	}
	for(int j = 0; j <= 25; j++) if(g[n][j] <= K) return j + K;
	return INF;
}

class TreasureOfWinedag {
public:
	int solvePuzzle(int n_, int K_, int m, int c0, std::vector<int> c1, std::vector<int> c2, std::vector<int> c3, std::vector<int> c4, std::string s) {
		n = n_, K = K_;
		str = s;
		for(int i = s.size(); i <= n - 1; i++) {
			int t = (long long)i * c0 % m;
			int newChar = 'z';
			for(int j = 0; j <= 24; j++)
				if(t >= c3[j] && t <= c4[j] && t % c1[j] == c2[j]) {
					newChar = 'a' + j;
					break;
				}
			str.push_back(newChar);
		}
		str = ' ' + str;
		// printf("str =%s\n", str.c_str());
		for(int i = 1; i <= n; i++) str[i] -= 'a';
		return solve();
	}
};

// int main() {
// 	TreasureOfWinedag T;
// 	printf("%d\n", T.solvePuzzle(/* ... */));
// 	return 0;
// }