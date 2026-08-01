#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2e5 + 5;

int n;
int a[N];

int cnt[1000];
bool remain[N];

std::vector<int> vct, pst, ngt;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) {
		if(-10 <= a[i] && a[i] <= 10 && cnt[a[i] + 10] < 3) cnt[a[i] + 10]++, remain[i] = true;
		if(a[i] > 0) pst.push_back(i);
		else ngt.push_back(i);
	}
	std::sort(pst.begin(), pst.end(), [&](int x, int y) { return a[x] < a[y]; });
	std::sort(ngt.begin(), ngt.end(), [&](int x, int y) { return a[x] < a[y]; });
	for(int i = 0; i < std::min((int)pst.size(), 10); i++) remain[pst[i]] = remain[pst.rbegin()[i]] = true;
	for(int i = 0; i < std::min((int)ngt.size(), 10); i++) remain[ngt[i]] = remain[ngt.rbegin()[i]] = true;
	for(int i = 1; i <= n; i++) if(remain[i]) vct.push_back(a[i]);
	// for(int i : vct) printf("%d ", i);
	// puts("");
	double mn = 1e18, mx = -1e18;
	for(int i = 0; i < (int)vct.size(); i++) for(int j = i + 1; j < (int)vct.size(); j++) for(int k = j + 1; k < (int)vct.size(); k++) {
		double v = (vct[i] + vct[j] + vct[k]) / ((double)(vct[i] * vct[j] * vct[k]));
		mn = std::min(mn, v), mx = std::max(mx, v);
	}
	printf("%.12f\n%.12f\n", mn, mx);
	return 0;
}