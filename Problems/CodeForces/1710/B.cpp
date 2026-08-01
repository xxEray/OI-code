#include <cstdio>
#include <algorithm>
#include <queue>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

struct Node { LL x, p; int id; LL calc(int r) const { return p + r * x; } } a[N];
int n;
LL m;

LL v[N];

int coe;
bool operator<(Node x, Node y) { return x.calc(coe) > y.calc(coe); }
std::priority_queue<Node> q;

LL mxl[N], mxr[N];
int out[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%lld", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%lld%lld", &a[i].x, &a[i].p), a[i].id = i;
		std::sort(a + 1, a + n + 1, [](Node x, Node y) { return x.x < y.x; });
		while(!q.empty()) q.pop();
		LL sum = 0;
		coe = 1;
		for(int i = 1; i <= n; i++) v[i] = 0;
		for(int i = 1; i <= n; i++) {
			while(!q.empty() && q.top().calc(1) <= a[i].x) sum -= q.top().calc(1), q.pop();
			v[i] += sum - a[i].x * (LL)q.size();
			q.push(a[i]), sum += a[i].calc(1);
		}
		sum = 0;
		coe = -1;
		while(!q.empty()) q.pop();
		for(int i = n; i >= 1; i--) {
			while(!q.empty() && q.top().calc(-1) <= -a[i].x) sum -= q.top().calc(-1), q.pop();
			v[i] += sum + a[i].x * (LL)q.size();
			q.push(a[i]), sum += a[i].calc(-1);
		}
		for(int i = 1; i <= n; i++) v[i] += a[i].p;
		for(int i = 1; i <= n; i++) v[i] = std::max(v[i] - m, 0LL);
		// printf("v: ");
		// for(int i = 1; i <= n; i++) printf("%lld ", v[i]);
		// puts("");
		mxl[0] = mxr[n + 1] = -LLINF;
		for(int i = 1; i <= n; i++) mxl[i] = std::max(mxl[i - 1], (v[i] == 0 ? -LLINF : v[i] - a[i].x));
		for(int i = n; i >= 1; i--) mxr[i] = std::max(mxr[i + 1], (v[i] == 0 ? -LLINF : v[i] + a[i].x));
		for(int i = 1; i <= n; i++)
			if(a[i].calc(-1) >= mxl[i] && a[i].calc(1) >= mxr[i]) out[a[i].id] = 1;
			else out[a[i].id] = 0;
		for(int i = 1; i <= n; i++) printf("%d", out[i]);
		puts("");
	}
	return 0;
} /*
4
3 6
1 5
5 5
3 4
2 3
1 3
5 2
2 5
1 6
10 6
6 12
1 6
4 5
5 5
8 3
9 7
12 5


*/