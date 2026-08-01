#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
using std::vector;
using std::string;

const int N = 9 + 4;
const int INF = 0x3f3f3f3f;

bool e[N][N];
int n;
int v[N];

class GraphLabel {
public:
	int adjacentDifference(vector<string> graph) {
		n = graph.size();
		for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) e[i][j] = graph[i - 1][j - 1] - '0';
		for(int i = 1; i <= n; i++) v[i] = i;
		int ans = INF;
		do {
			int ret = -INF;
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= n; j++)
					if(e[i][j])
						ret = std::max(ret, std::abs(v[i] - v[j]));
			ans = std::min(ans, ret);
		} while(std::next_permutation(v + 1, v + n + 1));
		return ans;
	}
};

int main() {
	GraphLabel T;
	printf("%d\n", T.adjacentDifference({"011111111",
 "101111111",
 "110111111",
 "111011111",
 "111101111",
 "111110111",
 "111111011",
 "111111101",
 "111111110"}));
	return 0;
}