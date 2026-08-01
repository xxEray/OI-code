#include <cstdio>
#include <algorithm>
#include <string>

const int N = 6000 + 5;

char s[N];
int n;

int a[N], b[N], another[N], id[N];
std::string f[N], tmp;

int main() {
	scanf("%d%s", &n, s + 1);
	for(int i = 1, ca = 0, cb = 0; i <= n * 2; i++)
		if(s[i] == 'a') a[++ca] = i, id[i] = ca;
		else if(s[i] == 'b') b[++cb] = i, id[i] = cb;
	for(int i = 1; i <= n; i++) another[a[i]] = b[i], another[b[i]] = a[i];
	a[n + 1] = b[n + 1] = 2 * n + 1, id[2 * n + 1] = n + 1;
	for(int i = n; i >= 1; i--) {
		f[i] = f[i + 1];
		if(a[i] < b[i]) {
			for(int j = i + 1; j <= n + 1; j++) if(std::min(a[j], b[j]) > b[i]) f[i] = std::max(f[i], "ab" + f[j]);
		} else {
			int j = b[i], k = b[i];
			tmp.clear();
			for(; j <= k; j++) {
				if(another[j] >= b[i]) tmp.push_back(s[j]);
				if(s[j] == 'b') k = std::max(k, another[j]);
			}
			f[i] = std::max(f[i], tmp + f[id[k + 1]]);
		}
	}
	// for(int i = n; i >= 1; i--) printf("f[%d] = %s\n", i, f[i].c_str());
	printf("%s\n", f[1].c_str());
	return 0;
} /*

*/
