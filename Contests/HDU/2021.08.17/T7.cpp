#include <cstdio>
#include <algorithm>
#include <set>

const int N = 2e7 + 5;

struct Node { int p, v; };
bool operator<(const Node &x, const Node &y) { return x.p < y.p; }
bool operator>(const Node &x, const Node &y) { return x.p > y.p; }
struct Priority {
	std::multiset<Node, std::greater<Node> > sl; // begin 是大的
	std::multiset<Node, std::less<Node> > sr; // begin 是小的
	int mp[N], lcnt, rcnt;
	void init(int x) { lcnt = x + 1, rcnt = x; }
	#define sizel ((int)sl.size())
	#define sizer ((int)sr.size())
	#define check() (sizer - sizel == 0 || sizer - sizel == 1)
	#define exist(st, x) ((st).find({mp[x], (x)}) != (st).end())
	void insert_left(int x) {
		mp[x] = --lcnt;
		sl.insert({mp[x], x});
		if(!check()) sr.insert(*sl.begin()), sl.erase(sl.begin());
	}
	void insert_right(int x) {
		mp[x] = ++rcnt;
		sr.insert({mp[x], x});
		if(!check()) sl.insert(*sr.begin()), sr.erase(sr.begin());
	}
	void erase(int x) {
		if(exist(sl, x)) {
			sl.erase(sl.find({mp[x], x}));
			if(!check()) sl.insert(*sr.begin()), sr.erase(sr.begin());
		} else if(exist(sr, x)) {
			sr.erase(sr.find({mp[x], x}));
			if(!check()) sr.insert(*sl.begin()), sl.erase(sl.begin());
		}
	}
	int middle() { return sr.begin()->v; }
} q;
int Q;

int main() {
	scanf("%d", &Q);
	q.init(Q);
	int next = 1;
	while(Q--) {
		char type[3]; int x;
		scanf("%s", type);
		if(type[0] == 'L') q.insert_left(next++);
		else if(type[0] == 'R') q.insert_right(next++);
		else if(type[0] == 'G') scanf("%d", &x), q.erase(x);
		else if(type[0] == 'Q') printf("%d\n", q.middle());
	}
	return 0;
} /*
9
L
L
L
Q
R
Q
G 1
R
Q
*/