#include <cstdio>
#include <algorithm>
#include <utility>

const int N = 2000 + 5;
const int INF = 0x3f3f3f3f;

int a[N * 3];
int n;

int flag[N], dp[N][N], L[N][N], S[N], Max;
std::pair<int, int> upd[N * 10];

int add = 0;

template<typename T> inline T chkmaxval(T &x, T y) { return x = std::max(x, y); }
#define t(x) (t_ + (x))
#define chkmax(arr, ind1, ind2, val)\
	chkmaxval((arr)[(ind1)][(ind2)], (val)),\
	chkmaxval((arr)[(ind2)][(ind1)], (val)),\
	m++,\
	upd[m].first = (ind1),\
	upd[m].second = (ind2)

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n * 3; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n - 1; i++) {
		int t = 2 + (i - 1) * 3;	
		if(a[t + 1] == a[t + 2] && a[t + 2] == a[t + 3])
			add++, flag[i] = true;
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			dp[i][j] = L[i][j] = -INF;
	for(int i = 1; i <= n; i++) S[i] = -INF;
	Max = 0;
	dp[a[1]][a[2]] = dp[a[2]][a[1]] = L[a[1]][a[2]] = L[a[2]][a[1]] = S[a[1]] = S[a[2]] = 0;
	for(int i = 1; i <= n - 1; i++) {
		if(flag[i]) continue;
		int t = 2 + (i - 1) * 3, m = 0;
		chkmax(dp, a[t + 2], a[t + 3], std::max(Max, L[a[t + 1]][a[t + 1]] + 1));
		chkmax(dp, a[t + 1], a[t + 3], std::max(Max, L[a[t + 2]][a[t + 2]] + 1));
		chkmax(dp, a[t + 1], a[t + 2], std::max(Max, L[a[t + 3]][a[t + 3]] + 1));
		int tmp[5] = {a[t + 1], a[t + 2], a[t + 3]};
		std::sort(tmp, tmp + 3);
		int A = tmp[0], B = tmp[1], C = tmp[2];
		if(B == C) std::swap(A, C);
		for(int j = 1; j <= n; j++)
			if(S[j] >= 0)
				chkmax(dp, j, A, S[j]), chkmax(dp, j, B, S[j]), chkmax(dp, j, C, S[j]);
		if(A == B)π
			for(int j = 1; j <= n; j++)
				if(L[A][j] >= 0)
					chkmax(dp, C, j, L[A][j] + 1);
		for(int j = 1; j <= m; j++) {
			int x = upd[j].first, y = upd[j].second;
			L[x][y] = L[y][x] = dp[x][y];
			chkmaxval(Max, dp[x][y]);
			chkmaxval(S[x], dp[x][y]), chkmaxval(S[y], dp[x][y]);
		}
	}
	printf("%d\n", std::max(Max, dp[a[n * 3]][a[n * 3]] + 1) + add);
	return 0;
}