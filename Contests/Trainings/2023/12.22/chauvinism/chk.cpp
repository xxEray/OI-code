#include <bits/stdc++.h>

#define filename "chauvinism"

const int N = 1e5 + 5;
int a[N], b[N], c[N];
char s[N];

int main() {
	FILE *fin = fopen(filename ".in", "r"), *fout = fopen(filename ".out", "r"), *fans = fopen(filename ".ans", "r");
	long long out, ans;
	fscanf(fout, "%lld", &out), fscanf(fans, "%lld", &ans);
	if(out != ans) {
		fprintf(stderr, "participant's answer and jury's answer differ.\n");
		return 1;
	}
	int n, K;
	fscanf(fin, "%d%d", &n, &K);
	for(int i = 1; i <= n; i++) fscanf(fin, "%d", &a[i]);
	for(int i = 1; i <= n; i++) fscanf(fin, "%d", &b[i]);
	fscanf(fout, "%s", s + 1);
	int cnt = 0;
	for(int i = 1; i <= n; i++)
		if(s[i] == 'A') cnt++, c[i] = a[i];
		else c[i] = b[i];
	long long sum = 0, mn = 0, ret = 0;
	for(int i = 0; i <= n; i++) {
		sum += c[i];
		mn = std::min(mn, sum);
		ret = std::max(ret, sum - mn);
	}
	if(cnt != K) {
		fprintf(stderr, "the number of A's doesn't equal to K.\n");
		return 1;
	}
	if(ret != out) {
		fprintf(stderr, "the cost of participant's solution doesn't equal to the cost given by the participant.\n", out);
		return 1;
	}
	fprintf(stderr, "Accepted.\n");
	return 0;
}