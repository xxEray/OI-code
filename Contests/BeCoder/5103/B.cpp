#include <bits/stdc++.h>

const int N = 3e5 + 5;
const int M = 1e6 + 5;

int n, Q;

int label[N];
int fa[N + 2 * M], type[N + 2 * M], sz[N + 2 * M];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { (x = find(x)) != (y = find(y)) ? fa[x] = y, type[y] |= type[x], sz[y] += sz[x] : 0; }
int cnt;

int main() {
	scanf("%d%d", &n, &Q);
	for(int i = 1; i <= n + 2 * Q; i++) fa[i] = i, sz[i] = 1;
	while(Q--) {
		char tp[2];
		int x, y;
		scanf("%s", tp);
		if(tp[0] == '+') {
			scanf("%d%d", &x, &y);
			if(x == y) {
				if(label[x]) type[find(label[x])] = true;
				else label[x] = ++cnt, type[label[x]] = true;
			} else {
				if(!label[x] && !label[y]) label[x] = ++cnt, label[y] = ++cnt, merge(label[x], label[y]);
				else if(!label[x] && label[y]) label[x] = ++cnt, merge(label[x], label[y]);
				else if(!label[y] && label[x]) label[y] = ++cnt, merge(label[x], label[y]);
				else {
					if(find(label[x]) == find(label[y])) type[find(label[x])] = true;
					else merge(label[x], label[y]);
				}
			}
		} else if(tp[0] == '-') {
			scanf("%d", &x);
			assert(label[x]);
			sz[find(label[x])]--, label[x] = 0;
		} else {
			scanf("%d", &x);
			if(!label[x]) putchar('0');
			else if(type[find(label[x])]) putchar('1');
			else putchar(sz[find(label[x])] == 1 ? '0' : '?');
		}
	}
	puts("");
	return 0;
}