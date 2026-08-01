#include <cstdio>
#include <algorithm>
#include <vector>

#define SZ(x) ((int)(x).size())

const int N = 2e5 + 5;

std::vector<int> ans[2][2];
bool flag[2][2];
void calc(int id, int s, int t, int l, int r) {
	if(l == r) {
		flag[id][0] = flag[id][1] = false;
		if(s == t) flag[id][0] = true;
		if(s + t == l * 2) flag[id][1] = true, ans[id][1].push_back(l);
		return;
	}
	if((s & 1) != (t & 1)) { flag[id][0] = flag[id][1] = false; return; }
	int d = (r - l) * 2;
	// 0
	bool swp = false;
	if(s > t) std::swap(s, t), swp = true;
	if((t - s) / d + (bool)((t - s) % d) > 1000000) flag[id][0] = false;
	else {
		flag[id][0] = true;
		int i;
		for(i = s; i + d < t; i += d) ans[id][0].push_back(l), ans[id][0].push_back(r);
		if(i != t) {
			ans[id][0].push_back(l), i = 2 * l - i;
			ans[id][0].push_back((i + t) / 2);
		}
	}
	if(swp) std::reverse(ans[id][0].begin(), ans[id][0].end());
	// 1
	int sl = 2 * l - s, sr = 2 * r - s;
	if(std::abs(sl - t) < std::abs(sr - t)) ans[id][1].push_back(l), s = sl;
	else ans[id][1].push_back(r), s = sr;
	swp = false;
	if(s > t) std::swap(s, t), swp = true;
	if((t - s) / d + (bool)((t - s) % d) > 1000000) flag[id][1] = false;
	else {
		flag[id][1] = true;
		int i;
		for(i = s; i + d < t; i += d) ans[id][1].push_back(l), ans[id][1].push_back(r);
		if(i != t) {
			ans[id][1].push_back(l), i = 2 * l - i;
			ans[id][1].push_back((i + t) / 2);
		}
	}
	if(swp) std::reverse(ans[id][1].begin() + 1, ans[id][1].end());
}

int main() {
	int sx, sy, tx, ty, a, b, c, d;
	scanf("%d%d%d%d%d%d%d%d", &sx, &sy, &tx, &ty, &a, &b, &c, &d);
	calc(0, sx, tx, a, b), calc(1, sy, ty, c, d);
	int id;
	if(flag[0][0] && flag[1][0]) id = 0;
	else if(flag[0][1] && flag[1][1]) id = 1;
	else { puts("No"); return 0; }
	puts("Yes");
	int sz = std::max(SZ(ans[0][id]), SZ(ans[1][id]));
	for(int i = SZ(ans[0][id]); i < sz; i++) ans[0][id].push_back(a);
	for(int i = SZ(ans[1][id]); i < sz; i++) ans[1][id].push_back(c);
	for(int i = 0; i < sz; i++) printf("%d %d\n", ans[0][id][i], ans[1][id][i]);
	return 0;
}