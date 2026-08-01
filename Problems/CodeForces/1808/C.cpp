#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>

const int N = 20 + 5;

char l[N], r[N];

char ans[N], ret[N];

bool checkl(int mx, int st) {
	for(int i = st; i <= 20; i++) {
		if(mx > l[i]) {
			for(int j = i; j <= 20; j++) ret[j] = mx;
			return true;
		} else if(mx == l[i]) ret[i] = mx;
		else return false;
	}
	return true;
}
bool checkr(int mn, int st) {
	for(int i = st; i <= 20; i++) {
		if(mn < r[i]) {
			for(int j = i; j <= 20; j++) ret[j] = mn;
			return true;
		} else if(mn == r[i]) ret[i] = mn;
		else return false;
	}
	return true;
}
bool check(int mn, int mx) {
	for(int i = 1; i <= 20; i++) ret[i] = 0;
	int i = 1;
	while(l[i] == '0' && r[i] == '0') ret[i] = '0', i++;
	for(; i <= 20; i++) {
		if(l[i] > mx || r[i] < mn) return false;
		if(l[i] == r[i] && mn <= l[i] && l[i] <= mx) { ret[i] = l[i]; continue; }
		for(int j = std::max(l[i] + 1, mn); j <= std::min(r[i] - 1, mx); j++) {
			for(int k = i; k <= 20; k++) ret[k] = j;
			return true;
		}
		if(mn <= l[i] && l[i] <= mx && checkl(mx, i + 1)) { ret[i] = l[i]; return true; }
		if(mn <= r[i] && r[i] <= mx && checkr(mn, i + 1)) { ret[i] = r[i]; return true; }
		return false;
	}
	return true;
}

int main() {
// #ifdef DEBUG
// 	freopen("in.txt", "r", stdin);
// 	freopen("out.txt", "w", stdout);
// #endif
	int T; scanf("%d", &T);
	while(T--) {
		for(int i = 0; i <= 21; i++) ret[i] = ans[i] = l[i] = r[i] = 0;
		scanf("%s%s", l + 1, r + 1);
		int ll = strlen(l + 1), lr = strlen(r + 1);
		for(int i = 1; i <= ll; i++) l[20 - i + 1] = l[ll - i + 1];
		for(int i = 1; i <= 20 - ll; i++) l[i] = '0';
		for(int i = 1; i <= lr; i++) r[20 - i + 1] = r[lr - i + 1];
		for(int i = 1; i <= 20 - lr; i++) r[i] = '0';
		l[21] = r[21] = 0;
		// printf("l = %s, r = %s\n", l + 1, r + 1);
		int ansv = 10;
		for(int i = 0; i <= 9; i++) for(int j = i; j <= 9; j++)
			if(j - i < ansv && check(i + '0', j + '0')) {
				// printf("check(%d, %d) = true\n", i, j);
				ansv = j - i;
				for(int k = 1; k <= 20; k++) ans[k] = ret[k];
			}
		int id = 0;
		for(int i = 1; i <= 20; i++) {
			if(r[i] == '0') continue;
			if(r[i] != '0' && l[i] == '0') { id = i; break; }
			break;
		}
		if(id) {
			ansv = 0;
			for(int i = 1; i <= id; i++) ans[i] = '0';
			for(int i = id + 1; i <= 20; i++) ans[i] = '9';
		}
		ans[21] = 0;
		// printf("ans = %s\n", ans + 1);
		bool flag = false;
		for(int i = 1; i <= 20; i++)
			if(ans[i] != '0' || flag) flag = true, putchar(ans[i]);
		puts("");
	}
	return 0;
}