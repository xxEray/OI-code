#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

const int N = 2e5 + 5;

struct Node { int v, id; } tmp;
bool operator<(const Node &x, const Node &y) { return x.v < y.v; }
int n;

std::priority_queue<Node> q1, q2;
std::vector<std::pair<int, int> > ans;

int main() {
	scanf("%d%*d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &tmp.v), tmp.id = i;
		if(tmp.v) q1.push(tmp);
	}
	while(!q1.empty()) {
		Node x = q1.top(); q1.pop();
		while(x.v && !q1.empty()) {
			Node y = q1.top(); q1.pop();
			x.v--, y.v--, ans.push_back({x.id, y.id});
			if(y.v) q2.push(y);
		}
		while(!q2.empty()) q1.push(q2.top()), q2.pop();
		if(x.v) { puts("No"); return 0; }
	}
	printf("Yes\n%d\n", (int)ans.size());
	for(auto &p : ans) printf("%d %d\n", p.first, p.second);
	return 0;
}