#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;
int a[N];


int prv[N], nxt[N];

std::set<std::pair<int, int>> todo;
void update(int i, int j) {
	if(i == 0 || j == n + 1) return;
	if(a[i] > i && a[j] < j) todo.insert({i, j});
}

void remove(int i, bool upd = true) {
	nxt[prv[i]] = nxt[i];
	prv[nxt[i]] = prv[i];
	if(upd) update(prv[i], nxt[i]);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) prv[i] = i - 1, nxt[i] = i + 1;
	prv[n + 1] = n, nxt[0] = 1;
	for(int i = 1; i <= n; i++) if(a[i] == i) remove(i, false);
	for(int i = 1; i <= n; i++) if(a[i] != i) update(i, nxt[i]);
	int ans = 0;
	while(!todo.empty()) {
		auto [i, j] = *todo.begin();
		todo.erase(todo.begin());
		ans++;
		std::swap(a[i], a[j]);
		update(prv[i], i), update(i, nxt[i]);
		update(prv[j], j), update(j, nxt[j]);
		if(a[i] == i) remove(i);
		if(a[j] == j) remove(j);
	}
	printf("%d\n", ans);
	return 0;
}