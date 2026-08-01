#pragma pack(1)

#include <bits/stdc++.h>

namespace FIO {
	const int D = 1 << 23;
	char in[D], *I = in + D, out[D], *O = out;
	char rdc() { return (I == in + D ? fread(I = in, 1, D, stdin) : 0), *I++; }
	template<typename T> void read(T &x) {
		char c = rdc(), fl = 0;
		while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
		for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
		if(fl) x = -x;
	}
	void wrtc(char c) { (O == out + D ? fwrite(O = out, 1, D, stdout) : 0), *O++ = c; }
	template<typename T> void write(T x, char ch = 0) {
		static char c[60]; int top = 0;
		if(x < 0) wrtc('-'), x = -x;
		do c[++top] = x % 10, x /= 10; while(x);
		while(top) wrtc(c[top--] + '0');
		if(ch) wrtc(ch);
	}
	void flush() { fwrite(out, 1, O - out, stdout); }
	struct Flusher { ~Flusher() { flush(); } } flusher;
}
using FIO::write;
using FIO::read;

typedef long long LL;

const int N = 3e5 + 5;
const int M = 6e5 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;

int n, m;
LL a[N];
struct Query { LL add; int l, r, id; } qr[M];
int cq;

struct Node { LL pre, suf, mx, sum; };
Node calc(const Node &x, const Node &y) {
	Node z;
	z.sum = x.sum + y.sum;
	z.pre = std::max(x.sum + y.pre, x.pre);
	z.suf = std::max(y.sum + x.suf, y.suf);
	z.mx = std::max({x.mx, y.mx, x.suf + y.pre});
	return z;
}
Node out[M];

using Convex = std::vector<std::pair<int, LL>>;

