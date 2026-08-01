#include <cstdio>
#include <algorithm>

const int M = 1e6 + 5;
const int N = 30 + 5;
const int S = (1 << 15) + 1;

int m;

int sum[16][S], cnt[S];

bool check(int d, int s) { return (1 << d) > s; }

void print(int d, int s) {
	for(int i = d - 1; i >= 0; i--) printf("%d", (s >> i & 1) + 1);
}

int main() {
	scanf("%d", &m);
	int U = (1 << 15) - 1;
	for(int i = 1; i <= 15; i++)
		for(int j = 1; j <= U; j++) {
			if(!check(i, j)) break;
			sum[i][j] = (sum[i - 1][j >> 1] * 10 + (i & 1) + 1) % m;
			if(!cnt[sum[i][j]]) cnt[sum[i][j]] = j;
		}
	for(int i = 1; i <= 15; i++)
		for(int j = 1; j <= U; j++)
			if(check(i, j) && sum[i][j] == 0) { print(i, j); return 0; }
	for(int i = 1; i <= 15; i++)
		for(int j = 1; j <= U; j++)
			if(check(i, j) && cnt[m - sum[i][j]])
				{ print(i, j), print(15, cnt[m - sum[i][j]]); return 0; }
	puts("Impossible");
	return 0;
}