#include <bits/stdc++.h>

const int N = 3e5 + 5;

int n, c;
char s[N];

int a[N], b[N];
int prv[N], nxt[N];

int out[N];

bool del[N];
void solve(int lb, int rb, int sum, int m) {
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> q;
	for(int i = 1; i <= c; i++) a[i] = b[i];
	for(int i = lb; i <= rb; i++) prv[i] = i - 1, nxt[i] = i + 1, del[i] = 0;
	prv[lb] = nxt[rb] = 0;
	prv[0] = nxt[0] = del[0] = 0;
	for(int i = lb; i <= rb; i++) q.push({a[i], i});
	int now = 0;
	for(int i = 0; i <= (c + 1) / 2; i++) {
		if(m - 2 * i >= 0) out[m - 2 * i] = std::max(out[m - 2 * i], sum - now);
		int x;
		while(!q.empty()) {
			x = q.top().second;
			q.pop();
			if(!del[x]) break;
			// printf("x = %d (deleted)\n", x);
		}
		if(q.empty()) break;
		// printf("x = %d\n", x);
		now += a[x];
		del[prv[x]] = del[nxt[x]] = true;
		// printf("delete %d %d\n", prv[x], nxt[x]);
		if(!prv[x] || !nxt[x]) del[x] = true, nxt[prv[prv[x]]] = 0, prv[nxt[nxt[x]]] = 0; // , printf("delete %d\n", x);
		else {
			a[x] = a[prv[x]] + a[nxt[x]] - a[x], q.push({a[x], x});
			// printf("a[%d] -> %d\n", x, a[x]);
			prv[x] = prv[prv[x]], nxt[prv[x]] = x;
			nxt[x] = nxt[nxt[x]], prv[nxt[x]] = x;
		}
	}
}

int main() {
#ifndef DEBUG
	freopen("modification.in", "r", stdin);
	freopen("modification.out", "w", stdout);
#endif
	scanf("%d%s", &n, s + 1);
	for(int i = 1; i <= n; i++) {
		if(i == 1 || s[i] != s[i - 1]) c++;
		a[c]++;
	}
	for(int i = 1; i <= c; i++) b[i] = a[i];
	// printf("a: "); for(int i = 1; i <= c; i++) printf("%d ", a[i]);	puts("");
	int sum = 0;
	for(int i = 1; i <= c; i++) sum += a[i];
	solve(2, c - 1, sum, c);
	solve(3, c - 1, sum - a[1], c - 1);
	solve(2, c - 2, sum - a[c], c - 1);
	solve(3, c - 2, sum - a[1] - a[c], c - 2);
	if(c <= 2) out[3] = n;
	for(int i = 3; i <= n + 1; i++) out[i] = std::max(out[i - 1], out[i]);
	out[2] = 0;
	int ret = 0;
	for(int i = 1; i <= n; i++) ret += (s[i] == '0');
	out[2] = std::max(out[2], ret);
	for(int i = n; i >= 1; i--) ret += (s[i] == '1') - (s[i] == '0'), out[2] = std::max(out[2], ret);
	for(int i = 2; i <= n + 1; i++) printf("%d ", out[i]);
	putchar('\n');
	return 0;
} /*
10
1011011001
*/