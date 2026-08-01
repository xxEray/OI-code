#include <cstdio>
#include <algorithm>
#include <map>
#include <cassert>

typedef long long LL;

const int N = 400 + 5;
const LL MOD = 998244353;
const LL inv6 = (MOD + 1) / 6;
const LL inv24 = (7 * MOD + 1) / 24;

int n;
LL m;
LL l[N], r[N];

LL calc_aaaa() {
	if(m % 4) return 0;
	bool flag = false;
	for(int i = 1; i <= n; i++) flag |= (l[i] <= m / 4 && m / 4 <= r[i]);
	// printf("aaaa: %lld\n", (LL)flag);
	return flag;
}

LL calc_aaab() {
	LL ans = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) {
		LL l0 = m - r[j], r0 = m - l[j];
		l0 = std::max(l0, l[i] * 3), r0 = std::min(r0, r[i] * 3);
		while(l0 % 3) l0++;
		while(r0 % 3) r0--;
		l0 /= 3, r0 /= 3;
		if(l0 > r0) continue;
		(ans += r0 - l0 + 1) %= MOD;
	}
	// printf("aaab: %lld\n", ans);
	return ans;
}

LL calc_aabb() {
	if(m & 1) return 0;
	LL ans = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) {
		LL l0 = m / 2 - r[i], r0 = m / 2 - l[i];
		l0 = std::max(l0, l[j]), r0 = std::min(r0, r[j]);
		if(l0 > r0) continue;
		(ans += r0 - l0 + 1) %= MOD;
	}
	// printf("aabb: %lld\n", ans);
	return ans;
}

struct Node { LL k, b, l, r; } t[N * N * 4];

// \sum_{x=L}^R ax^2 + bx + c
LL sum(LL a, LL b, LL c, LL L, LL R) {
	LL sx2 = a * (R * (R + 1) % MOD * (2 * R + 1) % MOD * inv6 % MOD - (L ? (L - 1) % MOD * L % MOD * (2 * L - 1) % MOD * inv6 % MOD : 0) + MOD) % MOD;
	LL sx1 = b * ((L + R) * (R - L + 1) / 2 % MOD) % MOD;
	LL sx0 = c * (R - L + 1) % MOD;
	// printf("sum(%lld, %lld, %lld, %lld, %lld) = %lld\n", a, b, c, L, R, (sx0 + sx1 + sx2) % MOD);
	return (sx0 + sx1 + sx2) % MOD;
}

int c = 0;
void preprocess() {
	std::map<LL, int> mp;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) {
		int mnl = std::min(r[i] - l[i], r[j] - l[j]);
		mp.insert({l[i] + l[j], 0});
		mp.insert({std::min(l[i] + l[j] + mnl + 1, r[i] + r[j] - mnl), 0});
		mp.insert({r[i] + r[j] - mnl, 0});
		mp.insert({r[i] + r[j] + 1, 0});
		// printf("y=x%+lld {%.4lf<x<%.4lf}\n", 1 - l[i] - l[j], l[i] + l[j] - 0.0001, std::min(l[i] + l[j] + mnl, r[i] + r[j] - mnl - 1) + 0.0001);
		// if(l[i] + l[j] + mnl + 1 <= r[i] + r[j] - mnl - 1)
		// 	printf("y=%lld {%.4lf<x<%.4lf}\n", 1LL + mnl, l[i] + l[j] + mnl + 1 - 0.0001, r[i] + r[j] - mnl - 1 + 0.0001);
		// printf("y=-x%+lld {%.4lf<x<%.4lf}\n", 1 + r[i] + r[j], r[i] + r[j] - mnl - 0.0001, r[i] + r[j] + 0.0001);
	}
	int cnt = 0;
	for(auto &p : mp) p.second = ++cnt;
	auto it = mp.begin();
	for(int i = 1; i < cnt; i++, it++) t[i].l = it->first, t[i].r = std::next(it)->first - 1; // printf("t[%d]: [%lld, %lld]\n", i, t[i].l, t[i].r);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) {
		int mnl = std::min(r[i] - l[i], r[j] - l[j]);
		int il = mp[l[i] + l[j]], iml = mp[std::min(l[i] + l[j] + mnl + 1, r[i] + r[j] - mnl)], imr = mp[r[i] + r[j] - mnl], ir = mp[r[i] + r[j] + 1];
		(t[il].k += 1) %= MOD, (t[iml].k += MOD - 1) %= MOD;
		(t[il].b += 1 - l[i] - l[j] + 2 * MOD) %= MOD, (t[iml].b += MOD - 1 + l[i] + l[j]) %= MOD;
		if(l[i] + l[j] + mnl + 1 <= r[i] + r[j] - mnl - 1) (t[iml].b += mnl + 1) %= MOD, (t[imr].b += 2 * MOD - mnl - 1) %= MOD;
		(t[imr].k += MOD - 1) %= MOD, (t[ir].k += 1) %= MOD;
		(t[imr].b += 1 + r[i] + r[j]) %= MOD, (t[ir].b += 3 * MOD - 1 - r[i] - r[j]) %= MOD;
	}
	for(int i = 1; i <= cnt; i++) (t[i].b += t[i - 1].b) %= MOD, (t[i].k += t[i - 1].k) %= MOD;
	for(int i = 1; i <= cnt; i++) if(t[i].b || t[i].k) t[++c] = t[i];
	// for(int i = 1; i <= c; i++) printf("y=%lldx%+lld {%.4lf<x<%.4lf}\n", t[i].k, t[i].b, t[i].l - 0.0001, t[i].r + 0.0001);
}

