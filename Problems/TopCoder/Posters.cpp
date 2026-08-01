// #pragma GCC optimize("-fdelete-null-pointer-checks,inline-functions-called-once,-funsafe-loop-optimizations,-fexpensive-optimizations,-foptimize-sibling-calls,-ftree-switch-conversion,-finline-small-functions,inline-small-functions,-frerun-cse-after-loop,-fhoist-adjacent-loads,-findirect-inlining,-freorder-functions,no-stack-protector,-fpartial-inlining,-fsched-interblock,-fcse-follow-jumps,-fcse-skip-blocks,-falign-functions,-fstrict-overflow,-fstrict-aliasing,-fschedule-insns2,-ftree-tail-merge,inline-functions,-fschedule-insns,-freorder-blocks,-fwhole-program,-funroll-loops,-fthread-jumps,-fcrossjumping,-fcaller-saves,-fdevirtualize,-falign-labels,-falign-loops,-falign-jumps,unroll-loops,-fsched-spec,-ffast-math,Ofast,inline,-fgcse,-fgcse-lm,-fipa-sra,-ftree-pre,-ftree-vrp,-fpeephole2",3)
#include <cstdio>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cassert>
using std::vector;
using std::min;
using std::max;

const int N = 100 + 5;

int n, m, K;
struct Node { int r, c; } a[N], tmp[N];
int p[N];

int sum[10];
int ar[N], ac[N], cr, cc; // available r/c
int ub[N], db[N], lb[N], rb[N];
int ans = 0;
int op[50], pos[10][2];
void dfs(int id, int ret) {
	if(sum[id] + ret <= ans) return;
	if(id >= K + 1) {
		if(ret > ans) ans = ret;
		return;
	}
	for(int i = 1; i <= cr; i++)
		for(int j = 1; j <= cc; j++)
			for(int k = 0; k < 4; k++) {
				int xa, ya, xb, yb;
				if(k & 1) xa = ar[i], xb = xa + a[id].r - 1;
				else xb = ar[i] - 1, xa = xb - a[id].r + 1;
				if(k & 2) ya = ac[j], yb = ya + a[id].c - 1;
				else yb = ac[j] - 1, ya = yb - a[id].c + 1;
				if(xa < 1 || xb > n || ya < 1 || yb > m) continue;
				ub[id] = xa, db[id] = xb, lb[id] = ya, rb[id] = yb;
				int oldret = ret, U = 1 << (id - 1);
				for(int s = 0; s < U; s++) {
					int u = ub[id], d = db[id], l = lb[id], r = rb[id];
					for(int o = 1; o < id; o++) if(s >> (o - 1) & 1)
						u = max(u, ub[o]), d = min(d, db[o]), l = max(l, lb[o]), r = min(r, rb[o]);
					ret += op[s] * max(d - u + 1, 0) * max(r - l + 1, 0);
				}
				dfs(id + 1, ret);
				ret = oldret;
			}
}

class Posters {
public:
	int maxCover(int width, int height, vector<int> pWidth, vector<int> pHeight) {
		n = height, m = width, K = pWidth.size();
		for(int i = 0; i < K; i++) tmp[i + 1].c = pWidth[i], tmp[i + 1].r = pHeight[i];
		if(K == 0) return 0;
		if(K == 1) return tmp[1].r * tmp[1].c;
		for(int i = 1; i <= K; i++) p[i] = i;
		for(int i = 0; i < 32; i++) op[i] = (__builtin_popcount(i) & 1) ? -1 : 1;
		do {
			// if(p[1] > p[2]) continue;
			for(int i = 1; i <= K; i++) a[i] = tmp[p[i]];
			for(int i = K; i >= 1; i--) sum[i] = sum[i + 1] + a[i].r * a[i].c;
			cr = cc = 0;
			ar[++cr] = 1, ar[++cr] = n + 1, ar[++cr] = a[1].r + 1, ar[++cr] = n - a[2].r + 1;
			ac[++cc] = 1, ac[++cc] = m + 1, ac[++cc] = a[1].c + 1, ac[++cc] = m - a[2].c + 1;
			ub[1] = 1, db[1] = a[1].r, lb[1] = 1, rb[1] = a[1].c;
			ub[2] = n - a[2].r + 1, db[2] = n, lb[2] = m - a[2].c + 1, rb[2] = m;
			int ret = a[1].r * a[1].c + a[2].r * a[2].c - max(db[1] - ub[2] + 1, 0) * max(rb[1] - lb[2] + 1, 0);
			dfs(3, ret);
		} while(std::next_permutation(p + 1, p + K + 1));
		return ans;
	}
};

int main() {
	// int nn, mm, KK;
	// scanf("%d%d%d", &nn, &mm, &KK);
	// vector<int> xx, yy;
	// for(int i = 1; i <= KK; i++) { int x; scanf("%d", &x); xx.push_back(x); }
	// for(int i = 1; i <= KK; i++) { int x; scanf("%d", &x); yy.push_back(x); }
	// Posters T;
	// printf("%d\n", T.maxCover(nn, mm, xx, yy));
	Posters T;
	printf("%d\n", T.maxCover(8,18,
{2,2,5,4,1},
{2,17,12,15,6}));
	return 0;
} /*
8 18 5
2 2  5  4  1
2 17 12 15 6

AACCCCC.
AACCCCC.
AACCCCC.
AACCDDDD
AACCDDDD
AACCDDDD
AACCDDDD
AACCDDDD
AACCDDDD
AACCDDDD
AACCDDDD
AACCDDDD
AA.EDDDD
AA.EDDDD
AA.EDDDD
AA.EDDDD
ABBEDDDD
.BBEDDDD
*/