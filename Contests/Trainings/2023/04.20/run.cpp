#include <cstdio>
#include <algorithm>
#include <deque>

const int N = 5000 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
char a[N][N];
int ans[2 * N];

int lf[N][N], up[N][N];

struct Node { int u, l, r, ans; };

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%s", a[i] + 1);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
		if(a[i][j] == '#') lf[i][j] = j, up[i][j] = i;
		else lf[i][j] = lf[i][j - 1], up[i][j] = up[i - 1][j];
	for(int i = 1; i <= n; i++) {
		std::deque<Node> q;
		for(int j = 1; j <= m; j++) {
			if(a[i][j] == '.') {
				while(!q.empty() && q.back().u <= up[i][j]) q.pop_back();
				int l = (q.empty() ? lf[i][j] + 1 : q.back().r + 1);
				q.push_back({up[i][j], l, j, std::max(-up[i][j] - l, (q.empty() ? -INF : q.back().ans))});
				int ret = i + j + 1 + q.back().ans;
				// printf("(%d, %d): ans = %d\n", i, j, ret);
				// if(i == 5) {
				// 	printf("q: "); for(auto x : q) printf("%d,%d,%d,%d ", x.u, x.l, x.r, x.ans); puts("");
				// }
				ans[ret]++;
			} else {
				q.clear();
			}
		}
	}
	for(int i = 1; i <= n + m; i++) printf("%d ", ans[i]);
	puts("");
	return 0;
} /*
5 4
....
....
...#
.#..
....
*/