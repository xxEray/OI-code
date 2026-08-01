#include <cstdio>
#include <algorithm>
#include <deque>

const int N = 1e5 + 5;

int a[N];
int n;

std::deque<int> q;

bool check() {
	int cnt = 0;
	for(int x : q) cnt += (x == 1);
	while(q.size() > 1U && q.front() == q.back()) q.pop_front(), q.pop_back();
	for(int i = 0; i < (int)q.size(); i += 2) if(q[i] != q[i + 1]) return false;
	return cnt % 4 == 0;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		q.clear(); 
		scanf("%d", &n);
		int xorall = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), xorall ^= a[i];
		if(xorall == 0) { puts("Draw"); continue; }
		if(n == 1) { puts("Alice"); continue; }
		int bit;
		for(int i = 30; i >= 0; i--) if(xorall >> i & 1) { bit = i; break; }
		for(int i = 1; i <= n; i++) q.push_back(a[i] >> bit & 1);
		if(!(n & 1)) { puts("Alice"); continue; }
		if(q.front() == 0 && q.back() == 0) { puts("Bob"); continue; }
		std::deque<int> cq = q;
		q.pop_front();
		bool flag1 = check();
		q = cq;
		q.pop_back();
		bool flag2 = check();
		if(flag1 || flag2) puts("Alice");
		else puts("Bob");
	}
	return 0;
} /*
19
1 0 0 0 0 1 1 1 1 0 0 0 0 1 1 0 0 1 1
*/