LL calc_aabc() {
	LL ans = 0;
	for(int i = 1, j = c; i <= n && j >= 1; i++) {
		while(j >= 1 && 2 * l[i] + t[j].l > m) j--;
		while(j >= 1 && 2 * l[i] + t[j].l <= m && m <= 2 * r[i] + t[j].r) {
			LL l0 = m - 2 * r[i], r0 = m - 2 * l[i], o = (m & 1);
			l0 = std::max(l0, t[j].l), r0 = std::min(r0, t[j].r);
			while(l0 % 2 != o) l0++;
			while(r0 >= 0 && r0 % 2 != o) r0--;
			if(l0 <= r0) {
				if(o) (ans += sum(0, 2 * t[j].k % MOD, (t[j].k + t[j].b) % MOD, (l0 - 1) / 2, (r0 - 1) / 2)) %= MOD;
				else (ans += sum(0, 2 * t[j].k % MOD, t[j].b, l0 / 2, r0 / 2)) %= MOD;
			}
			if(j >= 1 && 2 * l[i] + t[j - 1].l <= m && m <= 2 * r[i] + t[j - 1].r) j--;
			else break;
		}
	}
	// printf("aabc: %lld\n", ans);
	return ans;
}

LL calc_abcd() {
	LL ans = 0;
	for(int i = 1, j = c; i <= c && j >= 1; i++) {
		while(j >= 1 && t[i].l + t[j].l > m) j--;
		while(j >= 1 && t[i].l + t[j].l <= m && m <= t[i].r + t[j].r) {
			LL l0 = m - t[i].r, r0 = m - t[i].l;
			l0 = std::max(l0, t[j].l), r0 = std::min(r0, t[j].r);
			assert(l0 <= r0);
			LL ca = MOD - t[i].k * t[j].k % MOD;
			LL cb = (MOD - t[i].k * t[j].b % MOD + t[i].b * t[j].k % MOD + t[i].k * t[j].k % MOD * m % MOD) % MOD;
			LL cc = (t[i].k * t[j].b % MOD * m % MOD + t[i].b * t[j].b % MOD) % MOD;
			(ans += sum(ca, cb, cc, l0, r0)) %= MOD;
			if(j >= 1 && t[i].l + t[j - 1].l <= m && m <= t[i].r + t[j - 1].r) j--;
			else break;
		}
	}
	// printf("abcd: %lld\n", ans);
	return ans;
}

int main() {
	scanf("%d%lld", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld%lld", &l[i], &r[i]);
	preprocess();
	LL ans = calc_abcd() - 6 * calc_aabc() + 3 * calc_aabb() + 8 * calc_aaab() - 6 * calc_aaaa();
	ans = (ans % MOD + MOD) % MOD;
	// printf("ans=%lld/24=", ans);
	printf("%lld\n", ans * inv24 % MOD);
	return 0;
} /*
2 8
0 3
5 5
*/