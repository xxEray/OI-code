#include <bits/stdc++.h>

int rand(int l, int r) { return (rand() << 15 | rand()) % (r - l + 1) + l; }

const int N = 3e7;

std::vector<std::vector<int>> vct;

int n;

int a[N + 5];
int ans;
bool vis[N + 5];
void dfs(int id) {
	if(id == n + 1) {
		std::vector<int> arr(n);
		for(int i = 1; i <= n; i++) arr[i - 1] = a[i];
		vct.emplace_back(arr);
		return;
	}
	for(int i = 1; i <= n; i++) if(!vis[i]) {
		bool flag = true;
		for(int j = 1; j < id; j++) flag &= ((std::__gcd(j, id) == 1) == (std::__gcd(a[j], i) == 1));
		if(flag) {
			vis[i] = true, a[id] = i;
			dfs(id + 1);
			vis[i] = false;
		}
	}
}

int main(int, char *argv[]) {
	int sd; sscanf(argv[1], "%d", &sd); srand(sd);
	freopen("permutation.in", "w", stdout);
	n = N;
	printf("%d\n", n);
	if(1) {
		for(int i = 1; i <= n; i++) a[i] = i;
		std::random_shuffle(a + 1, a + n + 1);
		for(int i = 1; i <= n; i++)
			if(rand() % 2) printf("0 ");
			else printf("%d ", a[i]);
		return 0;
	}
	dfs(1);
	auto vec = vct[rand(0, (int)vct.size() - 1)];
	for(int i = 0; i < n; i++)
		if(rand() % 2) printf("0 ");
		else printf("%d ", vec[i]);
	puts("");
	return 0;
}