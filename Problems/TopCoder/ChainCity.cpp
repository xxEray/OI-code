// not done

#include <cstdio>
#include <algorithm>
#include <vector>
using std::vector;

const int N = 2000 + 5;

int a[N];
int n, m;
int ans = 0x3f3f3f3f;

bool check(int x) {
	int cnt = 0;
	for(int i = 1; i <= n;) {
		int j = std::upper_bound(a + 1, a + n + 1, a[i] + 2 * x) - a - 1;
		cnt++, i = j + 1;
	}
	printf("dis = %d, ans = %d\n", x, cnt);
	return cnt <= m;
}

void answer(int x) {
	int cnt = 0, ret1 = 0, ret2 = 0;
	for(int i = 1; i <= n;) {
		int j = std::upper_bound(a + 1, a + n + 1, a[i] + 2 * x) - a - 1;
		int r1 = (a[j] - a[i] + 1) / 2, r2 = (a[j] - a[i]) / 2;
		printf("r1 = %d, r2 = %d\n", r1, r2);
		if(ret1 <= r1) ret2 = std::max(ret1, r2), ret1 = r1;
		else ret2 = std::max(ret2, r1);
		cnt++, i = j + 1;
	}
	ans = std::min(ans, ret1 + ret2);
}

class ChainCity {
public:
	int findMin(vector<int> dist, int k_) {
		n = dist.size() + 1, m = k_;
		a[1] = 0;
		for(int i = 2; i <= n; i++) a[i] = a[i - 1] + dist[i - 2];
		int l = 0, r = a[n] - a[1];
		while(l < r) {
			puts("-----------------");
			int mid = (l + r) >> 1;
			if(check(mid)) { answer(mid), r = mid; }
			else l = mid + 1;
		}
		return ans;
	}
};

int main() {
	ChainCity T;
	printf("%d\n", T.findMin({3,5,4},
3));
	return 0;
}