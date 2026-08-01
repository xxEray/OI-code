#include <cstdio>
#include <algorithm>
#include <cassert>

const int N = 2e5 + 5;

int a[N], l[N], r[N];
bool in[N], out[N], ok[N];
int f[N], another[N], sum[N];
int n;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) r[a[i]] = i;
	for(int i = n; i >= 1; i--) l[a[i]] = i;
	for(int i = 1; i <= n; i++) if(l[i] == r[i]) l[i] = r[i] = 0;
	for(int i = 1; i <= n; i++) in[l[i]] = out[r[i]] = true, another[l[i]] = r[i];
	int cnt = 0, ans = 0, right = 0;
	for(int i = 1; i <= n; i++) {
		cnt += in[i] - out[i];
		if(!in[i] && !out[i]) continue;
		else if(in[i]) {
			assert(i != right), assert(another[i] != right);
			if(another[i] < right) continue;
			int ret;
			if(i < right) ret = another[i] - right - 1;
			else ret = another[i] - i - 1;
			assert(ret >= 0);
			if(ret == 0) continue;
			right = another[i];
			// printf("%d ", ret);
			ans += ret;
		} else if(out[i]) continue;
		else assert(false);
	}
	printf("%d\n", ans);
	return 0;
}