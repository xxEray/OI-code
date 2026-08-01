#include <bits/stdc++.h>

typedef long long LL;

const int N = 3000 + 5;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n;
int a[N];

int mnp[N][N], mxp[N][N];
void preprocess() {
	for(int i = 1; i <= n; i++) {
		mnp[i][i] = mxp[i][i] = i;
		for(int j = i + 1; j <= n; j++) {
			mnp[i][j] = (a[mnp[i][j - 1]] > a[j] ? j : mnp[i][j - 1]);
			mxp[i][j] = (a[mxp[i][j - 1]] < a[j] ? j : mxp[i][j - 1]);
		}
	}
}

std::unordered_map<LL, LL> mp;
int count = 0;
LL solve(int l, int r, int h) {
	if(l > r) return 0;
	if(mp.count(h * 3001LL * 3001 + l * 3001 + r)) return mp[h * 3001LL * 3001 + l * 3001 + r];
	// fprintf(stderr, "solve(%d, %d, %d)\n", l, r, h);
	int mn = a[mnp[l][r]] - h, mx = a[mxp[l][r]] - h;
	LL ret1 = 0, ret2 = 0;
	ret1 += (LL)(mx + mx - mn + 1) * mn / 2;
	for(int i = l - 1; i <= r; ) {
		int j = mnp[i + 1][r];
		if(!j || a[j] - h != mn) j = r + 1;
		ret1 += solve(i + 1, j - 1, h + mn);
		i = j;
	}
	for(int i = l - 1; i <= r; ) {
		if(i >= l) ret2 += mx;
		int j = mxp[i + 1][r];
		if(!j || a[j] - h != mx) j = r + 1;
		ret2 += solve(i + 1, j - 1, h);
		i = j;
	}
	return mp[h * 3001LL * 3001 + l * 3001 + r] = std::min(ret1, ret2);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	preprocess();
	printf("%lld\n", solve(1, n, 0));
	return 0;
}
