#include <bits/stdc++.h>

void ensorted(int &a, int &b, int &c, int &d) {
	if(a > b) std::swap(a, b);
	if(a > c) std::swap(a, c);
	if(a > d) std::swap(a, d);
	if(b > c) std::swap(b, c);
	if(b > d) std::swap(b, d);
	if(c > d) std::swap(c, d);
}

std::set<std::array<int, 4>> barrier;
std::map<std::array<int, 4>, int> mp;
int SG(int a, int b, int c, int d) {
	if(!a && !b && !c && !d) return 0;
	if(mp.count({a, b, c, d})) return mp[{a, b, c, d}];
	if(barrier.count({a, b, c, d})) return mp[{a, b, c, d}] = 0;
	std::vector<int> vct;
	for(int i = a - 1; i >= 0; i--)
		if(barrier.count({i, b, c, d})) break;
		else vct.emplace_back(SG(i, b, c, d));
	for(int i = b - 1; i >= 0; i--)
		if(barrier.count({a, i, c, d})) break;
		else vct.emplace_back(SG(a, i, c, d));
	for(int i = c - 1; i >= 0; i--)
		if(barrier.count({a, b, i, d})) break;
		else vct.emplace_back(SG(a, b, i, d));
	for(int i = d - 1; i >= 0; i--)
		if(barrier.count({a, b, c, i})) break;
		else vct.emplace_back(SG(a, b, c, i));
	std::sort(vct.begin(), vct.end());
	vct.erase(std::unique(vct.begin(), vct.end()), vct.end());
	int mex = -1;
	if(vct.empty() || vct.front() > 0) mex = 0;
	else {
		for(int i = 0; i < (int)vct.size() - 1; i++) if(vct[i + 1] - vct[i] > 1) { mex = vct[i] + 1; break; }
		if(mex == -1) mex = vct.back() + 1;
	}
	return mp[{a, b, c, d}] = mex;
}

int n;

void set_barrier() {
	int a = rand() % n, b = rand() % n, c = rand() % n, d = rand() % n;
	printf("barrier: (%d, %d, %d, %d)\n", a, b, c, d);
	barrier.insert({a, b, c, d});
}

int main() {
	freopen("out.txt", "w", stdout);
	srand(time(0));
	n = 5;
	barrier.insert({1, 1, 4, 5});
	barrier.insert({1, 4, 1, 1});
	barrier.insert({4, 5, 1, 4});
	// set_barrier();
	for(int a = 0; a <= n; a++)
		for(int b = 0; b <= n; b++)
			for(int c = 0; c <= n; c++)
				for(int d = 0; d <= n; d++) {
					int sg = SG(a, b, c, d);
					if(sg != (a ^ b ^ c ^ d)) printf("SG(%d, %d, %d, %d) = %d (%d)\n", a, b, c, d, sg, a ^ b ^ c ^ d);
				}
	return 0;
}