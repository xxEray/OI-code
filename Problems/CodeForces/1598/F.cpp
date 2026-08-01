#include <cstdio>
#include <algorithm>
#include <cstring>

const int N = 20 + 5;
const int S = (1 << 20) + 5;
const int LEN = 4e5 + 5;
const int INF = 0x3f3f3f3f;

int len[N];
char s[N][LEN];
int n;

int f[S], g[N][LEN], sumsg[N], sum[S], minp[N];

void updt(int &a, int b) { if(b > a) a = b; }

int main() {
	memset(f, ~0x3f, sizeof(f));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1), len[i] = strlen(s[i] + 1);
	for(int i = 1; i <= n; i++) {
		int t = INF;
		for(int j = 1; j <= len[i]; j++) {
			sumsg[i] += (s[i][j] == '(' ? 1 : -1);
			t = std::min(t, sumsg[i]);
			if(sumsg[i] <= 0 && -sumsg[i] + t >= 0) g[i][-sumsg[i]]++;
		}
		minp[i] = t;
	}
	int U = (1 << n) - 1;
	for(int st = 0; st <= U; st++)
		for(int j = 1; j <= n; j++)
			if(st >> (j - 1) & 1)
				sum[st] += sumsg[j];
	int ans = 0;
	f[0] = 0;
	for(int st = 0; st < U; st++)
		if(sum[st] >= 0)
			for(int j = 1; j <= n; j++)
				if(!(st >> (j - 1) & 1)) {
					updt(ans, f[st] + g[j][sum[st]]);
					if(sum[st] + minp[j] >= 0) updt(f[st | (1 << (j - 1))], f[st] + g[j][sum[st]]);
				}
	printf("%d\n", ans);
	return 0;
}