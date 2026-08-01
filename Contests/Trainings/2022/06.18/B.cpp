#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>

const int  N = 2e5 + 5;

int head[N], end[N];
int n, Q;

struct Node { int to[2]; int val, cnt; } dat[N];
int nw_node(int e1, int e2, int v, int c) {
	static int k = 1;
	dat[k].to[0] = e1, dat[k].to[1] = e2;
	dat[k].val = v, dat[k].cnt = c;
	return k++;
}
int nxt(int last, int now) { return dat[now].to[dat[now].to[0] == last]; }
int &ref(int val, int now) { return dat[now].to[dat[now].to[1] == val]; }

int main() {
	// freopen("b.in", "r", stdin);
	// freopen("b.out", "w", stdout);
	scanf("%d%d", &n, &Q);
	while(Q--) {
		char type[10];
		int x, y, z;
		scanf("%s", type);
		if(!strcmp(type, "push")) {
			scanf("%d%d%d", &x, &y, &z);
			int nw = nw_node(0, head[z], y, x);
			if(!end[z]) end[z] = nw;
			ref(0, head[z]) = nw;
			head[z] = nw;
		} else if(!strcmp(type, "pop")) {
			scanf("%d%d", &x, &z);
			int now = head[z];
			int ans = -1;
			while(x >= dat[now].cnt && now) {
				x -= dat[now].cnt;
				ans = dat[now].val;
				int nt = nxt(0, now);
				ref(now, nt) = 0;
				now = nt;
			}
			if(x && now) {
				dat[now].cnt -= x;
				ans = dat[now].val;
			}
			head[z] = now;
			if(now == 0) end[z] = 0;
			// assert(!x);
			printf("%d\n", ans);
		} else if(!strcmp(type, "put")) {
			scanf("%d%d", &x, &y);
			if(!head[x]) continue;
			int begx = head[x], begy = head[y];
			if(!begy) end[y] = begx;
			head[y] = end[x];
			if(begx) ref(0, begx) = begy;
			if(begy) ref(0, begy) = begx;
			head[x] = end[x] = 0;
		} else assert(!"Unexpected input");
	}
	return 0;
} /*
5 13
put 1 2
push 1 1 1
push 2 2 2
pop 1 2
push 10 3 2
put 1 2
put 2 1
put 1 5
pop 11 5
push 2 5 3
push 4 3 3
put 5 3
pop 5 3

*/