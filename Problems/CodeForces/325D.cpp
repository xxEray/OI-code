#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <cctype>

inline int read() {
    int x = 0;
    char ch = getchar();
    while(!isdigit(ch)) ch = getchar();
    while(isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return x;
}

const int N = 3000 + 5;
const int MAXQ = 3e5 + 5;

int n, m, Q;

const int dir[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

int mmm;
inline int hash(int x, int y) { return x * mmm + y; }

bool land[N][N * 2], vis[N * N * 2];
int fa[N * N * 2], ht[N * N * 2];
int find(int x) {
	int y = x;
	while(y != fa[y]) y = fa[y];
	for(int t1 = x, t2; t1 != fa[t1]; t1 = t2) t2 = fa[t1], fa[t1] = y;
	return y;
}
void merge(int x, int y) {
	x = find(x), y = find(y);
	if(x ^ y) {
		if(ht[x] > ht[y]) x ^= y ^= x ^= y;
		if(ht[x] == ht[y]) ht[y]++;
		fa[x] = y;
	}
}

int main() {
	n = read(), m = read(), Q = read();
	mmm = m << 1;
	if(m == 1) { puts("0"); return 0; }
	for(int i = 0; i <= hash(n, m * 2); i++) fa[i] = i, ht[i] = 1;
	int ans = 0;
	while(Q--) {
		int x, y; x = read(), y = read();
		int vc1[10], vc2[10], c1 = 0, c2 = 0, fl = false;
		for(int i = 0; i < 8; i++) {
			int dx = x + dir[i][0], dy = y + dir[i][1];
			if(dx < 1 || dx > n) continue;
			if(dy < 1) dy = 2 * m;
			if(dy > 2 * m) dy = 1;
			if(!land[dx][dy]) continue;
			vc1[++c1] = hash(dx, dy);
			vis[find(hash(dx, dy))] = true;
		}
		for(int i = 0; i < 8; i++) {
			int dx = x + dir[i][0], dy = y + m + dir[i][1];
			if(dx < 1 || dx > n) continue;
			if(dy < 1) dy = 2 * m;
			if(dy > 2 * m) dy = 1;
			if(!land[dx][dy]) continue;
			vc2[++c2] = hash(dx, dy);
			if(vis[find(hash(dx, dy))]) fl = true;
		}
		if(!fl) {
			ans++, land[x][y] = land[x][y + m] = true;
			for(int i = 1; i <= c1; i++) merge(vc1[i], hash(x, y));
			for(int i = 1; i <= c2; i++) merge(vc2[i], hash(x, y + m));
		}
		for(int i = 1; i <= c1; i++) vis[find(vc1[i])] = false;
	}
	printf("%d\n", ans);
	return 0;
} /*
3 3 9
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3
*/