#include <cstdio>
#include <algorithm>
#include <deque>

typedef long long LL;

const int N = 5e4 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n;
LL L;
LL a[N], s[N];

LL f[N];

LL x_of(int i) { return 2 * s[i]; }
LL y_of(int i) { return f[i] + s[i] * s[i]; }
LL k_of(int i) { return s[i] - L - 1; }
LL extra_of(int i) { return (s[i] - L - 1) * (s[i] - L - 1); }
std::deque<int> q;

int main() {
	scanf("%d%lld", &n, &L);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), s[i] = s[i - 1] + a[i] + 1;
	q.push_back(0);
	for(int i = 1; i <= n; i++) {
		while(q.size() > 1 && k_of(i) * (x_of(q[1]) - x_of(q[0])) >= y_of(q[1]) - y_of(q[0])) q.pop_front();
		f[i] = y_of(q.front()) - k_of(i) * x_of(q.front()) + extra_of(i);
		while(q.size() > 1 && (y_of(q.back()) - y_of(q.end()[-2])) * (x_of(i) - x_of(q.back())) >= (y_of(i) - y_of(q.back())) * (x_of(q.back()) - x_of(q.end()[-2])))
			q.pop_back();
		q.push_back(i);
	}
	printf("%lld\n", f[n]);
	return 0;
} /*
f(i) = min(f(j) + (sum(i) - sum(j) - L - 1)^2)
*/