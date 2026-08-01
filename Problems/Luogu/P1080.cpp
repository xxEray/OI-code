// Completed by DeepSeek V4 Flash
#include <bits/stdc++.h>

struct BigInt {
	std::vector<int> a;
	static const int BASE = 10000;

	BigInt() : a(1, 0) {}
	BigInt(int x) { *this = x; }

	BigInt& operator=(int x) {
		a.clear();
		do { a.push_back(x % BASE); x /= BASE; } while(x);
		return *this;
	}

	bool operator<(const BigInt &r) const {
		if(a.size() != r.a.size()) return a.size() < r.a.size();
		for(int i = (int)a.size() - 1; i >= 0; i--)
			if(a[i] != r.a[i]) return a[i] < r.a[i];
		return false;
	}

	BigInt operator*(int x) const {
		BigInt res; res.a.resize(a.size() + 5);
		long long carry = 0;
		for(size_t i = 0; i < a.size(); i++) {
			carry += (long long)a[i] * x;
			res.a[i] = carry % BASE;
			carry /= BASE;
		}
		int pos = (int)a.size();
		while(carry) { res.a[pos] = carry % BASE; carry /= BASE; pos++; }
		while(res.a.size() > 1 && res.a.back() == 0) res.a.pop_back();
		return res;
	}

	BigInt operator/(int x) const {
		BigInt res; res.a.resize(a.size());
		long long rem = 0;
		for(int i = (int)a.size() - 1; i >= 0; i--) {
			rem = rem * BASE + a[i];
			res.a[i] = (int)(rem / x);
			rem %= x;
		}
		while(res.a.size() > 1 && res.a.back() == 0) res.a.pop_back();
		return res;
	}

	void print() const {
		printf("%d", a.back());
		for(int i = (int)a.size() - 2; i >= 0; i--)
			printf("%04d", a[i]);
		putchar('\n');
	}
};

int main() {
	int n;
	scanf("%d", &n);
	std::vector<std::pair<int, int>> a(n + 1);
	for(int i = 0; i <= n; i++)
		scanf("%d%d", &a[i].first, &a[i].second);
	std::sort(a.begin() + 1, a.end(), [](auto x, auto y) {
		return (long long)x.first * x.second < (long long)y.first * y.second;
	});
	BigInt prod = a[0].first, ans = 0;
	for(int i = 1; i <= n; i++) {
		BigInt cur = prod / a[i].second;
		if(ans < cur) ans = cur;
		prod = prod * a[i].first;
	}
	ans.print();
	return 0;
}
