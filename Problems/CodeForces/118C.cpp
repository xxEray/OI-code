#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int a[N];
int n, m;

struct Node { int val, op, id; } num[N];
bool cmp(const Node &a, const Node &b) {
	if(a.val != b.val) return a.val < b.val;
	if(a.op != b.op) return a.op < b.op;
	if(a.id != b.id) return a.op ? a.id > b.id : a.id < b.id;
	return false;
}

int ret[N], ans[N];
int retv, ansv;
bool cmp2() {
	for(int i = 1; i <= n; i++) if(ret[i] != ans[i]) return ret[i] < ans[i];
	return false;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%1d", &a[i]);
	for(int i = 0; i <= 9; i++) {
		for(int j = 1; j <= n; j++) ret[j] = a[j];
		retv = 0;
		for(int j = 1; j <= n; j++) num[j] = (Node){std::abs(a[j] - i), a[j] < i, j};
		std::sort(num + 1, num + n + 1, cmp);
		for(int j = 1; j <= m; j++) ret[num[j].id] += (num[j].op ? num[j].val : -num[j].val), retv += num[j].val;
		if(i == 0 || retv < ansv || (retv == ansv && cmp2())) {
			for(int j = 1; j <= n; j++) ans[j] = ret[j];
			ansv = retv;
		}
	}
	printf("%d\n", ansv);
	for(int i = 1; i <= n; i++) printf("%d", ans[i]);
	return 0;
}