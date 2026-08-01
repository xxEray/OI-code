#include <bits/stdc++.h>

typedef long long LL;

const int M = 5e4 + 5;
const int MAXW = 300 + 5;

int n, m;
std::vector<LL> vct[MAXW];
std::vector<LL> f, g[MAXW], h[MAXW];

int rbd;
void cdq(int id, const std::vector<LL> &a, std::vector<LL> &ret, int l, int r, int vl, int vr) {
	if(l > r) return;
	int mid = (l + r) >> 1;
	LL mx = a[mid]; int mxid = mid;
	for(int i = vl; i <= std::min(vr, mid); i++) if(mid - i <= rbd && a[i] + vct[id][mid - i] >= mx) mx = a[i] + vct[id][mid - i], mxid = i;
	ret[mid] = mx;
	cdq(id, a, ret, l, mid - 1, vl, mxid), cdq(id, a, ret, mid + 1, r, mxid, vr);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) { int w; LL v; scanf("%d%lld", &w, &v); vct[w].push_back(v); }
	for(int i = 0; i <= m; i++) f.push_back(0);
	for(int i = 1; i <= 300; i++) {
		for(int j = 0; j < i; j++) g[j].clear(), h[j].clear();
		for(int j = 0; j <= m; j++) g[j % i].push_back(f[j]);
		for(int j = 0; j < i; j++) h[j].resize(g[j].size());
		std::sort(vct[i].begin(), vct[i].end(), std::greater<LL>());
		if((int)vct[i].size() > m / i) vct[i].erase(vct[i].begin() + m / i, vct[i].end());
		std::vector<LL> tmp = {0};
		for(int j = 0; j < (int)vct[i].size(); j++) tmp.push_back(tmp.back() + vct[i][j]);
		vct[i] = tmp;
		for(int j = 0; j < i; j++) rbd = (int)vct[i].size() - 1, cdq(i, g[j], h[j], 0, (int)g[j].size() - 1, 0, (int)g[j].size() - 1);
		f.clear();
		for(int j = 0; j <= m; j++) f.push_back(h[j % i][j / i]);
		// printf("%d: ", i); for(int j = 0; j <= m; j++) printf("%lld ", f[j]); puts("");
	}
	for(int i = 1; i <= m; i++) printf("%lld ", f[i]);
	puts("");
	return 0;
}