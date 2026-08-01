#include <cstdio>

const int N = 9 + 2;
const int S = (1 << 9) + 5;

int maze[N][N];
int n, m;

int f[N][S];

inline int at(int s, int i) { return (s >> (i - 1)) & 1; }

bool checkset(int i, int s) {
	for(int j = 1; j <= m; j++) if(maze[i][j] == 0 && at(s, j) == 1) return false;
	for(int j = 2; j <= m; j++) if(maze[i][j - 1] == 0 && maze[i][j] == 1 && at(s, j) == 0) return false;
	return true;
}

bool vis[N];
bool check(int i, int s, int t) {
	if(checkset(i, s) == false || checkset(i - 1, t) == false) return false;
	for(int j = 1; j <= m; j++) vis[j] = false;
	for(int j = 1; j <= m; j++) if(maze[i][j]) { vis[j] = true; break; }
	for(int j = 1; j <= m; j++)
		for(int k = 1; k < j; k++)
			if(maze[i][j] && maze[i][k] && (at(s, j) == at(s, k) || at(t, j) == at(t, k)))
				vis[j] |= vis[k];
	for(int j = 1; j <= m; j++) if(maze[i][j] && !vis[j]) return false;
	return true;
}

char s[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%s", s + 1);
		for(int j = 1; j <= m; j++) maze[i][j] = (s[j] == '.');
	}
	
	return 0;
}