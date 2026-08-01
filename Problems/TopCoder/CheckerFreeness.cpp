#include <cstdio>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <algorithm>
using std::vector;
using std::string;

#define SZ(x) ((int)((x).size()))

typedef long long LL;
const int N = 222 + 5;

struct Point { int x, y; } wh[N], bl[N];
int n, m;

vector<int> readin(vector<string> &vct) {
	string tmp;
	for(auto s : vct) tmp += s;
	std::istringstream si(tmp);
	int x;
	vector<int> ret;
	while(si >> x) ret.push_back(x);
	return ret;
}

Point tmpw[N], tmpb[N];
int cnt;
bool main_() {
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
		cnt = 0;
		for(int i_ = i + 1; i_ <= n; i_++) tmpw[++cnt] = wh[i];
		std::sort(tmpw + 1, tmpw + cnt + 1, [&](Point a, Point b) { return calc(wh[i], bl[j], a, b); });
	}
}

class CheckerFreeness {
public:
	string isFree(vector<string> whiteX, vector<string> whiteY, vector<string> blackX, vector<string> blackY) {
		vector<int> t = readin(whiteX);
		n = SZ(t);
		for(int i = 0; i < n; i++) wh[i + 1].x = t[i];
		t = readin(whiteY);
		for(int i = 0; i < n; i++) wh[i + 1].y = t[i];
		t = readin(blackX);
		m = SZ(t);
		for(int i = 0; i < m; i++) bl[i + 1].x = t[i];
		t = readin(blackY);
		for(int i = 0; i < m; i++) bl[i + 1].y = t[i];
		if(main_()) return "NO";
		else return "YES";
	}
};

int main() {
	CheckerFreeness T;
	printf("%s\n", T.isFree(
{"1 2"},
{"2 1"},
{"1 2"},
{"1 2"}
	).c_str());
	return 0;
}