#include <bits/stdc++.h>

typedef long long LL;

const int N = (1 << 25) + 5;
const int D = (1 << 28);
const int dir[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

LL X, Y;
int n;
struct Node { LL xl, xr, yl, yr; };

std::vector<Node> sa, sb;

void solve(const std::vector<Node> &vc, std::vector<Node> &vct) {
	vct.push_back({0, 0, 0, 0});
	for(auto [xl, xr, yl, yr] : vc) {
		int sz = vct.size();
		for(int i = 0; i < sz; i++) {
			vct.push_back({vct[i].xl + xl, vct[i].xr + xr, vct[i].yl + yl, vct[i].yr + yr});
			vct[i] = {vct[i].xl - xr, vct[i].xr - xl, vct[i].yl - yr, vct[i].yr - yl};
		}
	}
}

int main() {
#ifndef DEBUG
	freopen("balsamina.in", "r", stdin);
	freopen("balsamina.out", "w", stdout);
#endif
	scanf("%d%lld%lld", &n, &X, &Y);
	int d = 0;
	std::vector<Node> tmp;
	tmp.push_back({0, 0, 0, 0});
	for(int i = 1; i <= n; i++) {
		char ch[2]; LL l, r;
		scanf("%s%lld%lld", ch, &l, &r);
		if(ch[0] == 'R') d = (d + 3) % 4;
		else if(ch[0] == 'L') d = (d + 1) % 4;
		else tmp.push_back({0, 0, 0, 0}), d = (d + 1) % 4;
		if(dir[d][0] == 1) tmp.back().xl += l, tmp.back().xr += r;
		else if(dir[d][0] == -1) tmp.back().xl -= r, tmp.back().xr += -l;
		if(dir[d][1] == 1) tmp.back().yl += l, tmp.back().yr += r;
		else if(dir[d][1] == -1) tmp.back().yl -= r, tmp.back().yr += -l;
	}
	n = tmp.size() - 1;
	
	return 0;
}