#include <bits/stdc++.h>
#include <cassert>

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
using FIO::wrtc;
using FIO::write;
using FIO::read;

typedef long long LL;
template<typename T> using minheap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

const int N = 2e5 + 5;

int n, m, K;

struct Submission {
	LL st, dura;
	int id;
};
bool operator==(const Submission &x, const Submission &y) { return x.st == y.st && x.dura == y.dura && x.id == y.id; }
std::vector<Submission> submsn[N];

LL ans[N];

struct cmp {
	bool operator()(int x, int y) const { return submsn[x].back().st > submsn[y].back().st; }
};
minheap<LL> machine, moments;
std::priority_queue<int, std::vector<int>, cmp> q;
minheap<std::pair<LL, int>> suspend;

int main() {
	int T; read(T);
	while(T--) {
		while(!machine.empty()) machine.pop();
		while(!q.empty()) q.pop();
		while(!suspend.empty()) suspend.pop();
		while(!q.empty()) q.pop();
		read(n), read(m), read(K);
		K = std::min(K, n);
		for(int i = 1; i <= n; i++) submsn[i].clear();
		for(int i = 1; i <= m; i++) {
			int a, b, c;
			read(a), read(b), read(c);
			submsn[a].push_back({b, c, i});
		}
		for(int i = 1; i <= n; i++) std::reverse(submsn[i].begin(), submsn[i].end());
		for(int i = 1; i <= n; i++) if(!submsn[i].empty()) q.push(i), moments.emplace(submsn[i].back().st);
		for(int i = 1; i <= K; i++) machine.emplace(0);
		moments.emplace(0);
		while(!moments.empty()) {
			LL now = moments.top();
			moments.pop();
			while(!suspend.empty() && suspend.top().first <= now) {
				int st = submsn[suspend.top().second].back().st;
				if(st > now) moments.emplace(st);
				q.emplace(suspend.top().second);
				suspend.pop();
			}
			bool hasmac = (!machine.empty() && machine.top() <= now);
			bool hassub = (!q.empty() && submsn[q.top()].back().st <= now);
			if(hasmac && hassub) {
				int team = q.top();
				auto &sub = submsn[team].back();
				q.pop(), machine.pop();
				ans[sub.id] = now;
				now += sub.dura;
				submsn[team].pop_back();
				if(!submsn[team].empty()) suspend.emplace(now, team);
				machine.emplace(now);
				moments.emplace(now);
			}
		}
		assert(q.empty()), assert(suspend.empty());
		for(int i = 1; i <= m; i++) write(ans[i], ' ');
		wrtc('\n');
	}
#ifdef DEBUG
	fprintf(stderr, "time = %.3fs\n", (double)clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}