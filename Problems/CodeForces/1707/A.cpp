#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

int n, m;
int a[N];

int out[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        int iq = 0;
        for(int i = n; i >= 1; i--)
            if(a[i] <= iq) out[i] = true;
            else if(iq < m) out[i] = true, iq++;
            else out[i] = false;
        for(int i = 1; i <= n; i++) printf("%d", out[i]);
        puts("");
	}
	return 0;
}