#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

char s[N];
bool type[N];
int n, m, len;

int f[N][2];

int main() {
	scanf("%d%d", &n, &m);
	gets(s); // 读入这一行剩余内容
	gets(s + 1);
	len = strlen(s + 1);
	if(s[len] == '\n') len--; // 删去换行
	for(int i = 1; i <= len; i++) type[i] = (isalpha(s[i]) || s[i] == ' ');
	int lst = 1;
	for(int i = 1; i <= len; i++) {
		if(type[i] == 0) {
			lst = i + 1;
			f[i][1] = INF;
		} else {
			lst = std::max(lst, i - m + 1);
			f[i][1] = (lst <= 1 ? 1 : std::min(f[lst - 1][0] + 1, f[lst - 1][1] + 1));
		}
		f[i][0] = (i <= n ? 1 : std::min(f[i - n][0] + 1, f[i][1]));
		// printf("f[%d] = {%d, %d}, lst = %d\n", i, f[i][0], f[i][1], lst);
	}
	printf("%d\n", std::min(f[len][0], f[len][1]));
	return 0;
} /*
10 15
On the 11-th of February, 2006 the contest "Timus Top Coders: First Challenge" is held!
*/