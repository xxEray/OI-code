#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

typedef long long LL;

const int N = 1e4 + 5;

struct bign {
	std::vector<int> w;
	bign() { w.push_back(0); }
	bign(int x) { *this = x; }
	bign(const bign &x) { *this = x; }
	void trim() {
		while(!w.empty() && w.back() == 0) w.pop_back();
		if(w.empty()) w.push_back(0);
	}
	bign &operator=(int x) {
		w.clear();
		while(x) w.push_back(x % 10), x /= 10;
		trim();
		return *this;
	}
	bign &operator+=(const bign &x);
	bign &operator-=(const bign &x);
	void print() {
		for(auto it = w.rbegin(); it != w.rend(); it++) printf("%d", *it);
	}
};
bign operator+(const bign &x, const bign &y) {
	bign z;
	int len = std::max(x.w.size(), y.w.size());
	for(int i = 0; i < len; i++) {
		int t = z.w[i];
		if((int)x.w.size() > i) t += x.w[i];
		if((int)y.w.size() > i) t += y.w[i];
		z.w[i] = t % 10;
		z.w.push_back(t / 10);
	}
	z.trim();
	return z;
}
bign operator-(const bign &x, const bign &y) {
	bign z;
	for(int i = 0; i < (int)x.w.size(); i++) {
		int t = z.w[i] + x.w[i];
		if((int)y.w.size() > i) t -= y.w[i];
		if(t < 0) z.w.push_back(-1), t += 10;
		else z.w.push_back(0);
		z.w[i] = t;
	}
	z.trim();
	return z;
}
bign &bign::operator+=(const bign &x) { return *this = *this + x; }
bign &bign::operator-=(const bign &x) { return *this = *this - x; }

int n, m;

bign f[N];

int main() {
	scanf("%d%d", &n, &m);
	f[0] = f[1] = 1;
	for(int i = 2; i <= n + 1; i++)
		f[i] = f[i - 1] + f[i - 1] - (i - m - 2 >= 0 ? f[i - m - 2] : 0);
	f[n + 1].print();
	// printf("%lld\n", f[n + 1]);
	return 0;
}