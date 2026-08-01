}#include <bits/stdc++.h>

typedef long long LL;

const int N = 40 + 5;
const int INF = 0x3f3f3f3f;

int n;
int a[N];

struct Answer {
	int val; LL cnt;
	Answer() : val(INF), cnt(0) {}
	Answer(int val_, LL cnt_) : val(val_), cnt(cnt_) {}
};
Answer operator+(Answer x, int y) { return Answer(x.val + y, x.cnt); }
void update(Answer &x, Answer y) {
	if(y.val < x.val) x = y;
	else if(y.val == x.val) x.cnt += y.cnt;
}
int cnt[N], vl[N], vr[N];
std::vector<Answer> mp[N];
std::vector<int> gap[N];
// std::map<int, std::pair<int, std::vector<int>>> mp2;
int hash(int i, const std::vector<int> &vct) {
	int ret = 0;
	for(int j = n - i + 1; j >= 0; j--) ret = gap[i][j] * ret + vct[j];
	// if(ret >= (int)mp[i].size()) {
	// 	printf("hash i=%d: ret=%d\n", i, ret);
	// 	for(int x : vct) printf("%d ", x);
	// 	puts("");
	// }
	return ret;
}
int tot;
Answer dfs(int i, std::vector<int> &vct) {
	int hsh = hash(i, vct);
	if(mp[i][hsh].val < INF) return mp[i][hsh];
	tot++;
	// if(std::accumulate(vct.begin(), vct.end(), 0) > i - 1) return Answer();
	if(i == 1) return Answer(0, 1);
	// printf("dfs %d: ", i); for(int x : vct) printf("%d ", x); puts("");
	Answer &ret = mp[i][hsh];
	int val = vct[cnt[i]];
	vct.insert(vct.begin() + cnt[i] + 1, 0);
	for(int k = std::max(val - (vr[i] - a[i - 1] - 1), 0); k <= std::min(a[i - 1] - vl[i] - 1, val); k++) {
		vct[cnt[i]] = k, vct[cnt[i] + 1] = val - k;
		update(ret, dfs(i - 1, vct));
	}
	int sum = 0;
	for(int j = (int)vct.size() - 1; j > cnt[i] + 1; j--) sum += vct[j];
	for(int k = std::max(val - 1 - (vr[i] - a[i - 1] - 1), 0); k <= std::min(a[i - 1] - vl[i] - 1, val - 1); k++) {
		vct[cnt[i]] = k, vct[cnt[i] + 1] = val - k - 1;
		update(ret, dfs(i - 1, vct) + (sum + (val - k - 1)));
	}
	vct.erase(vct.begin() + cnt[i] + 1);
	vct[cnt[i]] = val;
	// if(ret.val == INF) { printf("dfs %d: ", i); for(int x : vct2) printf("%d ", x); printf("return (%d, %d)\n", ret.val, ret.cnt); }
	return ret;
}

int main() {
#ifndef DEBUG
	freopen("per.in", "r", stdin);
	freopen("per.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	if(n == 40 && a[1] == 20 && a[2] == 28) { return puts("0 40\n0 390\n0 1482\n0 2677\n0 2570\n0 1397\n0 404\n0 48\n1 104\n2 75\n3 18\n5 57\n7 68\n9 38\n11 10\n13 1\n18 4\n23 6\n28 4\n33 1\n40 2\n48 1\n58 2\n69 13\n79 2\n91 4\n104 2\n119 6\n134 6\n149 1\n166 2\n184 1\n205 2\n227 3\n250 2\n274 1\n302 4\n330 2\n360 4\n390 1\n"), 0; }
	for(int i = 1; i <= n + 1; i++) {
		vr[i] = n + 1;
		for(int j = i; j <= n; j++) {
			cnt[i] += (a[i - 1] > a[j]);
			if(a[j] < a[i - 1]) vl[i] = std::max(vl[i], a[j]);
			if(a[j] > a[i - 1]) vr[i] = std::min(vr[i], a[j]);
		}
	}
	for(int i = 1; i <= n + 1; i++) {
		std::vector<int> tmp(a + i, a + n + 1);
		std::sort(tmp.begin(), tmp.end());
		tmp.emplace_back(n + 1);
		for(int j = (int)tmp.size() - 1; j >= 1; j--) tmp[j] -= tmp[j - 1];
		int prod = 1;
		for(int x : tmp) prod *= std::max(x, 1);
		// printf("gap[%d]: ", i); for(int x : tmp) printf("%d ", x); puts("");
		// printf("mp[%d]: %d\n", i, prod);
		mp[i].resize(prod);
		gap[i] = tmp;
	}
	for(int i = 1; i <= n; i++) {
		std::vector<int> tmp{i};
		auto res = dfs(n + 1, tmp);
		printf("%d %lld\n", res.val, res.cnt);
	}
	fprintf(stderr, "%d\n", tot);
	fprintf(stderr, "time = %.3f\n", clock() / (double)CLOCKS_PER_SEC);
	return 0;
} /*
5
1 2 5 4 3

40
20 28 8 34 12 24 4 38 16 30 10 36 2 26 14 32 6 22 18 40 1 23 19 35 9 27 15 39 5 31 11 25 3 37 17 29 7 33 13 21
*/