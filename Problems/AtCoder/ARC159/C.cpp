#include <cstdio>
#include <algorithm>
#include <vector>
#include <array>
#include <cassert>

const int N = 50 + 5;

int n;

int a[N];

std::vector<std::array<int, N>> ans;
void operate(int x, int y) {
	ans.push_back({});
	ans.back()[x] = 1, ans.back()[y] = 2;
	int c = 2;
	for(int i = 1; i <= n; i++) if(!ans.back()[i]) ans.back()[i] = ++c;
	ans.push_back({});
	for(int i = 1; i <= n; i++) ans.back()[i] = n + 1 - ans.end()[-2][i];
	ans.back()[x] = n - 1, ans.back()[y] = n;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int sum = 0;
	for(int i = 1; i <= n; i++) sum += a[i];
	if(sum % n) {
		ans.push_back({});
		for(int i = 1; i <= n; i++) ans.back()[i] = i;
		for(int i = 1; i <= n; i++) a[i] += i, sum += i;
	}
	if(sum % n) { puts("No"); return 0; }
	puts("Yes");
	int target = sum / n;
	std::vector<int> toadd, tosub;
	for(int i = 1; i <= n; i++)
		if(a[i] < target) toadd.push_back(i);
		else if(a[i] > target) tosub.push_back(i);
	while(!toadd.empty()) {
		assert(!tosub.empty());
		operate(tosub.back(), toadd.back());
		a[tosub.back()]--;
		if(a[tosub.back()] == target) tosub.pop_back();
		a[toadd.back()]++;
		if(a[toadd.back()] == target) toadd.pop_back();
	}
	assert(ans.size() <= 10000);
	printf("%d\n", (int)ans.size());
	for(auto p : ans) {
		for(int i = 1; i <= n; i++) printf("%d ", p[i]);
		puts("");
	}
	return 0;
}