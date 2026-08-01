#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>

typedef long long LL;
const int N = 150 + 5;
const LL MOD = 123456789;

int n, m;
int matrix[N * 3][N * 3], equ[N * N][N * 3];
int hash[N][N];
bool vis[N];

const int dir[9][2] = {{1, 2}, {1, -2}, {-2, 1}, {-1, 2}, {2, -1}, {-1, -2}, {-2, -1}, {0, 0}, {2, 1}};
LL qpow(LL a, LL b) { LL ret = 1; while(true) { if(b & 1) (ret *= a) %= MOD; if(!(b >>= 1)) return ret; (a *= a) %= MOD; } }
bool check(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }

int gauss(int r, int c) {
	int free = 0;
	for(int var = 1; var <= c - 1; var++) {
		int id = -1;
		for(int i = 1; i <= r; i++) if(!vis[i] && matrix[i][var]) { id = i; break; }
		if(id == -1) { free++; continue; }
		vis[id] = true;
		for(int i = 1; i <= r; i++) if(i != id && matrix[i][var])
			for(int j = var; j <= c; j++)
				matrix[i][j] ^= matrix[id][j];
	}
	return free;
}

class KnightsOut {
public:
	int count(int n_, int m_) {
		n = n_, m = m_;
		int varc, cc = 0, ce = 0; // var_cnt, hash_cnt, equation_cnt
		for(int i = 1; i <= std::min(n, 2); i++) for(int j = 1; j <= m; j++) hash[i][j] = ++cc;
		for(int i = 3; i <= n; i++) hash[i][1] = ++cc;
		varc = cc;
		for(int i = 3; i <= n; i++) for(int j = 2; j <= m; j++) hash[i][j] = ++cc;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				if(i <= 2 || j <= 1) equ[hash[i][j]][hash[i][j]] = 1;
				else {
					equ[hash[i][j]][varc + 1] = 1;
					for(int d = 0; d < 8; d++) {
						int ti = i - 2 + dir[d][0], tj = j - 1 + dir[d][1];
						if(!check(ti, tj)) continue;
						for(int k = 1; k <= varc + 1; k++) equ[hash[i][j]][k] ^= equ[hash[ti][tj]][k];
					}
				}
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				if(i > n - 2 || j > m - 1) {
					ce++, matrix[ce][varc + 1] = 1;
					for(int d = 0; d < 9; d++) {
						int ti = i + dir[d][0], tj = j + dir[d][1];
						if(!check(ti, tj)) continue;
						for(int k = 1; k <= varc + 1; k++) matrix[ce][k] ^= equ[hash[ti][tj]][k];
					}
				}
		int free = gauss(ce, varc + 1);
		return qpow(2, free);
	}
};

int main() {
	KnightsOut T;
	printf("%d\n", T.count(69, 142));
	return 0; 
}