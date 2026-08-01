#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2e5 + 5;

int n;
int a[N];

std::vector<int> ans;

int main() {
	scanf("%d", &n);
	n *= 2;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n - 3; i += 2) {
		if(a[i] >= a[i + 1] && a[i] >= a[i + 2]) {
			std::swap(a[i], a[i + 1]), ans.push_back(i);
		} else if(a[i + 1] >= a[i] && a[i + 1] >= a[i + 2]);
		else {
			std::swap(a[i + 1], a[i + 2]), ans.push_back(i + 1);
		}
	}
	if(a[n - 1] > a[n]) std::swap(a[n - 1], a[n]), ans.push_back(n - 1);
	printf("%d\n", (int)ans.size());
	for(int v : ans) printf("%d ", v);
	puts("");
	return 0;
}