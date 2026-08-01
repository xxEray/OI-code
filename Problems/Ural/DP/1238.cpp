#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 100 + 5;
const int INF = 0x3f3f3f3f;

char s[N];
int n;

int f[N][N];
std::pair<int, int> last[N][N];

int size(int x) {
	int ret = 0;
	while(x) ret++, x /= 10;
	return ret;
}

void print(int i, int j) {
	if(i > j) return;
	else if(last[i][j].first == 0)
		for(int k = i; k <= j; k++) putchar(s[k]);
	else if(last[i][j].first == 1) {
		printf("%d(", (j - i + 1) / last[i][j].second);
		print(i, i + last[i][j].second - 1);
		putchar(')');
	} else if(last[i][j].first == 2) {
		print(i, last[i][j].second);
		print(last[i][j].second + 1, j);
	}
}

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int len = 1; len <= n; len++)
		for(int l = 1; l + len - 1 <= n; l++) {
			int r = l + len - 1;
			f[l][r] = len, last[l][r] = {0, 0};
			for(int i = 1; i < len; i++)
				if(len % i == 0) {
					bool flag = true;
					for(int j = l + i; j <= r; j += i)
						flag &= !strncmp(s + l, s + j, i);
					if(flag) {
						int ret = size(len / i) + 2 + f[l][l + i - 1];
						if(f[l][r] > ret) f[l][r] = ret, last[l][r] = {1, i};
					}
				}
			for(int i = l; i < r; i++)
				if(f[l][r] > f[l][i] + f[i + 1][r])
					f[l][r] = f[l][i] + f[i + 1][r], last[l][r] = {2, i};
		}
	print(1, n);
	return 0;
}