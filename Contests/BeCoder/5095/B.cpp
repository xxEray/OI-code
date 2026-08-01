#include <bits/stdc++.h>

#define msg(...) fprintf(stderr, __VA_ARGS__)

typedef unsigned long long ull;

const int N = 1000 + 5;

int n, m;
int e[N][2];

int ans[N];
void dfs(int id, ull vl, ull qm) { // val, question-mark
	if(id == m + 1) {
		// msg("vl: "); for(int i = 1; i <= n; i++) msg("%llu ", vl >> i & 1); msg("\n");
		// msg("qm: "); for(int i = 1; i <= n; i++) msg("%llu ", qm >> i & 1); msg("\n");
		// msg("\n");
		int mn = 64, mx = 0;
		for(int i = 1; i <= n; i++) if(vl >> i & 1) mn = std::min(mn, i), mx = std::max(mx, i);
		if(mn == 64) {
			for(int i = 1; i <= n; i++) {
				if(~qm >> i & 1) continue;
				int j = i;
				while(qm >> (j + 1) & 1) j++;
				int len = j - i + 1;
				for(int p = 1; p <= len; p++) for(int q = p; q <= len; q++) ans[q - p + 1] ^= 1;
				i = j;
			}
		} else {
			bool flag = true;
			for(int i = mn; i <= mx; i++) flag &= (vl >> i & 1) || (qm >> i & 1);
			if(flag) {
				int bl = 1, br = 64;
				for(int i = mn - 1; i >= 1; i--) if(~qm >> i & 1) { bl = i + 1; break; }
				for(int i = mx + 1; i <= 64; i++) if(~qm >> i & 1) { br = i - 1; break; }
				for(int i = bl; i <= mn; i++)
					for(int j = mx; j <= br; j++)
						ans[j - i + 1] ^= 1;
			}
		}
		return;
	}
	int u = e[id][0], v = e[id][1];
	if((qm >> u & 1) && (qm >> v & 1)) {
		dfs(id + 1, vl | (1ull << u) | (1ull << v), qm ^ (1ull << u) ^ (1ull << v));
		dfs(id + 1, vl, qm ^ (1ull << u) ^ (1ull << v));
	} else if((~qm >> u & 1) && (~qm >> v & 1)) {
		if((vl >> u & 1) && (~vl >> v & 1)) dfs(id + 1, vl ^ (1ull << u) ^ (1ull << v), qm);
		else dfs(id + 1, vl, qm);
	} else if(qm >> u & 1) {
		if(~vl >> v & 1) dfs(id + 1, vl, qm ^ (1ull << u) ^ (1ull << v));
		else dfs(id + 1, vl, qm);
	} else {
		if(vl >> u & 1) dfs(id + 1, vl ^ (1ull << u) ^ (1ull << v), qm ^ (1ull << u) ^ (1ull << v));
		else dfs(id + 1, vl, qm);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) scanf("%d%d", &e[i][0], &e[i][1]);
	dfs(1, 0ull, ((1ull << n) - 1) << 1);
	for(int i = 1; i <= n; i++) printf("%d ", ans[i]);
	puts("");
	return 0;
}