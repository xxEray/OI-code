#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
using std::vector;
using std::string;

#define SZ(x) ((int)(x).size())

typedef long long LL;
const int N = 333 + 5;

typedef long long LL;

int a[N];
int bx[N], by[N];
int n, m;

vector<int> readin(vector<string> &vct) {
	string tmp;
	for(auto s : vct) tmp += s;
	std::istringstream sin(tmp);
	int x;
	vector<int> ret;
	while(sin >> x) ret.push_back(x);
	return ret;
}

struct Angle { int r, c; };
bool operator<(Angle x, Angle y) { return (LL)x.r * y.c < (LL)y.r * x.c; }
bool operator==(Angle x, Angle y) { return x.r == y.r && x.c == y.c; }
Angle tx[N], ty[N];
struct Node { int x, y, pos; } temp[N];
Angle tmp[N];
void discrete(Angle *arr, int tot) {
	for(int i = 1; i <= tot; i++) tmp[i] = arr[i];
	std::sort(tmp + 1, tmp + tot + 1);
	int tot_ = std::unique(tmp + 1, tmp + tot + 1) - tmp - 1;
	for(int i = 1; i <= tot; i++) arr[i].r = std::lower_bound(tmp + 1, tmp + tot_ + 1, arr[i]) - tmp;
}

struct BIT {
	int t[N];
	void add(int ind, int v) { while(ind <= m) t[ind] += v, ind += ind & -ind; }
	int query(int r) { int ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
	void clear() { for(int i = 1; i <= m; i++) t[i] = 0; }
} seg;

class Ear {
public:
	LL getCount(vector<string> redX, vector<string> blueX, vector<string> blueY) {
		vector<int> t = readin(redX);
		n = SZ(t);
		for(int i = 0; i < n; i++) a[i + 1] = t[i];
		t = readin(blueX);
		m = SZ(t);
		for(int i = 0; i < m; i++) bx[i + 1] = t[i];
		t = readin(blueY);
		for(int i = 0; i < m; i++) by[i + 1] = t[i];
		std::sort(a + 1, a + n + 1);
		LL ans = 0;
		for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) {
			int cnt = 0;
			for(int k = 1; k <= m; k++)
				if(bx[k] > a[i] && bx[k] < a[j]) {
					++cnt;
					temp[cnt].pos = bx[k];
					tx[cnt].r = by[k], tx[cnt].c = bx[k] - a[i];
					ty[cnt].r = by[k], ty[cnt].c = a[j] - bx[k];
				}
			discrete(tx, cnt), discrete(ty, cnt);
			for(int k = 1; k <= cnt; k++) temp[k] = {tx[k].r, ty[k].r, temp[k].pos};
			std::sort(temp + 1, temp + cnt + 1, [](Node x, Node y) { return x.x < y.x; });
			seg.clear();
			int last = cnt;
			for(int k = cnt; k >= 1; k--) {
				int pl = std::lower_bound(a + 1, a + n + 1, temp[k].pos) - a - 1;
				int pr = std::upper_bound(a + 1, a + n + 1, temp[k].pos) - a;
				while(temp[last].x > temp[k].x) seg.add(temp[last].y, 1), last--;
				ans += (LL)(pl - i) * (j - pr) * (seg.query(cnt) - seg.query(temp[k].y));
			}
		}
		return ans;
	}
};

// int main() {
// 	Ear T;
// 	printf("%lld\n", T.getCount({"1 2 3 4 5 6 7 8 9"}, {"4 5 6 7 8"}, {"1 2 3 4 5"}));
// 	return 0;
// }