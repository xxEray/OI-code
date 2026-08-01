#include <bits/stdc++.h>
#include <cassert>

typedef long long LL;

int n;

std::map<std::pair<int, std::vector<int>>, bool> mp;
bool state(const std::vector<int> &vct, int turn) {
	if(vct.size() == 1) return false;
	else if(vct.size() == 2) return true;
	else if(mp.count({turn, vct})) return mp[{turn, vct}];
	// printf("state [%d] ", turn); for(int x : vct) printf("%d ", x); puts("");
	if(turn == 0) {
		std::vector<int> tmp = vct;
		for(int i = 0; i < vct[0] - 1; i++) {
			tmp[0]--, tmp[1]++;
			if(!state(tmp, 1)) return mp[{turn, vct}] = true;
		}
		tmp.erase(tmp.begin()), tmp[0]++;
		if(!state(tmp, 1)) return mp[{turn, vct}] = true;
	} else {
		std::vector<int> tmp = vct;
		for(int i = 0; i < vct.back() - 1; i++) {
			tmp.back()--, tmp.rbegin()[1]++;
			if(!state(tmp, 0)) return mp[{turn, vct}] = true;
		}
		tmp.pop_back(), tmp.back()++;
		if(!state(tmp, 0)) return mp[{turn, vct}] = true;
	}
	return mp[{turn, vct}] = false;
}

bool calc(std::vector<int> vct) {
	int sz = vct.size();
	if(sz == 1) return false;
	else if(sz == 2) return true;
	LL s1 = 0, s2 = 0, sum1 = 0, sum2 = 0;
	for(int i = 0; i < sz / 2; i++) {
		s1 += vct[i];
		if(i) vct[i] += vct[i - 1];
		sum1 += vct[i];
	}
	for(int i = sz - 1; i >= sz - sz / 2 + (sz % 2 == 0); i--) {
		s2 += vct[i];
		if(i < sz - 1) vct[i] += vct[i + 1];
		sum2 += vct[i];
	}
	// if(s1 != s2) return s1 > s2;
	return sum1 > sum2;
}

std::vector<int> seq;
void dfs(int id) {
	if(id == n) {
		bool fl = state(seq, 0);
		if(fl == calc(seq)) return;
		// if(!fl) return;
		for(int i = 0; i < n; i++) printf("%d ", seq[i]);
		printf("-- %s\n", fl ? "YES" : "NO");
		return;
	}
	for(int i = 1; i <= 4; i++) seq[id] = i, dfs(id + 1);
}

int main() {
	printf("%d\n", (int)state({1, 3, 1, 1, 2}, 0));
	return 0;
	freopen("1010.txt", "w", stdout);
	for(n = 3; n <= 7; n++) {
		seq.resize(n);
		dfs(0);
	}
	return 0;
}