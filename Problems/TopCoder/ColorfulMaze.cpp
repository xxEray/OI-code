#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>

const double eps = 1e-10;
const int N = 50 + 5;
const int MAXS = (1 << 7) + 5;
const int M = 10;

char a[N][N];
double b[10];
int n, m;

int fa[N * N * MAXS * M];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void  merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

int hash(int i, int j, int msk, int k) { return (i - 1) * m * 128 * 8 + (j - 1) * 128 * 8 + msk * 8 + k + 1; }
bool check(int msk, char c) { return (c == '.' || c == '$' || c == '!') || ('A' <= c && c <= 'G' && (msk >> (c - 'A') & 1)); }

double f[N * N * MAXS * M];
bool vis[N * N * MAXS * M];

const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
class ColorfulMaze {
public:
	double getProbability(std::vector<std::string> maze, std::vector<int> trap) {
		n = maze.size(), m = maze[0].size();
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) a[i][j] = maze[i - 1][j - 1];
		for(int i = 'A'; i <= 'G'; i++) b[i - 'A'] = trap[i - 'A'] / 100.0;
		int U = (1 << 7) - 1;
		for(int i = 1; i <= n * m * 128 * 8; i++) fa[i] = i, f[i] = 0;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
			for(int msk = 0; msk <= U; msk++) for(int k = 0; k <= 7; k++)
				for(int d = 0; d < 4; d++) {
					int ti = i + dir[d][0], tj = j + dir[d][1];
					if(ti < 1 || ti > n || tj < 1 || tj > m) continue;
					if(check(msk, a[i][j]) && check(msk, a[ti][tj])) merge(hash(i, j, msk, k), hash(ti, tj, msk, k));
				}
		int stx, sty, edx, edy;
		for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
			if(a[i][j] == '$') stx = i, sty = j;
			else if(a[i][j] == '!') edx = i, edy = j;
		for(int msk = U; msk >= 0; msk--) for(int k = 0; k <= 7; k++) {
			std::priority_queue<std::pair<double, std::pair<int, int>>> q;
			q.push({1, {edx, edy}}), f[find(hash(edx, edy, msk, k))] = 1, vis[hash(edx, edy, msk, k)] = true;
			while(!q.empty()) {
				int i = q.top().second.first, j = q.top().second.second;
				q.pop();
				for(int d = 0; d < 4; d++) {
					int ti = i + dir[d][0], tj = j + dir[d][1];
					if(ti < 1 || ti > n || tj < 1 || tj > m) continue;
					if(a[ti][tj] == '#') continue;
					if(a[i][j] - 'A' == k) continue;
					if('A' <= a[i][j] && a[i][j] <= 'G' && !(msk >> (a[i][j] - 'A') & 1)) {
						double ret = 0;
						ret += (1 - b[a[i][j] - 'A']) * f[find(hash(i, j, msk | (1 << (a[i][j] - 'A')), k))];
						if(k == 7) ret += b[a[i][j] - 'A'] * f[find(hash(i, j, msk, a[i][j] - 'A'))];
						if(f[find(hash(ti, tj, msk, k))] < ret) f[find(hash(ti, tj, msk, k))] = ret;
					} else {
						if(f[find(hash(ti, tj, msk, k))] < f[find(hash(i, j, msk, k))])
							f[find(hash(ti, tj, msk, k))] = f[find(hash(i, j, msk, k))];
					}
					if(vis[hash(ti, tj, msk, k)]) continue;
					vis[hash(ti, tj, msk, k)] = true;
					q.push({f[find(hash(ti, tj, msk, k))], {ti, tj}});
				}
			}
		}
		return f[find(hash(stx, sty, 0, 7))];
	}
};