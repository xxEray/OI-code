#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 1e6 + 5;

char s[N];
int n;

struct Node {
	int l, r;
	bool operator<(const Node &rhs) const { return l - r > rhs.l - rhs.r; }
} both[N];
int cntboth = 0;

int main() {
	scanf("%d", &n);
	int cntl = 0, cntr = 0;
	for(int i = 1; i <= n; i++) {
		scanf("%s", s);
		int l = 0, r = 0;
		int len = strlen(s);
		for(int j = 0; j < len; j++)
			if(s[j] == '(') l++;
			else if(l == 0) r++;
			else l--;
		if(l == 0) cntr += r;
		else if(r == 0) cntl += l;
		else both[++cntboth] = {l, r};
	}
	std::sort(both + 1, both + cntboth + 1);
	for(int i = 1; i <= cntboth; i++)
		if(cntl < both[i].r) { puts("No"); return 0; }
		else cntl += both[i].l - both[i].r;
	if(cntl != cntr) puts("No");
	else puts("Yes");
	return 0;
}