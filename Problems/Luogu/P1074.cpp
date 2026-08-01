#include <cstdio>
#include <algorithm>

const int N = 9 + 5;

int bl[N][N];

int a[N][N], score[N][N];
int sum[N][N];

void print(int arr[N][N]) { puts(""); for(int i = 1; i <= 9; i++) for(int j = 1; j <= 9; j++) printf("%d%c", arr[i][j], j == 9 ? '\n' : ' '); }

int tot[N], id[N], nxt[N];

bool r[N][N], c[N][N], b[N][N];

int ans = 0;
void dfs(int x, int y, int ret) {
	if(y == 10) dfs(nxt[x], 1, ret);
	if(x == 10) {
		// print(a);
		ans = std::max(ans, ret);
		return;
	}
	if(ret + sum[x][y] < ans) return;
	if(a[x][y]) dfs(x, y + 1, ret + score[x][y] * a[x][y]);
	else {
		for(int k = 1; k <= 9; k++) if(!r[x][k] && !c[y][k] && !b[bl[x][y]][k]) {
			a[x][y] = k;
			r[x][k] = c[y][k] = b[bl[x][y]][k] = true;
			dfs(x, y + 1, ret + score[x][y] * k);
			a[x][y] = 0;
			r[x][k] = c[y][k] = b[bl[x][y]][k] = false;
		}
	}
}

bool ok[N];

int main() {
	for(int i = 1; i <= 9; i++) for(int j = 1; j <= 9; j++) score[i][j] = 10 - std::max(std::abs(i - 5), std::abs(j - 5));
	for(int i = 0, cnt = 0; i <= 6; i += 3) for(int j = 0; j <= 6; j += 3) {
		cnt++;
		for(int p = 1; p <= 3; p++) for(int q = 1; q <= 3; q++) bl[i + p][j + q] = cnt;
	}
	for(int i = 1; i <= 9; i++) for(int j = 1; j <= 9; j++) scanf("%d", &a[i][j]);
	bool flag = true;
	for(int i = 1; i <= 9; i++) for(int j = 1; j <= 9; j++) if(a[i][j]) {
		int v = a[i][j];
		r[i][v] ? flag = false : r[i][v] = true;
		c[j][v] ? flag = false : c[j][v] = true;
		b[bl[i][j]][v] ? flag = false : b[bl[i][j]][v] = true;
	}
	while(flag) {
		bool modify = false;
		for(int i = 1; i <= 9; i++) for(int j = 1; j <= 9; j++) if(!a[i][j]) {
			for(int k = 1; k <= 9; k++) ok[k] = true;
			for(int k = 1; k <= 9; k++) if(r[i][k]) ok[k] = false;
			for(int k = 1; k <= 9; k++) if(c[j][k]) ok[k] = false;
			for(int k = 1; k <= 9; k++) if(b[bl[i][j]][k]) ok[k] = false;
			int cnt = 0;
			for(int k = 1; k <= 9; k++) cnt += ok[k];
			if(cnt == 0) flag = false;
			else if(cnt == 1) {
				for(int k = 1; k <= 9; k++) if(ok[k]) {
					a[i][j] = k;
					r[i][k] = c[j][k] = b[bl[i][j]][k] = true;
					break;
				}
				modify = true;
			}
		}
		if(!modify) break;
	}
	if(!flag) { puts("-1"); return 0; }
	// print(a);
	for(int i = 1; i <= 9; i++) for(int j = 1; j <= 9; j++) tot[i] += (a[i][j] == 0);
	for(int i = 1; i <= 9; i++) id[i] = i;
	std::sort(id + 1, id + 9 + 1, [](int x, int y) { return tot[x] < tot[y]; });
	id[10] = 10;
	for(int i = 1; i <= 9; i++) nxt[id[i]] = id[i + 1];
	for(int i = 9, s = 0; i >= 1; i--) for(int j = 9; j >= 1; j--) s += score[id[i]][j] * 9, sum[id[i]][j] = s;
	dfs(id[1], 1, 0);
	if(ans == 0) puts("-1");
	else printf("%d\n", ans);
	return 0;
}