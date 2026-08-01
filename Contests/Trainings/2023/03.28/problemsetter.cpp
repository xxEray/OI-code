#include <cstdio>
#include <algorithm>
#include <vector>
#include <ctime>
#include <set>
#include <cassert>

// #define assert(...) ((void)0)

typedef long long LL;

const int N = 30 + 5;

int n;
LL a[N];
bool done[N];
LL out[N];
int step[N][2];

std::vector<LL> v1[2 * N], v2[2 * N];
LL val1, val2;
int id;
int t1[N], t2[N];
bool ok;
void dfs1(int i, int x, int y, LL v, const bool &type) {
	// if(!type) printf("dfs1(%d, %d, %d, %lld)\n", i, x, y, v);
	if(ok) return;
	if(i == n / 2 + 1) {
		if(!x && !y) return;
		if(type) ok |= (v == val1 && x - y + 30 == id);
		else v1[x - y + 30].push_back(v);
		// if(!type) printf("  - get %lld with %d\n", v, x - y + 30);
		return;
	}
	if(!ok) t1[i] = 0, dfs1(i + 1, x, y, v, type);
	if(!ok) t1[i] = 1, dfs1(i + 1, x + 1, y, v + a[i], type);
	if(!ok) t1[i] = -1, dfs1(i + 1, x, y + 1, v - a[i], type);
}
void dfs2(int i, int x, int y, LL v, const bool &type) {
	// if(!type) printf("dfs2(%d, %d, %d, %lld)\n", i, x, y, v);
	if(ok) return;
	if(i == n / 2) {
		if(!x && !y) return;
		if(type) ok |= (-v == val2 && y - x + 30 == id);
		else v2[y - x + 30].push_back(-v);
		// if(!type) printf("  - get %lld with %d\n", -v, y - x + 30);
		return;
	}
	if(!ok) t2[i] = 0, dfs2(i - 1, x, y, v, type);
	if(!ok) t2[i] = 1, dfs2(i - 1, x + 1, y, v + a[i], type);
	if(!ok) t2[i] = -1, dfs2(i - 1, x, y + 1, v - a[i], type);
}

int cnt[1000005];
void radix_sort(std::vector<LL> &vct) {
	std::vector<LL> res(vct.size());
	for(auto &v : vct) v += 1e11, assert(v >= 0);
	for(int i = 0; i <= 1000000; i++) cnt[i] = 0;
	for(const auto &v : vct) cnt[v % 1000000]++;
	for(int i = 1; i <= 1000000; i++) cnt[i] += cnt[i - 1];
	for(int i = (int)vct.size() - 1; i >= 0; i--) res[--cnt[vct[i] % 1000000]] = vct[i];
	res.swap(vct);
	for(int i = 0; i <= 1000000; i++) cnt[i] = 0;
	for(const auto &v : vct) cnt[v / 1000000]++;
	for(int i = 1; i <= 1000000; i++) cnt[i] += cnt[i - 1];
	for(int i = (int)vct.size() - 1; i >= 0; i--) res[--cnt[vct[i] / 1000000]] = vct[i];
	res.swap(vct);
	for(auto &v : vct) v -= 1e11;
	assert(std::is_sorted(vct.begin(), vct.end()));
}

bool calc() {
	bool flag = false, flag1 = true, flag2 = true;
	dfs1(1, 0, 0, 0, false), dfs2(n, 0, 0, 0, false);
	for(int i = 0; i <= 60 && !flag; i++) {
		radix_sort(v1[i]), radix_sort(v2[i]);
		if(i == 30) for(int j = 0; j < (int)v1[i].size(); j++) if(v1[i][j] == 0) { val1 = val2 = 0; id = i; flag = true, flag2 = false; break; }
		if(i == 30) for(int j = 0; j < (int)v2[i].size(); j++) if(v2[i][j] == 0) { val1 = val2 = 0; id = i; flag = true, flag1 = false; break; }
		int j = 0, k = 0;
		while(j < (int)v1[i].size() && k < (int)v2[i].size())
			if(v1[i][j] == v2[i][k]) { val1 = v1[i][j], val2 = v2[i][k]; id = i; flag = true; break; }
			else if(v1[i][j] < v2[i][k]) j++;
			else k++;
	}
	if(!flag) return false;
	// printf("val1 = %lld, val2 = %lld\n", val1, val2);
	if(flag1) ok = false, dfs1(1, 0, 0, 0, true), assert(ok);
	else for(int i = 1; i <= n / 2; i++) t1[i] = 0;
	if(flag2) ok = false, dfs2(n, 0, 0, 0, true), assert(ok);
	else for(int i = n / 2 + 1; i <= n; i++) t2[i] = 0;
	std::vector<int> posi, nega;
	for(int i = 1; i <= n / 2; i++)
		if(t1[i] == 1) posi.push_back(i);
		else if(t1[i] == -1) nega.push_back(i);
	for(int i = n / 2 + 1; i <= n; i++)
		if(t2[i] == 1) posi.push_back(i);
		else if(t2[i] == -1) nega.push_back(i);
	assert(!posi.empty() && !nega.empty());
	assert(posi.size() == nega.size());
	std::random_shuffle(posi.begin(), posi.end()), std::random_shuffle(nega.begin(), nega.end());
	LL val = 0;
	int sz = posi.size();
	for(int i = 0; i < sz; i++) {
		done[posi[i]] = true, out[posi[i]] = -val, val += a[posi[i]], step[posi[i]][0] = posi[i], step[posi[i]][1] = nega[i];
		done[nega[i]] = true, out[nega[i]] = val, val -= a[nega[i]], step[nega[i]][0] = nega[i], step[nega[i]][1] = posi[(i + 1) % sz];
	}
	assert(val == 0);
	for(int i = 1; i <= n; i++) if(!done[i]) out[i] = a[i], step[i][0] = i, step[i][1] = posi[0];
	return true;
}

int main() {
	// srand(time(0));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	bool flag = false;
	for(int i = 1; i <= n; i++) if(!(a[i] & 1)) {
		out[i] = a[i] / 2, step[i][0] = step[i][1] = i;
		for(int j = 1; j <= n; j++) if(j != i) out[j] = a[j] - out[i], step[j][0] = j, step[j][1] = i;
		flag = true;
		break;
	}
	if(!flag) flag |= calc();
	if(!flag) { puts("No"); return 0; }
	for(int i = 1; i <= n; i++) assert(std::abs(out[i]) <= 10000000000);
	for(int i = 1; i <= n; i++) assert(out[step[i][0]] + out[step[i][1]] == a[i]);
	puts("Yes");
	for(int i = 1; i <= n; i++) printf("%lld ", out[i]);
	puts("");
	for(int i = 1; i <= n; i++) printf("%d %d\n", step[i][0], step[i][1]);
	return 0;
}