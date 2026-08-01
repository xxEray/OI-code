#pragma GCC optimize("-fdelete-null-pointer-checks,inline-functions-called-once,-funsafe-loop-optimizations,-fexpensive-optimizations,-foptimize-sibling-calls,-ftree-switch-conversion,-finline-small-functions,inline-small-functions,-frerun-cse-after-loop,-fhoist-adjacent-loads,-findirect-inlining,-freorder-functions,no-stack-protector,-fpartial-inlining,-fsched-interblock,-fcse-follow-jumps,-fcse-skip-blocks,-falign-functions,-fstrict-overflow,-fstrict-aliasing,-fschedule-insns2,-ftree-tail-merge,inline-functions,-fschedule-insns,-freorder-blocks,-fwhole-program,-funroll-loops,-fthread-jumps,-fcrossjumping,-fcaller-saves,-fdevirtualize,-falign-labels,-falign-loops,-falign-jumps,unroll-loops,-fsched-spec,-ffast-math,Ofast,inline,-fgcse,-fgcse-lm,-fipa-sra,-ftree-pre,-ftree-vrp,-fpeephole2",3)
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <unordered_map>

typedef long long LL;

const int INF = 0x3f3f3f3f;

LL qpow(LL x, LL y, LL mod) { LL ret = 1 % mod; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }

void chkmin(int &x, int y) { x > y ? x = y : 0; }

std::unordered_map<int, int> mp;

int main() {
	// freopen("in.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);
	int T; scanf("%d", &T);
	while(T--) {
		int p;
		scanf("%d", &p);
		if(p % 2 == 0) p /= 2;
		p *= 9;
		if(p % 2 == 0 || p % 5 == 0) { puts("-1"); continue; }
		int sqp = ceil(sqrt(p));
		// printf("p = %d, sqp = %d\n", p, sqp);
		mp.clear();
		LL v = 1, mul = qpow(10, sqp, p);
		int ans = INF;
		for(int i = 1; i <= sqp; i++) {
			(v *= mul) %= p;
			if(mp[v] == 0) mp[v] = i;
			else chkmin(mp[v], i);
		}
		v = 1;
		for(int i = 0; i < sqp; i++) {
			if(i) (v *= 10) %= p;
			if(mp.find(v) != mp.end()) chkmin(ans, mp[v] * sqp - i);
		}
		printf("%d\n", ans);
	}
	return 0;
}