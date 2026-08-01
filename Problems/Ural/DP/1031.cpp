#include <cstdio>
#include <deque>

typedef long long LL;

const int N = 1e4 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

LL L0 = 0, L1, L2, L3, C1, C2, C3;
int st, ed, n;
LL a[N];
LL f[N];
std::deque<int> q1, q2, q3;

int main() {
	scanf("%lld%lld%lld%lld%lld%lld", &L1, &L2, &L3, &C1, &C2, &C3);
	scanf("%d%d%d", &n, &st, &ed);
	if(ed < st) std::swap(st, ed);
	a[1] = 0;
	for(int i = 2; i <= n; i++) scanf("%lld", &a[i]);
	f[st] = 0;
	q1.push_back(st), q2.push_back(st), q3.push_back(st);
	for(int i = st + 1; i <= ed; i++) {
		while(!q1.empty() && a[q1.front()] < a[i] - L1) q1.pop_front();
		while(!q2.empty() && a[q2.front()] < a[i] - L2) q2.pop_front();
		while(!q3.empty() && a[q3.front()] < a[i] - L3) q3.pop_front();
		f[i] = LLINF;
		if(!q1.empty()) f[i] = std::min(f[i], f[q1.front()] + C1);
		if(!q2.empty()) f[i] = std::min(f[i], f[q2.front()] + C2);
		if(!q3.empty()) f[i] = std::min(f[i], f[q3.front()] + C3);
		// printf("\n#%d\nq1: ", i);
		// for(int x : q1) printf("%d ", x);
		// printf("\nq2: ");
		// for(int x : q2) printf("%d ", x);
		// printf("\nq3: ");
		// for(int x : q3) printf("%d ", x);
		// printf("\nf = %lld\n", f[i]);
		q1.push_back(i), q2.push_back(i), q3.push_back(i);
	}
	printf("%lld\n", f[ed]);
	return 0;
} /*
3 6 8 20 30 40
7
1 6
3 7 8 13 15 23
*/