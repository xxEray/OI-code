#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 2000 + 5;
const LL MOD = 1e6 + 3;

char tmp[10000];

LL f[N];

int main() {
	freopen("in.txt", "r", stdin);
	int cnt = 0, flag = true;
	while(true) {
		char c;
		// 正/负号
		c = getchar();
		if(c == '+' || c == '-');
		else if('0' <= c && c <= '9') ungetc(c, stdin);
		else if(c == EOF) break;
		else { flag = false; break; }
		// 数字
		int ret = scanf("%[0-9]", tmp);
		if(ret == EOF) break;
		else if(ret != 1) { flag = false; break; }
		// 运算符（可能为空）
		c = getchar();
		if(c == '+' || c == '-' || c == '*' || c == '/') cnt++;
		else if(c == EOF) break;
		else { flag = false; break; }
	}
	if(!flag) { puts("0"); return 0; }
	// printf("cnt = %d\n", cnt);
	f[0] = f[1] = 1;
	for(int i = 2; i <= cnt; i++)
		for(int j = 1; j <= i; j++)
			(f[i] += f[j - 1] * f[i - j] % MOD) %= MOD;
	printf("%lld\n", f[cnt]);
	return 0;
}