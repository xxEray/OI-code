#include <cstdio>
#include <algorithm>
#include <set>

typedef long long LL;

const int N = 16000 + 5;
const int M = 100 + 5;

int n, m;
struct Zone { int cap, lv, id; } a[M];
bool operator<(Zone x, Zone y) { return x.lv < y.lv; }
struct Student { int lv; int w, id; } b[N];

std::multiset<Zone> st;
int out[N];

int main() {
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) scanf("%d", &a[i].cap), n += a[i].cap, a[i].id = i;
	for(int i = 1; i <= m; i++) scanf("%d", &a[i].lv);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i].lv), b[i].id = i;
	for(int i = 1; i <= n; i++) scanf("%d", &b[i].w);
	std::sort(b + 1, b + n + 1, [&](Student x, Student y) { return x.w > y.w; });
	for(int i = 1; i <= m; i++) st.insert(a[i]);
	for(int i = 1; i <= n; i++) {
		auto it = st.lower_bound({0, b[i].lv, 0});
		if(it == st.begin()) continue;
		auto tmp = *--it;
		st.erase(it);
		tmp.cap--;
		if(tmp.cap) st.insert(tmp);
		out[b[i].id] = tmp.id;
	}
	for(int i = 1; i <= n; i++)
		if(out[i]) printf("%d ", out[i]);
		else {
			auto tmp = *st.begin();
			st.erase(st.begin());
			printf("%d ", tmp.id);
			tmp.cap--;
			if(tmp.cap) st.insert(tmp);
		}
	puts("");
	return 0;
}