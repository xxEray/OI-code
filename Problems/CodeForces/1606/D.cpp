#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 5e5 + 5;
const int INF = 0x3f3f3f3f;

std::vector<int> a[N], lmin[N], rmin[N], lmax[N], rmax[N];
int n, m;

int premin[N], sufmax[N];
struct Node { int mn, mx, id; } t[N];
bool operator<(Node x, Node y) { return x.mn == y.mn ? x.mx < y.mx : x.mn < y.mn; }

int tp[N];

int main() {
	int T; scanf("%d", &T);
	int ansi, ansj;
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i <= n + 1; i++) { std::vector<int> ().swap(a[i]); a[i].resize(m + 2); }
		for(int i = 0; i <= n + 1; i++) { std::vector<int> ().swap(lmin[i]); lmin[i].resize(m + 2); }
		for(int i = 0; i <= n + 1; i++) { std::vector<int> ().swap(rmin[i]); rmin[i].resize(m + 2); }
		for(int i = 0; i <= n + 1; i++) { std::vector<int> ().swap(lmax[i]); lmax[i].resize(m + 2); }
		for(int i = 0; i <= n + 1; i++) { std::vector<int> ().swap(rmax[i]); rmax[i].resize(m + 2); }
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
		for(int i = 1; i <= n; i++) lmin[i][0] = rmin[i][m + 1] = INF, lmax[i][0] = rmax[i][m + 1] = 0;
		for(int j = 1; j <= m; j++) {
			for(int i = 1; i <= n; i++) lmin[i][j] = (j == 1 ? a[i][j] : std::min(lmin[i][j - 1], a[i][j]));
			for(int i = 1; i <= n; i++) lmax[i][j] = (j == 1 ? a[i][j] : std::max(lmax[i][j - 1], a[i][j]));
		}
		for(int j = m; j >= 1; j--) {
			for(int i = 1; i <= n; i++) rmin[i][j] = (j == m ? a[i][j] : std::min(rmin[i][j + 1], a[i][j]));
			for(int i = 1; i <= n; i++) rmax[i][j] = (j == m ? a[i][j] : std::max(rmax[i][j + 1], a[i][j]));
		}
		premin[0] = INF, sufmax[n + 1] = 0;
		// for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) printf("%d, %d: lmin = %d, rmin = %d, lmax = %d, rmax = %d\n", i, j, lmin[i][j], rmin[i][j], lmax[i][j], rmax[i][j]);
		for(int j = 1; j < m; j++) {
			for(int i = 1; i <= n; i++) t[i] = (Node){lmin[i][j], lmax[i][j], i};
			std::sort(t + 1, t + n + 1);
			for(int i = 1; i <= n; i++) premin[i] = std::min(premin[i - 1], rmin[t[i].id][j + 1]); // , printf("premin[%d] = %d\n", i, premin[i]);
			for(int i = n; i >= 1; i--) sufmax[i] = std::max(sufmax[i + 1], rmax[t[i].id][j + 1]); // , printf("sufmax[%d] = %d\n", i, sufmax[i]);
			int lpremax = 0;
			for(int i = 1; i < n; i++) {
				lpremax = std::max(lpremax, t[i].mx);
				if(lpremax < t[i + 1].mn && premin[i] > sufmax[i + 1]) { ansi = i, ansj = j; goto _Print_Solution_; }
			}
		}
		puts("NO");
		continue;
	_Print_Solution_:
		puts("YES");
		for(int i = 1; i <= n; i++) tp[t[i].id] = (i <= ansi ? 0 : 1);
		for(int i = 1; i <= n; i++) putchar(tp[i] ? 'R' : 'B');
		printf(" %d\n", ansj);
	}
	return 0;
}