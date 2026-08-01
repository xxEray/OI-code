#include <bits/stdc++.h>

#define SZ(container) ((int)(container).size())

const int N = 50 + 5;
const int INF = 0x3f3f3f3f;

int n, m;
char a[N][N];
std::vector<int> to[N * N];

const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int hash(int x, int y) { return (x - 1) * m + y; }

int dis[N * N][N * N], dis2[N * N][N * N];

inline bool in(char c, const char *cs) {
	int len = strlen(cs);
	for(int i = 0; i < len; i++) if(c == cs[i]) return true;
	return false;
}
void get_dis(int *d, int st, const char *count, const char *road) {
	std::queue<int> q;
	for(int i = 1; i <= n * m; i++) d[i] = INF;
	if(!in(a[(st - 1) / m + 1][(st - 1) % m + 1], count)) return;
	q.push(st), d[st] = 0;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : to[u]) if(in(a[(v - 1) / m + 1][(v - 1) % m + 1], count) && d[v] == INF) {
			d[v] = d[u] + 1;
			if(in(a[(v - 1) / m + 1][(v - 1) % m + 1], road)) q.push(v);
		}
	}
}

std::vector<int> park, car;
std::vector<int> order[N * N];
int mycar, E;
bool exist[N * N];
int place[N * N], occupied_by[N * N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%s", a[i] + 1);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
		for(int d = 0; d < 4; d++) {
			int x = i + dir[d][0], y = j + dir[d][1];
			if(x >= 1 && x <= n && y >= 1 && y <= m) to[hash(i, j)].push_back(hash(x, y));
		}
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
		if(a[i][j] == 'A') park.push_back(hash(i, j));
		else if(a[i][j] == 'C') car.push_back(hash(i, j));
		else if(a[i][j] == 'Y') mycar = hash(i, j);
		else if(a[i][j] == 'E') E = hash(i, j);
	std::sort(car.begin(), car.end());
	for(int i = 1; i <= n * m; i++) get_dis(dis[i], i, "AYC.", "YC."), get_dis(dis2[i], i, "EUAYC.", "UAYC.");
	for(int i : car) {
		order[i] = park;
		std::sort(order[i].begin(), order[i].end(), [&](int x, int y) { return dis[i][x] == dis[i][y] ? x < y : dis[i][x] < dis[i][y]; });
		std::reverse(order[i].begin(), order[i].end());
		// printf("car %d: ", i);
		// for(int j : order[i]) printf("%d ", j);
		// puts("");
	}
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
	for(int x : car) q.push({dis[x][order[x].back()], x});
	for(int x : park) exist[x] = true;
	while(!q.empty()) {
		int x = q.top().second;
		q.pop();
		if(exist[order[x].back()]) {
			place[x] = order[x].back();
			exist[place[x]] = false, occupied_by[place[x]] = x;
			continue;
		}
		while(!order[x].empty() && !exist[order[x].back()]) order[x].pop_back();
		if(order[x].empty()) continue;
		q.push({dis[x][order[x].back()], x});
	}
	order[mycar] = park;
	std::sort(order[mycar].begin(), order[mycar].end(), [&](int x, int y) {
		return dis[mycar][x] + dis2[x][E] * 2 == dis[mycar][y] + dis2[y][E] * 2 ? x < y : dis[mycar][x] + dis2[x][E] * 2 < dis[mycar][y] + dis2[y][E] * 2;
	});
	// for(int x : park) printf("(%d, %d): occupied_by = (%d, %d)\n", (x - 1) / m + 1, (x - 1) % m + 1, (occupied_by[x] - 1) / m + 1, (occupied_by[x] - 1) % m + 1);
	// for(int x : car) printf("(%d, %d): place = (%d, %d)\n", (x - 1) / m + 1, (x - 1) % m + 1, (place[x] - 1) / m + 1, (place[x] - 1) % m + 1);
	int ans = -1;
	for(int x : order[mycar])
		if(exist[x] || dis[occupied_by[x]][x] > dis[mycar][x] || (dis[occupied_by[x]][x] == dis[mycar][x] && mycar < occupied_by[x])) {
			// printf("my car occupied (%d, %d)\n", (x - 1) / m + 1, (x - 1) % m + 1);
			ans = dis[mycar][x] + dis2[x][E] * 2;
			break;
		}
	printf("%d\n", ans);
	return 0;
}