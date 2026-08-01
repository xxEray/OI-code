#include <bits/stdc++.h>

typedef long long LL;

const int N = 2.5e5 + 5;

int n;
int a[N], b[N];

struct Node { int ind, val; };
bool operator<(const Node &x, const Node &y) { return x.val < y.val; }
std::priority_queue<Node> q;
std::set<int> ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
	LL sum = 0;
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		sum += a[i];
		if(sum >= b[i]) {
			sum -= b[i], cnt++;
			q.push({i, b[i]}), ans.emplace(i);
		} else if(!q.empty() && q.top().val > b[i]) {
			sum += q.top().val, sum -= b[i], ans.erase(q.top().ind), q.pop();
			q.push({i, b[i]}), ans.emplace(i);
		}
	}
	printf("%d\n", cnt);
	for(int x : ans) printf("%d ", x);
	puts("");
	return 0;
}