#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

const int MAX_A = 2e6 + 5;

int n;

bool vis[MAX_A];
bool isprm[MAX_A];

int stk[MAX_A], top = 0;

int main() {
	memset(isprm, true, sizeof(isprm));
	isprm[1] = false;
	for(int i = 2; i < MAX_A; i++)
		if(isprm[i])
			for(int j = i + i; j < MAX_A; j += i)
				isprm[j] = false;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		int sqa = floor(sqrt(a)), sqb = floor(sqrt(b));
		if(isprm[a] && vis[a]) a = -1;
		for(int j = 2; j <= sqa; j++) if(a % j == 0 && (vis[j] || vis[a / j])) a = -1;
		if(isprm[b] && vis[b]) b = -1;
		for(int j = 2; j <= sqb; j++) if(b % j == 0 && (vis[j] || vis[b / j])) b = -1;
		if(a == -1 && b == -1) { puts("No"); return 0; }
		else if(a == -1) {
			if(isprm[b]) vis[b] = true;
			for(int j = 2; j <= sqb; j++) if(b % j == 0) vis[j] = vis[b / j] = true;
		} else if(b == -1) {
			if(isprm[a]) vis[a] = true; 
			for(int j = 2; j <= sqa; j++) if(a % j == 0) vis[j] = vis[a / j] = true;
		} else {
			top = 0;
			if(a == b && isprm[a]) vis[a] = true;
			for(int j = 2; j <= std::max(sqa, sqb); j++)
				if(a % j == 0 && b % j == 0) {
					if(!vis[j]) stk[top++] = j;
					else { puts("No"); return 0; }
				}
			for(int j = 2; j <= sqa; j++)
				if(a % j == 0 && b % (a / j) == 0 && j != a / j) {
					if(!vis[a / j]) stk[top++] = a / j;
					else { puts("No"); return 0; }
				}
			for(int j = 2; j <= sqb; j++)
				if(b % j == 0 && a % (b / j) == 0 && j != b / j) {
					if(!vis[b / j]) stk[top++] = b / j;
					else { puts("No"); return 0; }
				}
			for(top--; top >= 0; top--) vis[stk[top]] = true;
		}
	}
	puts("Yes");
	return 0;
} /*
4
95 12
13 66
95 66
56 3
*/