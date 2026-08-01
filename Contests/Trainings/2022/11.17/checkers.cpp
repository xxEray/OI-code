#include <bits/stdc++.h>

inline char rdc() {
	const int D = 1 << 23;
	static char buf[D], *p1, *p2;
	static std::streambuf *in = std::cin.rdbuf();
	return (p1 == p2 && (p2 = (p1 = buf) + in->sgetn(buf, D), p1 == p2) ? -1 : *p1++);
}
template<typename T> void read(T &x) {
	char c = rdc(), fl = 0;
	while(c < '0' || c > '9') fl |= (c == '-'), c = rdc();
	for(x = 0; '0' <= c && c <= '9'; c = rdc()) x = x * 10 + (c - '0');
    if(fl) x = -x;
}
inline void wrtc(char c) {
	static std::streambuf *out = std::cout.rdbuf();
	out->sputc(c);
}
template<typename T> void write(T x, char ch = 0) {
	static char c[60]; int top = 0;
    if(x < 0) wrtc('-'), x = -x;
	do c[++top] = x % 10, x /= 10; while(x);
	while(top) wrtc(c[top--] + '0');
	if(ch) wrtc(ch);
}

const int N = 1e5 + 5;

int n, m;
struct Node { int x, y; Node(int x_ = 0, int y_ = 0) : x(x_), y(y_) {} } a[N];
bool operator==(const Node &x, const Node &y) { return x.x == y.x && x.y == y.y; }

const int dir[6][2] = {{-1, -1}, {-1, 0}, {0, -1}, {1, 1}, {1, 0}, {0, 1}};
inline Node step(Node v, int d, int k) { return Node(v.x + k * dir[d][0], v.y + k * dir[d][1]); }

struct NodeHash {
	static unsigned long long splitmix64(unsigned long long x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}
	unsigned long long operator()(const Node &x) const {
		static const unsigned long long FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x.x + FIXED_RANDOM) ^ (splitmix64(x.y + FIXED_RANDOM) >> 1);
	}
};
std::unordered_map<Node, int, NodeHash> hash;
void discrete() {
	for(int i = 1; i <= n; i++) {
		hash.insert({a[i], 0});
		for(int d = 0; d < 6; d++) hash.insert({step(a[i], d, 1), 0});
	}
	for(auto &p : hash) p.second = ++m;
}

int id[N * 7], fa[N * 7], sz[N * 7];
int find(int x) { return x == fa[x] ? x : find(fa[x]); }
std::vector<std::array<int, 4>> op;
void merge(int x, int y) {
	x = find(x), y = find(y);
	if(x == y) { op.push_back({-1, -1, -1, -1}); return; }
	if(sz[x] > sz[y]) std::swap(x, y);
	op.push_back({x, fa[x], y, sz[y]});
	fa[x] = y, sz[y] += sz[x];
}
void undo() {
	assert(!op.empty());
	const auto &o = op.back();
	if(o[0] >= 0) fa[o[0]] = o[1], sz[o[2]] = o[3];
	op.pop_back();
}

int main() {
#ifndef DEBUG
	freopen("checkers.in", "r", stdin);
	freopen("checkers.out", "w", stdout);
#endif
	read(n);
	for(int i = 1; i <= n; i++) read(a[i].x), read(a[i].y);
	discrete();
	for(int i = 1; i <= n; i++) id[hash[a[i]]] = i;
	for(int i = 1; i <= m; i++) fa[i] = i, sz[i] = 1;
	for(int i = 1; i <= n; i++)
		for(int d = 0; d < 3; d++) {
			const int &h1 = hash[step(a[i], d, 1)], &h2 = hash[step(a[i], d, -1)];
			if(!id[h1] && !id[h2]) merge(h1, h2);
		}
	for(int i = 1; i <= n; i++) {
		int ret = 0, cnt = 0, entr = 0;
		for(int d = 0; d < 6; d++)
			if(id[hash[step(a[i], d, 1)]]) {
				const int &h = hash[step(a[i], d, 2)];
				if(!id[h]) entr ? (merge(entr, h), cnt++) : 0, entr = h;
			} else ret++;
		write(ret + (entr ? sz[find(entr)] : 0), '\n');
		while(cnt--) undo();
	}
	return 0;
}
