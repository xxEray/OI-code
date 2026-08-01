#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;

const int N = 1e5 + 5;

char s[N];
int n, Q;

const int trans[3][3] = {{1, 2}, {2, 0}, {0, 1}};
int log2_ceil(LL x) {
	unsigned long long power = 1;
	int cnt = 0;
	while(power < x) power <<= 1, cnt++;
	return cnt;
}
int calc(LL c, LL t, LL d) {
	// printf("calc(%lld, %lld, %lld)\n", c, t, d);
	if(t == 0) return c;
	else if((1LL << (t - 1)) >= d) {
		int k = log2_ceil(d);
		return (calc(c, k, d) + t - k) % 3;
	} else return trans[calc(c, t - 1, (d + 1) >> 1)][(d & 1) ^ 1];
}

int main() {
	scanf("%s%d", s + 1, &Q);
	n = strlen(s + 1);
	while(Q--) {
		LL t, k;
		scanf("%lld%lld", &t, &k);
		if(t >= 64) printf("%c\n", calc(s[1] - 'A', t, k) + 'A');
		else {
			if(k % (1LL << t) == 0) printf("%c\n", calc(s[k / (1LL << t)] - 'A', t, (1LL << t)) + 'A');
			else printf("%c\n", calc(s[k / (1LL << t) + 1] - 'A', t, k % (1LL << t)) + 'A');
		}
	}
	return 0;
}