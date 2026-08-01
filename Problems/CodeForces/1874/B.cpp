#include <bits/stdc++.h>

const int N = 7e4 + 5;
const int INF = 0x3f3f3f3f;

const int index[2][2][2] = {{{7, 3}, {5, 1}}, {{6, 2}, {4, 0}}};

std::vector<int> to[N];
int dis[N];

inline int bit(int x, int i, int j) { return (x >> i & 1) << j; }
inline int ibt(int x, int i, int j) { return (65535 & ~(1 << j)) | bit(x, i, j); }

int mp[1000000];
std::vector<int> vct[8];
int cnt = 0;
void dfs(int id, int val) {
	if(id == 8) {
		mp[val] = INF;
		for(int i0 : vct[0]) for(int i1 : vct[1]) for(int i2 : vct[2]) for(int i3 : vct[3])
			for(int i4 : vct[4]) for(int i5 : vct[5]) for(int i6 : vct[6]) for(int i7 : vct[7])
				mp[val] = std::min(mp[val], dis[i0 << 14 | i1 << 12 | i2 << 10 | i3 << 8 | i4 << 6 | i5 << 4 | i6 << 2 | i7]);
		return;
	}
	vct[id] = {0, 1, 2, 3}, dfs(id + 1, val * 5 + 4);
	vct[id] = {0}, dfs(id + 1, val * 5 + 0);
	vct[id] = {1}, dfs(id + 1, val * 5 + 1);
	vct[id] = {2}, dfs(id + 1, val * 5 + 2);
	vct[id] = {3}, dfs(id + 1, val * 5 + 3);
}

void preprocess() {
	for(int i = 0; i < 65536; i++) {
		dis[i] = INF;
		to[i].push_back(i & ibt(i, 0, 1) & ibt(i, 2, 3) & ibt(i, 4, 5) & ibt(i, 6, 7) & ibt(i, 8, 9) & ibt(i, 10, 11) & ibt(i, 12, 13) & ibt(i, 14, 15));
		to[i].push_back(i | bit(i, 0, 1) | bit(i, 2, 3) | bit(i, 4, 5) | bit(i, 6, 7) | bit(i, 8, 9) | bit(i, 10, 11) | bit(i, 12, 13) | bit(i, 14, 15));
		to[i].push_back(i ^ bit(i, 1, 0) ^ bit(i, 3, 2) ^ bit(i, 5, 4) ^ bit(i, 7, 6) ^ bit(i, 9, 8) ^ bit(i, 11, 10) ^ bit(i, 13, 12) ^ bit(i, 15, 14));
		to[i].push_back(i ^ 85); // 85 = 0b0000000001010101
	}
	std::queue<int> q;
	dis[10023] = 0, q.push(10023); // 10023 = 0b0010011100100111
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : to[u]) if(dis[v] == INF) {
			dis[v] = dis[u] + 1;
			q.push(v);
		}
	}
	dfs(0, 0);
}

int main() {
	preprocess();
	int T; scanf("%d", &T);
	while(T--) {
		int a, b, c, d, m;
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &m);
		int val[8] = {4, 4, 4, 4, 4, 4, 4, 4};
		bool flag = true;
		for(int i = 0; i < 30; i++) {
			int &v = val[index[a >> i & 1][b >> i & 1][m >> i & 1]];
			int vv = (c >> i & 1) << 1 | (d >> i & 1);
			if(v != 4 && v != vv) { flag = false; break; }
			v = vv;
		}
		if(!flag) { puts("-1"); continue; }
		// for(int i = 7; i >= 0; i--) printf("%d ", val[i]);
		// puts("");
		int vv = val[7] * 78125 + val[6] * 15625 + val[5] * 3125 + val[4] * 625 + val[3] * 125 + val[2] * 25 + val[1] * 5 + val[0];
		printf("%d\n", mp[vv] == INF ? -1 : mp[vv]);
		// printf("%d\n", mp[vv]);
	}
	return 0;
} /*
1
50 50 0 0 39
*/