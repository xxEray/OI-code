#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>

typedef long long LL;
const int N = 150 + 5;
const LL MOD = 123456789;

int n, m;
struct Equation { std::set<int> coe; int result; } equ[N * N];
std::set<int> mention[N * N], tmp;
bool vis[N * N];

#define contains(container, element) ((container).find((element)) != (container).end())
const int dir[9][2] = {{1, 2}, {2, 1}, {1, -2}, {-2, 1}, {-1, 2}, {2, -1}, {-1, -2}, {-2, -1}, {0, 0}};
int hash(int x, int y) { return (x - 1) * m + y; }
LL qpow(LL a, LL b) { LL ret = 1; while(true) { if(b & 1) (ret *= a) %= MOD; if(!(b >>= 1)) return ret; (a *= a) %= MOD; } }
bool check(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }

int gauss(int r, int c) {
	int free = 0;
	for(int var = 1; var <= r; var++) {
		// puts("---");
		int id = -1;
		for(int i = 1; i <= r; i++) if(!vis[i] && contains(equ[i].coe, var)) { id = i; break; }
		if(id == -1) { free++; /* printf("var = %d: skip\n", var); */ continue; }
		vis[id] = true;
		// printf("var = %d, id = %d\n", var, id);
		tmp = mention[var];
		for(int i : tmp) if(i != id) {
			for(int j : equ[id].coe)
				// do xor
				if(contains(equ[i].coe, j)) {
					equ[i].coe.erase(j);
					assert(contains(mention[j], i));
					mention[j].erase(i);
				} else {
					equ[i].coe.insert(j);
					assert(!contains(mention[j], i));
					mention[j].insert(i);
				}
			equ[i].result ^= equ[id].result;
		}
		// for(int i = 1; i <= n * m; i++) {
		// 	printf("%d: (xor) ", i);
		// 	for(int j : equ[i].coe) printf("[%d] ", j);
		// 	printf("= %d\n", equ[i].result);
		// }
		// for(int i = 1; i <= n * m; i++) {
		// 	printf("mention %d: ", i);
		// 	for(int j : mention[i]) printf("[%d] ", j);
		// 	puts("");
		// }
	}
	return free;
}

class KnightsOut {
public:
	int count(int n_, int m_) {
		n = n_, m = m_;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++) {
				equ[hash(i, j)].result = 1;
				for(int d = 0; d < 9; d++) {
					int i_ = i + dir[d][0], j_ = j + dir[d][1];
					if(!check(i_, j_)) continue;
					equ[hash(i, j)].coe.insert(hash(i_, j_));
				}
			}
		for(int i = 1; i <= n * m; i++) for(int j : equ[i].coe) assert(!contains(mention[j], i)), mention[j].insert(i);
		// for(int i = 1; i <= n * m; i++) {
		// 	printf("%d: (xor) ", i);
		// 	for(int j : equ[i].coe) printf("[%d] ", j);
		// 	printf("= %d\n", equ[i].result);
		// }
		// for(int i = 1; i <= n * m; i++) {
		// 	printf("mention %d: ", i);
		// 	for(int j : mention[i]) printf("[%d] ", j);
		// 	puts("");
		// }
		int free = gauss(n * m, n * m + 1);
		return qpow(2, free);
	}
};

int main() {
	KnightsOut T;
	printf("%d\n", T.count(69, 142));
	return 0;
}