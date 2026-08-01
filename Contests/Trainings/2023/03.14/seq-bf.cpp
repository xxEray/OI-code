#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

int n, m, L, R, X, now;
int c[N], used[N], a[N], tot[N];
int ans, final_ans;
void update() {
	int ret = 0;
	for(int i = 1; i <= n; i++) {
		int mex = 0;
		for(int j = i; j <= n; j++) {
			tot[a[j]]++;
			while(tot[mex]) mex++;
			if(mex >= now) ret++;
		}
		for(int j = i; j <= n; j++) tot[a[j]]--;
	}
	ans = std::max(ans, ret);
	if(ret == final_ans) {
		for(int i = 1; i <= n; i++) printf("%d ", a[i]);
		puts("");
	}
}
void dfs(int id) {
	if(id == n + 1) { update(); return; }
	for(int i = 0; i < m; i++) if(used[i] < c[i]) {
		used[i]++, a[id] = i;
		dfs(id + 1);
		used[i]--;
	}
}

int main() {
	scanf("%d%d%d%d", &m, &L, &R, &X);
	for(int i = 0; i < m; i++) scanf("%1d", &c[i]), c[i] += X, n += c[i];
	now = R;
	final_ans = INF, dfs(1);
	printf("ans = %d\n", ans);
	final_ans = ans, dfs(1);
//	for(int i = L; i <= R; i++) {
//		ans = 0, now = i;
//		dfs(1);
//		printf("now=%d, ans=%d\n", now, ans);
//	}
	return 0;
}
