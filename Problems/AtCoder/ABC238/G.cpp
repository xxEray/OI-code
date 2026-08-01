#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

typedef long long LL;

const int N = 2e5 + 5;

int a[N], copy[N];
int n, m;

bool isprm[N];
std::vector<int> prime;
void sieve() {
	int maxn = 2e5;
	for(int i = 2; i <= maxn; i++) isprm[i] = true;
	for(int i = 2; i <= maxn; i++) if(isprm[i]) {
		prime.push_back(i);
		for(int j = i + i; j <= maxn; j += i) isprm[j] = false;
	}
}

int cnt[N];
std::vector<std::pair<int, int>> divisor[N];
std::set<int> occur[N][3];

int out[N];
struct Query { int l, r, id; } q[N];
bool operator<(Query x, Query y) { return x.r < y.r; }

#define exist(container, element) ((container).find((element)) != (container).end())

int main() {
	sieve();
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
		// Attention: copy[r] = 1
		while(q[i].r >= q[i].l && copy[q[i].r] == 1) q[i].r--;
		if(q[i].l > q[i].r) out[q[i].id] = true;
	}
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]), copy[i] = a[i];
		for(int p : prime) {
			if((LL)p * p > a[i]) break;
			if(a[i] % p) continue;
			// printf("%d: %d", i, p);
			divisor[i].push_back({p, cnt[p]});
			while(a[i] % p == 0) (cnt[p] += 1) %= 3, a[i] /= p;
			occur[p][cnt[p]].insert(i), printf("occur[%d][%d].insert(%d)\n", p, cnt[p], i);
			// puts("");
		}
		if(isprm[a[i]]) { // 1 is not a prime
			// printf("%d: %d .\n", i, a[i]);
			divisor[i].push_back({a[i], cnt[a[i]]});
			(cnt[a[i]] += 1) %= 3;
			occur[a[i]][cnt[a[i]]].insert(i), printf("occur[%d][%d].insert(%d)\n", a[i], cnt[a[i]], i);
		}
	}
	for(int i = 1; i <= n; i++) puts(out[i] ? "Yes" : "No");
	return 0;
}