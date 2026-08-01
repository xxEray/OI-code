#include <cstdio>
#include <algorithm>
#include <string>
#include <map>

typedef long long LL;

const int N = 50 + 5;
const int LEN = 20 + 5;
const LL LLINF = 0x3f3f3f3f3f3f3f3fLL;

std::string s[N];
LL w[N];
int n;

std::map<std::pair<std::string, bool>, int> id;
int idtot = 0;

LL edge[N * LEN * 3][N * LEN * 3];
inline void add_edge(int u, int v, LL w) { // 有向边
	edge[u][v] = std::min(edge[u][v], w);
}

void get_vertices() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		char t[LEN];
		scanf("%s%lld", t, &w[i]);
		s[i] = t;
	}
	for(int i = 1; i <= n; i++) {
		std::string tmp;
		for(int j = 0; j < (int)s[i].size(); j++) {
			tmp.push_back(s[i][j]);
			if(id.find({tmp, 1}) == id.end()) id[{tmp, 1}] = ++idtot;
		}
		for(int j = 0; j < (int)s[i].size(); j++) {
			if(id.find({tmp, 0}) == id.end()) id[{tmp, 0}] = ++idtot;
			tmp.erase(tmp.begin());
		}
	}
	id[{"", 0}] = ++idtot;
	id[{"", 1}] = ++idtot;
	id[{"Start", 0}] = ++idtot;
	id[{"Finish", 0}] = ++idtot;
	for(int i = 1; i <= idtot; i++)
		for(int j = 1; j <= idtot; j++)
			edge[i][j] = (i == j ? 0 : LLINF);
}

bool prefix(const std::string &s1, const std::string &s2) { // 判断 s1 是否为 s2 的前缀
	for(int i = 0; i < (int)s1.size(); i++)
		if(s1[i] != s2[i]) return false;
	return true;
}
bool suffix(const std::string &s1, const std::string &s2) { // 判断 s1 是否为 s2 的后缀
	int add = (int)s2.size() - (int)s1.size(); // 计算两个字符串中间的错位
	for(int i = 0; i < (int)s1.size(); i++)
		if(s1[i] != s2[i + add]) return false;
	return true;
}
bool palindrome(const std::string &s) { // 判断 s 是否为回文串
	for(int i = 0; i < (int)s.size(); i++)
		if(s[i] != s[(int)s.size() - i - 1]) return false;
	return true;
}
void get_edges() {
	for(auto pr : id) {
		if(pr.first.first == "Start" || pr.first.first == "Finish" || pr.first.first == "") continue;
		for(int i = 1; i <= n; i++) {
			std::string frm = pr.first.first, add = s[i];
			bool tfrm = pr.first.second;
			if(tfrm == 0) {
				if((int)frm.size() >= (int)add.size()) {
					std::reverse(add.begin(), add.end());
					if(prefix(add, frm)) add_edge(id[pr.first], id[{frm.substr(add.size()), 0}], w[i]);
				} else {
					std::reverse(frm.begin(), frm.end());
					if(suffix(frm, add)) add_edge(id[pr.first], id[{add.substr(0, (int)add.size() - (int)frm.size()), 1}], w[i]);
				}
			} else {
				if((int)add.size() >= (int)frm.size()) {
					std::reverse(frm.begin(), frm.end());
					if(prefix(frm, add)) add_edge(id[pr.first], id[{add.substr(frm.size()), 0}], w[i]);
				} else {
					std::reverse(add.begin(), add.end());
					if(suffix(add, frm)) add_edge(id[pr.first], id[{frm.substr(0, (int)frm.size() - (int)add.size()), 1}], w[i]);
				}
			}
		}
	}
	for(auto pr : id) if(palindrome(pr.first.first)) add_edge(id[pr.first], id[{"Finish", 0}], 0);
	for(int i = 1; i <= n; i++) add_edge(id[{"Start", 0}], id[{s[i], 0}], w[i]), add_edge(id[{"Start", 0}], id[{s[i], 1}], w[i]);
}

void debug() { // debug 输出
	for(auto p : id) printf("{\"%s\", %d} -> %d\n", p.first.first.c_str(), p.first.second, p.second);
	for(auto p : id) {
		std::string str = p.first.first;
		int u = p.second;
		for(auto q : id) {
			std::string to = q.first.first;
			int v = q.second;
			if(edge[u][v] >= LLINF) continue;
			printf("{\"%s\", %d} -> {\"%s\", %d}  [W=%lld]\n", str.c_str(), p.first.second, to.c_str(), q.first.second, edge[u][v]);
		}
	}
}

LL dis[N * LEN * 3];
bool vis[N * LEN * 3];
void dijstra(int st, int tot) {
	for(int i = 1; i <= tot; i++) dis[i] = LLINF;
	dis[st] = 0;
	vis[st] = true;
	for(int i = 1; i <= tot; i++) // 对 st 进行松弛
		if(edge[st][i] < LLINF && dis[i] > dis[st] + edge[st][i])
			dis[i] = dis[st] + edge[st][i];
	for(int i = 1; i < tot; i++) {
		int u = 1;
		for(int j = 1; j <= tot; j++)
			if(vis[u] || (!vis[j] && dis[j] < dis[u]))
				u = j;
		vis[u] = true;
		for(int j = 1; j <= tot; j++) // 对 u 进行松弛
			if(edge[u][j] < LLINF && dis[j] > dis[u] + edge[u][j])
				dis[j] = dis[u] + edge[u][j];
	}
}
void get_answer() {
	dijstra(id[{"Start", 0}], idtot);
	LL ans = dis[id[{"Finish", 0}]];
	printf("%lld\n", ans >= LLINF ? -1LL : ans);
}

int main() {
	get_vertices();
	get_edges();
	// debug();
	get_answer();
	return 0;
}