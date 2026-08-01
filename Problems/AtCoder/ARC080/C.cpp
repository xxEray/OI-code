#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <array>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N];

int lg[N];
int go[2][N][21];
int calc(int x, int y) { return (x == -1 || y == -1) ? (x == -1 ? y : x) : (a[x] < a[y] ? x : y); }
void preprocess() {
	lg[0] = -1;
	for(int i = 1; i <= n; i++) lg[i] = lg[i >> 1] + 1;
	for(int i = 1; i <= n; i++) go[i & 1][i][0] = i, go[!(i & 1)][i][0] = -1;
	for(int k = 0; k <= 1; k++)
		for(int j = 1; j <= 20; j++)
			for(int i = 1; i + (1 << j) - 1 <= n; i++)
				go[k][i][j] = calc(go[k][i][j - 1], go[k][i + (1 << (j - 1))][j - 1]);
}
int calc_min(int l, int r) {
	int k = lg[r - l + 1];
	return calc(go[l & 1][l][k], go[l & 1][r - (1 << k) + 1][k]);
}
std::vector<int> ans;
std::set<std::array<int, 4>> st;
void insert(int l, int r) {
	if(l > r) return;
	int x = calc_min(l, r - 1), y = calc_min(x + 1, r);
	st.insert({a[x], a[y], l, r});
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	preprocess();
	insert(1, n);
	while(!st.empty()) {
		auto q = *st.begin();
		int l = q[2], r = q[3];
		st.erase(st.begin());
		int x = calc_min(l, r - 1), y = calc_min(x + 1, r);
		ans.push_back(a[x]), ans.push_back(a[y]);
		insert(l, x - 1), insert(x + 1, y - 1), insert(y + 1, r);
	}
	for(int v : ans) printf("%d ", v);
	return 0;
}