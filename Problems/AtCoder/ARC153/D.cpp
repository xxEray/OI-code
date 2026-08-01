#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;

int n;

struct Node { int v[11]; } a[N];

int f[11][N];

std::vector<Node> d[11];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		for(int j = 0; j <= 9; j++) {
			a[i].v[j] = x % 10;
			x /= 10;
		}
		for(int j = 0; j <= 9; j++) d[j].push_back(a[i]);
	}
	for(int j = 0; j <= 9; j++) std::sort(d[j].begin(), d[j].end(), [&](Node x, Node y) { return x.v[j] == y.v[j] ? x.v[j + 1] > y.v[j + 1] : x.v[j] > y.v[j]; });
	memset(f, 0x3f, sizeof(f));
	{
		int cnt[11] = {};
		for(int i = 1; i <= n; i++) cnt[a[i].v[0]]++;
		int extra = 0;
		int sum = 0;
		for(int k = 0; k <= 9; k++) sum += cnt[k] * k;
		for(int k = 0; k <= 9; k++) {
			extra += cnt[10 - k];
			sum -= cnt[10 - k] * 10;
			f[0][extra] = std::min(f[0][extra], sum + k * n);
		}
	}
	for(int j = 0; j <= 8; j++) {
		int cnt[11] = {};
		for(int i = 1; i <= n; i++) cnt[a[i].v[j + 1]]++;
		int ex = 0;
		for(int i = 0; i <= n; i++) {
			int extra = ex;
			int sum = 0;
			for(int k = 0; k <= 9; k++) sum += cnt[k] * k;
			for(int k = 0; k <= 9; k++) {
				extra += cnt[10 - k];
				sum -= cnt[10 - k] * 10;
				f[j + 1][extra] = std::min(f[j + 1][extra], f[j][i] + sum + k * n);
			}
			if(i < n) {
				cnt[d[j][i].v[j + 1]]--, cnt[(d[j][i].v[j + 1] + 1) % 10]++;
				if(d[j][i].v[j + 1] == 9) ex++;
			}
		}
	}
	// for(int j = 0; j <= 9; j++) for(int i = 0; i <= n; i++) if(f[j][i] < INF) printf("f[%d][%d] = %d\n", j, i, f[j][i]);
	int ans = INF;
	for(int i = 0; i <= n; i++) ans = std::min(ans, f[9][i] + i);
	printf("%d\n", ans);
	return 0;
} /*
1
11
*/