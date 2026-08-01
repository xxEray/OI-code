#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 50 + 5;
const int MEM = 1e5 + 5;

char s[N], t[N];
char c[N][3], a[N][N], len[N];
int ls, lt, m;

struct Node { Node *nxt[30]; } mem[MEM];
Node *nw_node() { static int k = 0; return &mem[++k]; }
Node *head[N], *top;

int main() {
	scanf("%s%s", s + 1, t + 1);
	ls = strlen(s + 1), lt = strlen(t + 1);
	for(int i = 1; i <= m; i++) scanf("%s%s", c[i], a[i] + 1), len[i] = strlen(a[i] + 1);
	for(int i = 1; i <= ls; i++) s[i] -= 'a' - 1;
	for(int i = 1; i <= m; i++) for(int j = 1; j <= len[i]; j++) a[i][j] -= 'a' - 1;
	top = nw_node();
	for(int i = 1; i <= m; i++) head[i] = nw_node();
	Node *now = top;
	for(int i = 1; i <= ls; i++) {
		now->nxt[s[i]] = nw_node();
		now = now->nxt[s[i]];
	}
	for(int i = 1; i <= m; i++) {
		now = head[i];
		for(int j = 1; j <= len[i]; j++) {
			now->nxt[a[i][j]] = nw_node();
			now = now->nxt[a[i][j]];
		}
	}
	head[0] = top, len[0] = ls;
	for(int o = 1; o <= m; o++) {
		char ch = c[o][0];
		for(int i = 0; i <= m; i++) {
			now = head[i];
			for(int j = 1; j <= len[i]; j++) {
				if(now->nxt[ch]) {
					Node *cur = now, *clone = head[o];
					bool flag = false;
					for(int k = 1; k <= len[o]; k++)
						if(cur->nxt[a[o][k]]) cur = cur->nxt[a[o][k]], clone = clone->nxt[a[o][k]];
						else {
							flag = true;
							cur->nxt[a[o][k]] = clone->nxt[a[o][k]];
						}
				}
				now = now->nxt[a[i][j]];
			}
		}
	}
	return 0;
}