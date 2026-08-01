#include <cstdio>

const int N = 1000 + 5;

int n;
char s[N], ret[N], ans[N];

bool flag, once;
void dfs(int ind) {
	if(ind == n) {
		ans[ind] = '\0';
		std::printf("%s\n", ans);
		flag = true;
		return;
	}
	if(ret[ind] >= 0) {
		ans[ind] = ret[ind] + '0';
		int once_before = once;
		once = true;
		dfs(ind + 1);
		once = once_before;
		if(flag) return;
		ans[ind] = !ret[ind] + '0';
		dfs(ind + 1);
	} else {
		ans[ind] = 0 + '0';
		dfs(ind + 1);
		if(flag) return;
		ans[ind] = 1 + '0'; 
		dfs(ind + 1);
	}
}

int main() {
	int T;
	std::scanf("%d", &T);
	for(int t = 1; t <= T; t++) {
		std::scanf("%d%s", &n, s);
		for(int i = 0; i < n * 2 - 1; i++) s[i] -= '0', ret[i] = -1;
		for(int i = 0; i < n; i++)
			for(int j = i; j <= i + n - 1; j++)
				if(ret[j - i] == -1) ret[j - i] = s[j];
				else if(ret[j - i] != s[j]) ret[j - i] = -2;
		flag = once = false;
		dfs(0);
	}
	return 0;
}