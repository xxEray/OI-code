#include <bits/stdc++.h>

const int N = 1e5 + 5;

int n, m;

bool mpx[N], mpy[N];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) { int x, y; scanf("%d%d", &x, &y); mpx[x] = true, mpy[y] = true; }
	int cnt = 0;
	for(int i = 1; i <= n; i++) cnt += mpx[i];
	for(int i = 1; i <= n; i++) if(cnt < m && !mpx[i]) mpx[i] = true, cnt++;
	cnt = 0;
	for(int i = 1; i <= n; i++) cnt += mpy[i];
	for(int i = 1; i <= n; i++) if(cnt < m && !mpy[i]) mpy[i] = true, cnt++;
	std::vector<int> vx, vy, vix, viy;
	for(int i = 1; i <= n; i++)
		if(mpx[i]) vx.emplace_back(i);
		else vix.emplace_back(i);
	for(int i = 1; i <= n; i++)
		if(mpy[i]) vy.emplace_back(i);
		else viy.emplace_back(i);
	printf("%d\n", n * m);
	for(int x : vx) for(int y : vy) printf("%d %d\n", x, y);
	for(int i = 0; i < n - m; i++) for(int j = 0; j < m; j++) printf("%d %d\n", vix[i], viy[(i + j) % (n - m)]);
	return 0;
}