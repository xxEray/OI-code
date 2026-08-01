#include <bits/stdc++.h>

typedef long long LL;

const int N = (1 << 25) + 5;
const int D = (1 << 28);

LL X, Y;
int a[N], b[N];
LL al[N], ar[N];
int n;
struct Node { LL xl, xr, yl, yr; };

Node calc(Node x, int d, LL l, LL r) {
	if(d == 0) x.xl += l, x.xr += r;
	else if(d == 1) x.yl -= r, x.yr -= l;
	else if(d == 2) x.xl -= r, x.xr -= l;
	else if(d == 3) x.yl += l, x.yr += r;
	else __builtin_unreachable();
	return x;
}

std::vector<Node> vct;
std::vector<int> vctid, vctans;
std::vector<std::pair<LL, LL>> vx, vy;
std::vector<int> vxid, vyid, vxans, vyans;

bool dfsx(int id, std::pair<LL, LL> pr) {
	if(id == (int)vx.size()) { return pr.first <= X && X <= pr.second; }
	if(vxans[id] = 1, dfsx(id + 1, {pr.first + vx[id].first, pr.second + vx[id].second})) return true;
	if(vxans[id] = -1, dfsx(id + 1, {pr.first - vx[id].second, pr.second - vx[id].first})) return true;
	return false;
}
bool dfsy(int id, std::pair<LL, LL> pr) {
	if(id == (int)vy.size()) { return pr.first <= Y && Y <= pr.second; }
	if(vyans[id] = 1, dfsy(id + 1, {pr.first + vy[id].first, pr.second + vy[id].second})) return true;
	if(vyans[id] = -1, dfsy(id + 1, {pr.first - vy[id].second, pr.second - vy[id].first})) return true;
	return false;
}
bool dfs(int id, Node nd) {
	if(id == (int)vct.size()) return dfsx(0, {nd.xl, nd.xr}) && dfsy(0, {nd.yl, nd.yr});
	if(vctans[id] = 1, dfs(id + 1, {nd.xl + vct[id].xl, nd.xr + vct[id].xr, nd.yl + vct[id].yl, nd.yr + vct[id].yr})) return true;
	if(vctans[id] = -1, dfs(id + 1, {nd.xl - vct[id].xr, nd.xr - vct[id].xl, nd.yl - vct[id].yr, nd.yr - vct[id].yl})) return true;
	return false;
}

Node suf[N];

int main() {
#ifndef DEBUG
	freopen("balsamina.in", "r", stdin);
	freopen("balsamina.out", "w", stdout);
#endif
	scanf("%d%lld%lld", &n, &X, &Y);
	for(int i = 1; i <= n; i++) {
		char ch[2];
		scanf("%s%lld%lld", ch, &al[i], &ar[i]);
		if(ch[0] == 'L') a[i] = -1;
		else if(ch[0] == 'R') a[i] = 1;
		else a[i] = 0;
	}
	Node nd0 = {0, 0, 0, 0};
	{
		int i = 1, d0 = 0;
		while(i <= n && a[i]) (d0 += (a[i] == 1 ? 1 : 3)) %= 4, nd0 = calc(nd0, d0, al[i], ar[i]), i++;
		for(; i <= n;)
			if(i == n || !a[i + 1]) {
				if(i & 1) vy.emplace_back(al[i], ar[i]), vyid.emplace_back(i);
				else vx.emplace_back(al[i], ar[i]), vxid.emplace_back(i);
				i++;
			} else {
				Node nd = {0, 0, 0, 0};
				vctid.emplace_back(i);
				int d = i & 1;
				nd = calc(nd, d, al[i], ar[i]);
				for(i++; i <= n && a[i]; i++) (d += (a[i] == 1 ? 1 : 3)) %= 4, nd = calc(nd, d, al[i], ar[i]);
				vct.emplace_back(nd);
			}
	}
	vctans.resize(vct.size()), vxans.resize(vx.size()), vyans.resize(vy.size());
	// printf("X = %lld, Y = %lld\n", X, Y);
	// printf("nd0: [%lld, %lld] [%lld, %lld]\n", nd0.xl, nd0.xr, nd0.yl, nd0.yr);
	// printf("vct:\n"); for(auto [xl, xr, yl, yr] : vct) printf("  [%lld, %lld] [%lld, %lld]\n", xl, xr, yl, yr);
	// printf("vx:\n"); for(auto [l, r] : vx) printf("  [%lld, %lld]\n", l, r);
	// printf("vy:\n"); for(auto [l, r] : vy) printf("  [%lld, %lld]\n", l, r);
	if(!dfs(0, nd0)) { puts("-1"); return 0; }
	printf("%d\n", n);
	for(int i = 0; i < (int)vct.size(); i++) {
		int d = vctid[i] & 1;
		if(vctans[i] == -1) (d += 2) %= 4;
		b[vctid[i]] = d;
	}
	for(int i = 0; i < (int)vx.size(); i++) b[vxid[i]] = (vxans[i] == 1 ? 0 : 2);
	for(int i = 0; i < (int)vy.size(); i++) b[vyid[i]] = (vyans[i] == 1 ? 3 : 1);
	for(int i = 1; i <= n; i++)
		if(!a[i]) a[i] = ((b[i] - b[i - 1] + 4) % 4 == 1 ? 1 : -1);
		else b[i] = (b[i - 1] + a[i] + 4) % 4;
	for(int i = n; i >= 1; i--) suf[i] = calc(suf[i + 1], b[i], al[i], ar[i]);
	LL x = 0, y = 0;
	for(int i = 1; i <= n; i++)
		if(i & 1) {
			LL v;
			if(b[i] == 3) v = std::max(Y - suf[i + 1].yr, y + al[i]);
			else v = std::max(Y - suf[i + 1].yr, y - ar[i]);
			printf("%c %lld\n", (a[i] == 1 ? 'R' : 'L'), std::abs(y - v));
			y = v;
		} else {
			LL v;
			if(b[i] == 0) v = std::max(X - suf[i + 1].xr, x + al[i]);
			else v = std::max(X - suf[i + 1].xr, x - ar[i]);
			printf("%c %lld\n", (a[i] == 1 ? 'R' : 'L'), std::abs(x - v));
			x = v;
		}
	return 0;
} /*
2 -3 4
L 2 5
? 3 5

5 3 -4
? 1 5
? 1 5
? 1 5
? 1 5
? 1 5
*/