std::vector<int> q[N << 2];
Convex mx[N << 2], pre, suf;
LL sum[N];
inline void get_conv_left(Convex &ret, LL *pl, LL *pr) {
	ret.clear(), ret.emplace_back(0, 0);
	LL sm = 0;
	for(int i = 1; pl != pr; i++) {
		sm += *pl--;
		while(ret.size() >= 2 && (sm - ret.back().second) * (ret.back().first - ret.end()[-2].first) >= (ret.back().second - ret.end()[-2].second) * (i - ret.back().first))
			ret.pop_back();
		ret.emplace_back(i, sm);
	}
}
inline void get_conv_right(Convex &ret, LL *pl, LL *pr) {
	ret.clear(), ret.emplace_back(0, 0);
	LL sm = 0;
	for(int i = 1; pl != pr; i++) {
		sm += *pl++;
		while(ret.size() >= 2 && (sm - ret.back().second) * (ret.back().first - ret.end()[-2].first) >= (ret.back().second - ret.end()[-2].second) * (i - ret.back().first))
			ret.pop_back();
		ret.emplace_back(i, sm);
	}
}
inline void conv_max(Convex &ret, Convex &another) {
	Convex vct(ret.size() + another.size());
	std::merge(ret.begin(), ret.end(), another.begin(), another.end(), vct.begin(),
		[&](const std::pair<int, LL> &x, const std::pair<int, LL> &y) { return x.first == y.first ? x.second > y.second : x.first < y.first; });
	another.clear(), another.shrink_to_fit();
	ret.clear();
	for(int i = 0; i < (int)vct.size(); i++) if(!i || vct[i].first != vct[i - 1].first) {
		auto [x, y] = vct[i];
		while(ret.size() >= 2 && (y - ret.back().second) * (ret.back().first - ret.end()[-2].first) >= (ret.back().second - ret.end()[-2].second) * (x - ret.back().first))
			ret.pop_back();
		ret.emplace_back(x, y);
	}
}
inline void minkowski(Convex &z, Convex &x, Convex &y) {
	// printf("x: "); for(LL v : x) printf("%lld ", v); puts("");
	// printf("y: "); for(LL v : y) printf("%lld ", v); puts("");
	for(int i = 0; i < (int)x.size() - 1; i++) x[i].first = x[i + 1].first - x[i].first, x[i].second = x[i + 1].second - x[i].second;
	for(int i = 0; i < (int)y.size() - 1; i++) y[i].first = y[i + 1].first - y[i].first, y[i].second = y[i + 1].second - y[i].second;
	z.resize(x.size() + y.size() + 1), z[0].first = 0, z[0].second = 0;
	std::merge(x.begin(), --x.end(), y.begin(), --y.end(), z.begin() + 1,
		[&](const std::pair<int, LL> &s, const std::pair<int, LL> &t) { return s.second * t.first > t.second * s.first; });
	for(int i = 1; i < (int)z.size(); i++) z[i].first += z[i - 1].first, z[i].second += z[i - 1].second;
	// printf("z: "); for(LL v : z) printf("%lld ", v); puts("");
}
inline void dfs(int x, int l, int r) {
	if(l == r) {
		for(int i : q[x]) {
			Node tmp;
			tmp.sum = a[l] + qr[i].add, tmp.pre = std::max(0LL, a[l] + qr[i].add), tmp.suf = std::max(0LL, a[l] + qr[i].add), tmp.mx = std::max(0LL, a[l] + qr[i].add);
			out[qr[i].id] = calc(out[qr[i].id], tmp);
		}
		q[x].clear(), q[x].shrink_to_fit();
		mx[x].resize(2), mx[x].emplace_back(0, 0), mx[x].emplace_back(1, a[l]);
		pre.clear(), pre.emplace_back(0, 0), pre.emplace_back(1, a[l]);
		return;
	}
	int mid = (l + r) >> 1;
	{
		std::vector<int> tmp;
		tmp.swap(q[x]);
		for(int i : tmp)
			if(qr[i].l <= l && r <= qr[i].r) q[x].emplace_back(i);
			else {
				if(qr[i].l <= mid) q[x << 1].emplace_back(i);
				if(qr[i].r > mid) q[x << 1 | 1].emplace_back(i);
			}
		q[x].shrink_to_fit();
	}
	dfs(x << 1, l, mid), dfs(x << 1 | 1, mid + 1, r);
	get_conv_left(suf, a + mid, a + l - 1);
	minkowski(mx[x], pre, suf);
	conv_max(mx[x], mx[x << 1]), conv_max(mx[x], mx[x << 1 | 1]);
	mx[x].shrink_to_fit();
	get_conv_right(pre, a + l, a + r + 1);
	get_conv_left(suf, a + r, a + l - 1);
	// printf("x=%d [%d, %d]:\n", x, l, r);
	// printf("  pre: "); for(auto [s, t] : pre) printf("(%d, %lld) ", s, t); puts("");
	// printf("  suf: "); for(auto [s, t] : suf) printf("(%d, %lld) ", s, t); puts("");
	// printf("  mx: "); for(auto [s, t] : mx[x]) printf("(%d, %lld) ", s, t); puts("");
	int pmx = 0, ppre = 0, psuf = 0;
	for(int i : q[x]) {
		while(pmx < (int)mx[x].size() - 1 && mx[x][pmx].second + mx[x][pmx].first * qr[i].add <= mx[x][pmx + 1].second + mx[x][pmx + 1].first * qr[i].add) pmx++;
		while(ppre < (int)pre.size() - 1 && pre[ppre].second + pre[ppre].first * qr[i].add <= pre[ppre + 1].second + pre[ppre + 1].first * qr[i].add) ppre++;
		while(psuf < (int)suf.size() - 1 && suf[psuf].second + suf[psuf].first * qr[i].add <= suf[psuf + 1].second + suf[psuf + 1].first * qr[i].add) psuf++;
		Node tmp;
		tmp.sum = sum[r] - sum[l - 1] + qr[i].add * (r - l + 1);
		tmp.pre = pre[ppre].second + pre[ppre].first * qr[i].add, tmp.suf = suf[psuf].second + suf[psuf].first * qr[i].add, tmp.mx = mx[x][pmx].second + mx[x][pmx].first * qr[i].add;
		out[qr[i].id] = calc(out[qr[i].id], tmp);
	}
	q[x].clear(), q[x].shrink_to_fit();
}

int main() {
	// freopen("T.in", "r", stdin);
	// freopen("T.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; i++) read(a[i]);
	pre.reserve(n), suf.reserve(n);
	LL sm = 0, minsum = 0;
	for(int i = 1; i <= m; i++) {
		int t, x, y;
		read(t);
		if(t == 1) read(x), sm += x;
		else read(x), read(y), cq++, qr[cq].add = sm, qr[cq].l = x, qr[cq].r = y, qr[cq].id = cq;
		minsum = std::min(minsum, sm);
	}
	for(int i = 1; i <= n; i++) a[i] += minsum;
	for(int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
	for(int i = 1; i <= cq; i++) qr[i].add -= minsum;
	std::sort(qr + 1, qr + cq + 1, [&](const Query &x, const Query &y) { return x.add < y.add; });
	for(int i = 1; i <= cq; i++) q[1].emplace_back(i);
	dfs(1, 1, n);
	for(int i = 1; i <= cq; i++) write(out[i].mx, '\n');
	return 0;
} /*
4 4
-1697303909 -1993062325 -1614488036 125110327 
1 -17972790
2 1 4
2 1 2
2 1 3
*/