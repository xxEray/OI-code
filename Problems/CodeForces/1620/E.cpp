#include <cstdio>
#include <algorithm>
#include <map>
#include <deque>

const int N = 5e5 + 5;

int a[N];
int n, Q;

int qid[N];
struct Node { int repl, bef; };
std::deque<Node> q[N];
std::map<int, int> mp;

int cn;
int index(int x) { return mp.find(x) == mp.end() ? mp[x] = ++cn : mp[x]; }

int main() {
	scanf("%d", &Q);
	for(int i = 1; i <= Q; i++) {
		int t, x, y;
		scanf("%d", &t);
		if(t == 1) scanf("%d", &x), a[++n] = x;
		else scanf("%d%d", &x, &y), q[index(x)].push_back({y, n}), qid[i] = index(x);
	}
	
	return 0;
}