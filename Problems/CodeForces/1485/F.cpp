#include <cstdio>
#include <algorithm>
#include <map>

typedef long long LL;

const int N = 2e5 + 5;
const int MOD = 1e9 + 7;

int b[N];
int n;

std::map<int, int> f;
int tag = 0; // f[i + tag] = dp[i]

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
		int sm = 0;
		f[b[1]] = 1, sm = (sm + 1) % MOD;
		for(int i = 1; i < n; i++) {
			int add = (sm - f[-tag]) % MOD;
			f[b[i + 1] - tag - b[i + 1]] += add;
			f[b[i + 1] - tag - b[i + 1]] %= MOD;
			sm += add;
			sm %= MOD;
			tag += b[i + 1];
		}
		printf("%d\n", sm);
	}
	return 0;
} /*
1
3
1 -1 1
-----
dp[1][1]=1 => {
	dp[2][-1]->1
	dp[2][0]->1
	----------
	dp[2][-1]={sum-dp[1][0]}
	dp[2][1+(-1)]=dp[1][1]
	----------
	tag[1]=0
	tag[2]=-1
	f[2][b[2]-tag[2]]={sum-f[1][0-tag[1]]}
	f[2][*+tag[2]]=f[1][*+tag[1]]
}
dp[1][1] = 1
dp[2][-1] = 1
dp[2][0] = 1
dp[3][0] = 1
dp[3][1] = 1 + 1
*/