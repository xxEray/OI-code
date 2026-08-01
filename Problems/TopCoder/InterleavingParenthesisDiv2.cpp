#include <cstdio>
#include <algorithm>
#include <string>
using std::string;

typedef long long LL;

const int N = 50 + 5;
const LL MOD = 1e9 + 7;

char a[N], b[N];
int n, m;
LL f[N][N], g[N][N];

class InterleavingParenthesisDiv2 {
public:
	int countWays(string s1, string s2) {
		n = s1.size(), m = s2.size();
		for(int i = 1; i <= n; i++) a[i] = s1[i - 1];
		for(int i = 1; i <= m; i++) b[i] = s2[i - 1];
		for(int i = 1; i <= n; i++) g[i][0] = g[i - 1][0] + (a[i] == '(' ? 1 : -1);
		for(int i = 0; i <= n; i++) for(int j = 1; j <= m; j++) g[i][j] = g[i][j - 1] + (b[j] == '(' ? 1 : -1);
		// for(int i = 0; i <= n; i++) for(int j = 0; j <= m; j++) printf("g[%d][%d] = %lld\n", i, j, g[i][j]);
		f[0][0] = 1;
		for(int i = 1; i <= n; i++) if(g[i][0] >= 0) f[i][0] = f[i - 1][0];
		for(int i = 1; i <= m; i++) if(g[0][i] >= 0) f[0][i] = f[0][i - 1];
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(g[i][j] >= 0) f[i][j] = (f[i - 1][j] + f[i][j - 1]) % MOD;
		// for(int i = 0; i <= n; i++) for(int j = 0; j <= m; j++) printf("f[%d][%d] = %lld\n", i, j, f[i][j]);
		return g[n][m] == 0 ? f[n][m] : 0;
	}
};

int main() {
	InterleavingParenthesisDiv2 T;
	printf("%d\n", T.countWays("", ""));
	return 0;
}