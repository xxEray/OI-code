#include <cstdio>
#include <algorithm>
#include <assert.h>

const int N = 1e5 + 5;

char a[N];
int n, Q;

int in[N * 30], out[N * 30];
int time_state = 0;

struct Answer { int v[10]; } ans[N * 30];
Answer operator+(Answer x, Answer y) { Answer z; for(int i = 0; i < 10; i++) z.v[i] = x.v[i] + y.v[i]; return z; }
Answer operator-(Answer x, Answer y) { Answer z; for(int i = 0; i < 10; i++) z.v[i] = x.v[i] - y.v[i]; return z; }
Answer operator+(Answer x, int y) { x.v[y]++; return x; }

struct Node { int id, prv, nxt; } list[N];
void calc(int st) {
	int pos = st, dir = 1;
	while(st <= pos && pos <= n) {
		time_state++, ans[time_state] = ans[time_state - 1];
		if('0' <= a[pos] && a[pos] <= '9') ans[time_state] = ans[time_state] + (a[pos] - '0');
		if(!in[pos]) in[pos] = time_state;
		if('1' <= a[pos] && a[pos] <= '9') a[pos]--;
		else if(a[pos] == '0') {
			int prv = list[pos].prv, nxt = list[pos].nxt;
			list[prv].nxt = nxt, list[nxt].prv = prv;
		} else {
			dir = (a[pos] == '<' ? -1 : 1);
			int nxtpos = (dir == 1 ? list[pos].nxt : list[pos].prv);
			if(a[nxtpos] == '<' || a[nxtpos] == '>') {
				int prv = list[pos].prv, nxt = list[pos].nxt;
				list[prv].nxt = nxt, list[nxt].prv = prv;
			}
		}
		if(dir == -1)
			for(int i = list[pos].prv + 1; i <= pos; i++) if(!out[i]) out[i] = time_state;
		pos = (dir == 1 ? list[pos].nxt : list[pos].prv);
	}
}

int main() {
	scanf("%d%d", &n, &Q);
	scanf("%s", a + 1);
	for(int i = 1; i <= n; i++) list[i].id = i, list[i].prv = i - 1, list[i].nxt = i + 1;
	for(int i = 1; i <= n; i++) if(!in[i]) calc(i);
	for(int i = 1; i <= n; i++) if(!out[i]) out[i] = time_state + 1;
	in[n + 1] = time_state + 1;
	// for(int i = 1; i <= n; i++) printf("%d: in = %d, out = %d\n", i, in[i], out[i]);
	// for(int i = 1; i <= time_state; i++) {
	// 	printf("ans[%d]: ", i);
	// 	for(int j = 0; j < 10; j++) printf("%d ", ans[i].v[j]);
	// 	puts("");
	// }
	while(Q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		int tl = in[l], tr = std::min(in[r + 1] - 1, out[l]);
		if(tl > tr) {
			printf("time_state = %d\n", time_state);
			for(int i = l - 3; i <= l + 10; i++) putchar(a[i]);
			printf("...");
			for(int i = r - 10; i <= r + 3; i++) putchar(a[i]);
			puts("");
			printf("l = %d, r = %d, tl = %d, tr = min(%d, %d)\n", l, r, tl, in[r + 1] - 1, out[l]);
			return 0;
		}
		Answer ret = ans[tr] - ans[tl - 1];
		for(int i = 0; i < 10; i++) printf("%d ", ret.v[i]);
		puts("");
	}
	return 0;
} /*
10 1
306<<>4>04
2 4
*/