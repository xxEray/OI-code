#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int n;
int a[5][N], b[N];

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y : 0; }

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= 3; i++) for(int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
	bool flag = true;
	for(int i = 1; i <= n; i++) flag &= (a[2][i] % 3 == 2 && std::abs(a[1][i] - a[2][i]) == 1 && std::abs(a[3][i] - a[2][i]) == 1);
	for(int i = 1; i <= n; i++) flag &= (a[2][i] / 3 % 2 == !(i & 1));
	for(int i = 1; i <= n; i++) for(int j = 1; j <= 3; j += 2) flag &= (a[j][i] % 2 == i % 2);
	int sum1 = 0, sum2 = 0;
	for(int i = 1; i <= n; i++) fa[i] = i, b[i] = (a[2][i] / 3 + 1), ((i & 1) ? sum1 : sum2) += (a[1][i] == a[2][i] - 1 ? 0 : 1);
	for(int i = 1; i <= n; i++) merge(i, b[i]);
	int cnt1 = (n + 1) / 2, cnt2 = n / 2;
	for(int i = 1; i <= n; i += 2) cnt1 -= (find(i) == i);
	for(int i = 2; i <= n; i += 2) cnt2 -= (find(i) == i);
	flag &= ((cnt1 & 1) == (sum2 & 1) && (cnt2 & 1) == (sum1 & 1));
	puts(flag ? "Yes" : "No");
	return 0;
}