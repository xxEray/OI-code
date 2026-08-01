#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

const int N = 4e5 + 5;
const int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}; // → ← ↓ ↑

struct Node { int x, y, rock; } a[N];
int Q, n, H, W;

std::map<int, std::vector<int>> row, col;
std::set<std::pair<int, int>> pos;

bool check(int x, int y) { return 1 <= x && x <= H && 1 <= y && y <= W; }

struct Edge { int to, nxt; } edge[N << 2];
int head[N];
void add_edge(int u, int v) { static int k = 1; edge[k] = (Edge){v, head[u]}, head[u] = k++; }

int main() {
	scanf("%d%d%d", &H, &W, &Q);
	while(Q--) {
		int x, y; scanf("%d%d", &x, &y);
		for(int d = 0; d < 4; d++) {
			int dx = x + dir[d][0], dy = y + dir[d][1];
			if(check(dx, dy) && pos.find({dx, dy}) == pos.end()) {
				pos.insert({dx, dy});
				n++;
				a[n].x = dx, a[n].y = dy, a[n].rock = d ^ 1;
				row[dx].push_back(n), row[dy].push_back(n);
			}
		}
	}
	for(auto &pr : row) {
		int i = pr.first;
		auto &v = pr.second;
		for(int j : v) {
			
		}
	}
	return 0;
}