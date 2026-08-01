#include <cstdio>
#include <algorithm>
#include <deque>

typedef long long LL;

const int N = 3e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n;
LL S;
LL sumc[N], sumt[N];

LL f[N];

std::deque<std::pair<LL, LL>> q;

// -x = -sumc[j], y = f[j] - sumt[j] * sumc[n] + sumc[j] * sumt[j] - sumc[j] * S, k = sumt[i], extra = sumc[n] * sumt[i] + S * sumc[n]
inline LL xof(int j) { return sumc[j]; }
inline LL yof(int j) { return f[j] - sumt[j] * sumc[n] + sumc[j] * sumt[j] - sumc[j] * S; }
inline LL kof(int i) { return sumt[i]; }
inline LL extra(int i) { return sumc[n] * sumt[i] + S * sumc[n]; }

bool compare(LL x, LL y, LL k) { return (x > k * y) ^ (y < 0); }
bool compare(LL x1, LL y1, LL x2, LL y2) { return y2 == 0 ? x2 > 0 : (((__int128_t)x1 * y2 < (__int128_t)x2 * y1) ^ (y1 < 0) ^ (y2 < 0)); }

int main() {
	scanf("%d%lld", &n, &S);
	for(int i = 1; i <= n; i++) scanf("%lld%lld", &sumt[i], &sumc[i]), sumt[i] += sumt[i - 1], sumc[i] += sumc[i - 1];
	for(int i = 1; i <= n; i++) f[i] = LLINF;
	// for(int i = 1; i <= n; i++) for(int j = 0; j < i; j++) f[i] = std::min(f[i], yof(j) - kof(i) * xof(j) + extra(i));
	q.push_back({xof(0), yof(0)});
	for(int i = 1; i <= n; i++) {
		while(q.size() >= 2 && !compare(q[0].second - q[1].second, q[0].first - q[1].first, kof(i))) q.pop_front();
		f[i] = q[0].second - kof(i) * q[0].first + extra(i);
		while(q.size() >= 2 && !compare(q.end()[-2].second - q.back().second, q.end()[-2].first - q.back().first, q.back().second - yof(i), q.back().first - xof(i))) q.pop_back();
		q.push_back({xof(i), yof(i)});
	}
	printf("%lld\n", f[n]);
	return 0;
}