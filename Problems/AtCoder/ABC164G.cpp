#include <iostream>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

typedef long long LL;

const int N = 26 * 26 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n, Q;
map<string, LL> q;
map<string, int> id;
LL e[N][N], ori[N];

string cat(char i) { return string() + i; }
string cat(char i, char j) { return string() + i + j; }
string cat(char i, char j, char k) { return string() + i + j + k; }

LL dis[N][N];

int main() {
	n = 0;
	for(char i = 'a'; i <= 'z'; i++) for(char j = 'a'; j <= 'z'; j++) id[cat(i, j)] = ++n;
	cin >> Q;
	while(Q--) {
		string str;
		LL w;
		cin >> str >> w;
		q[str] = w;
	}
	for(char i = 'a'; i <= 'z'; i++) for(char j = 'a'; j <= 'z'; j++) ori[id[cat(i, j)]] = q[cat(i, j)] + q[cat(i)] + q[cat(j)];
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) e[i][j] = -LLINF;
	for(char i = 'a'; i <= 'z'; i++) for(int j = 'a'; j <= 'z'; j++) for(int k = 'a'; k <= 'z'; k++)
		e[id[cat(i, j)]][id[cat(j, k)]] = q[cat(i, j, k)] + q[cat(j, k)] + q[cat(k)];
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dis[i][j] = (i == j ? 0 : -LLINF);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(e[i][j] > -LLINF) dis[i][j] = e[i][j];
	for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dis[i][j] = std::max(dis[i][j], dis[i][k] + dis[k][j]);
	for(int i = 1; i <= n; i++) if(dis[i][i] > 0) { puts("Infinity"); return 0; }
	LL ans = -LLINF;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) ans = std::max(ans, ori[i] + dis[i][j]);
	for(char c = 'a'; c <= 'z'; c++) ans = std::max(ans, q[cat(c)]);
	printf("%lld\n", ans);
	return 0;
}