#include <bits/stdc++.h>
#include <cassert>

typedef long long LL;

const int N = 2e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;
int a[N], b[N];

int mod(int x) {
	if(x < 0) x += m;
	if(x >= m) x -= m;
	assert(0 <= x && x < m);
	return x;
}

int target[N];

int tmp[N * 8], val[N * 8], mx;
std::vector<std::array<int, 4>> seq;
void discrete() {
	for(auto [l, r, v0, v1] : seq) tmp[++mx] = l, tmp[++mx] = r;
	std::sort(tmp + 1, tmp + mx + 1);
	mx = std::unique(tmp + 1, tmp + mx + 1) - tmp - 1;
	for(auto &[l, r, v0, v1] : seq) {
		int dl = std::lower_bound(tmp + 1, tmp + mx + 1, l) - tmp;
		int dr = std::lower_bound(tmp + 1, tmp + mx + 1, r) - tmp;
		val[dl] = l, l = dl;
		val[dr] = r, r = dr;
	}
}
struct BIT {
	LL t[N * 6];
	void add(int x, LL v) { while(x <= mx) t[x] += v, x += x & -x; }
	void add(int l, int r, LL v) { add(l, v), add(r + 1, -v); }
	LL query(int r) { LL ret = 0; while(r) ret += t[r], r -= r & -r; return ret; }
} bit0, bit1;

void perform(std::function<void(int, int, int, int)> func) {
	for(int i = 1; i <= n; i++) {
		if(i & 1) { // target[i] + x
			auto updt = [=](int l, int r) {
				int stepa = mod(l - a[i]), stept = mod(l - target[i]);
				assert(stept + (r - l) < m);
				func(stept, stept + r - l, stepa - stept, 1);
			};
			if(a[i] >= target[i]) {
				updt(target[i], a[i] - 1), updt(a[i], m - 1), updt(0, target[i] - 1);
			} else {
				updt(target[i], m - 1), updt(0, a[i] - 1), updt(a[i], target[i] - 1);
			}
		} else { // target[i] - x
			auto updt = [=](int l, int r) { // l < r
				int stepa = mod(l - a[i]), stept = mod(target[i] - l);
				assert(stept - (r - l) >= 0);
				func(stept - (r - l), stept, stepa + stept, -1);
			};
			if(a[i] > target[i]) {
				updt(0, target[i]), updt(a[i], m - 1), updt(target[i] + 1, a[i] - 1);
			} else {
				updt(a[i], target[i]), updt(0, a[i] - 1), updt(target[i] + 1, m - 1);
			}
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n - 1; i++) scanf("%d", &b[i]);
	target[1] = 0; // 0 + x
	for(int i = 2; i <= n; i++) target[i] = mod(b[i - 1] - target[i - 1]);
	perform([&](int l, int r, int v0, int v1) {
		if(l > r) return;
		seq.push_back({l, r, v0, v1});
		// printf("add [%d, %d] += %d..%d\n", l, r, v0 + v1 * l, v0 + v1 * r);
	});
	discrete();
	for(auto [l, r, v0, v1] : seq) {
		bit0.add(l, r, v0);
		bit1.add(l, r, v1);
	}
	LL ans = LLINF;
	// for(int i = 1; i <= mx; i++) printf("[%d]=%lld\n", val[i], bit0.query(i) + val[i] * bit1.query(i));
	for(int i = 1; i <= mx; i++) ans = std::min(ans, bit0.query(i) + val[i] * bit1.query(i));
	printf("%lld\n", ans);
	return 0;
}