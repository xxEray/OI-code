#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int N = 2e5 + 5;

LL tmp[N];
int n; LL m;
std::vector<int> a, b;
int la, lb;

bool check(int x, int y) {

}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &tmp[i]);
	scanf("%lld", &m);
	a.push_back(0), b.push_back(0);
	for(int i = 2; i <= n; i++) {
		int v = tmp[i] - tmp[i - 1];
		if(v & 1) b.push_back(v);
		else a.push_back(v);
	}
	la = (int)a.size() - 1, lb = (int)b.size() - 1;
	int l1 = 1, r1 = la;
	while(l1 < r1) {
		int mid1 = (l1 + r1) >> 1;
		int l2 = 1, r2 = lb + 1;
		while(l2 < r2) {
			int mid2 = (l2 + r2) >> 1;
			if(check(mid1, mid2)) l = mid + 1;
			else r = mid;
		}
		l2--;
		if(check(mid1, l2) && 
	}
	return 0;
}