// auto input
#include <bits/stdc++.h>
using std::cin;
using std::cout;

typedef long long LL;

const int N = 500 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m, src;
int K[N];
LL c[N];

LL f[2][N][N];

void chkmin(LL &x, LL y) { if(x > y) x = y; }

int main() {
	std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while(T--) {
		cin >> n >> m >> src;
		for(int i = 0; i <= m; i++) for(int j = 1; j <= n; j++) f[0][i][j] = f[1][i][j] = LLINF;
		f[0][0][src] = 0;
		for(int i = 1; i <= m; i++) cin >> K[i] >> c[i];
		for(int i = 1; i <= m; i++)
			for(int j = 0; j <= m; j++) {
				for(int k = 1; k <= n; k++) f[i & 1][j][k] = LLINF;
				for(int k = 1; k <= n; k++) {
					if(k - K[i] >= 1) chkmin(f[i & 1][j][k - K[i]], f[~i & 1][j][k] + c[i]);
					else if(j) chkmin(f[i & 1][j][1], f[~i & 1][j - 1][k] + c[i]);
					if(k + K[i] <= n) chkmin(f[i & 1][j][k + K[i]], f[~i & 1][j][k] + c[i]);
					else if(j) chkmin(f[i & 1][j][n], f[~i & 1][j - 1][k] + c[i]);
				}
				std::deque<int> q;
				for(int k = 1, t = 1; k <= n; k++) {
					while(t <= n && t <= k + K[i] - 1) {
						while(!q.empty() && f[~i & 1][j][q.back()] >= f[~i & 1][j][t]) q.pop_back();
						q.emplace_back(t);
						t++;
					}
					while(!q.empty() && q.front() <= k - K[i]) q.pop_front();
					if(!q.empty()) chkmin(f[i & 1][j][k], f[~i & 1][j][q.front()]);
				}
				// for(int k = 1; k <= n; k++) if(f[i & 1][j][k] < LLINF / 2) printf("f[%d][%d][%d] = %lld\n", i, j, k, f[i & 1][j][k]);
			}
		for(int i = 1; i <= n; i++) {
			LL lim;
			cin >> lim;
			bool flag = false;
			for(int j = m; j >= 0; j--) if(f[m & 1][j][i] <= lim) { cout << j << ' '; flag = true; break; }
			if(!flag) cout << -1 << ' ';
		}
		cout << '\n';
	}
	return 0;
} /*
1
5 4 3
0 2 0 4 0 1 0 3
0 2 10 7 10
*/