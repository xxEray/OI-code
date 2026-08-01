#include <cstdio>
#include <algorithm>
#include <queue>

const int N = 2e5 + 5;

struct Segment { int l, r; } a[N];
bool cmp1(const Segment &x, const Segment &y) { return x.l < y.l; }
struct cmp2 { bool operator()(const Segment &x, const Segment &y) { return x.r > y.r; } }; // 因为 priority_queue 是大根堆，所以运算符要反一下
int n;

std::priority_queue<Segment, std::vector<Segment>, cmp2> q;

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].l, &a[i].r);
		std::sort(a + 1, a + n + 1, cmp1);
		bool flag = true;
		for(int i = 1, j = 1; j <= 1000000000;) {
			while(i <= n && a[i].l <= j) q.push(a[i++]);
			if(q.empty()) {
				if(i <= n) { j = a[i++].l; continue; }
				else break;
			}
			Segment sg = q.top();
			q.pop();
			if(sg.r < j) { flag = false; break; }
			j++;
		}
		if(!q.empty()) flag = false;
		puts(flag ? "Yes" : "No");
		while(!q.empty()) q.pop();
	}
	return 0;
} /*
WA seed: 110097429792326964
1
3
1 3
1 1
2 3
*/