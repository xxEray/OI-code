#include <bits/stdc++.h>

typedef long long LL;

const int N = 2000 + 5;
const int V = 1800 + 5;
const int SQRT_N = 50;
const int D = SQRT_N * 1800;

const char mapping[2][2] = {{'L',  'D'}, {'U', 'R'}};

int n;
struct Node { int val, id; } a[N];

std::bitset<2 * SQRT_N * V> bs[N];
bool solve(std::vector<int> &seq, int A) {
	auto base = [&](int i) { return (LL)i * A / n; };
	auto shift = [](std::bitset<2 * SQRT_N * V> &tmp, LL offset) { return offset > 0 ? tmp >> offset : tmp << -offset; };
	bs[0].reset(), bs[0][D] = 1;
	for(int i = 1; i <= n; i++) {
		LL offset = base(i) - base(i - 1);
		bs[i] = (shift(bs[i - 1], offset) << a[i].val) | (shift(bs[i - 1], offset) >> a[i].val);
	}
	if(!bs[n][D]) return false;
	LL j = D;
	for(int i = n; i >= 1; i--) {
		LL offset = base(i) - base(i - 1);
		if((shift(bs[i - 1], offset) >> a[i].val)[j]) j += a[i].val + base(i) - base(i - 1), seq.emplace_back(0);
		else j += -a[i].val + base(i) - base(i - 1), seq.emplace_back(1);
	}
	assert(j == D);
	std::reverse(seq.begin(), seq.end());
	// printf("A=%d: ", A); for(int i = 1; i <= n; i++) printf("%+d ", seq[i - 1] ? a[i].val : -a[i].val); puts("");
	return true;
}

std::vector<int> seqA, seqB;
char out[N];

int main() {
	int A, B;
	scanf("%d%d%d", &n, &A, &B);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i].val), a[i].id = i;
	std::random_shuffle(a + 1, a + n + 1);
	std::tie(A, B) = std::make_pair(A + B, A - B);
	bool flag = solve(seqA, A) && solve(seqB, B);
	if(!flag) puts("No");
	else {
		puts("Yes");
		for(int i = 1; i <= n; i++) out[a[i].id] = mapping[seqA[i - 1]][seqB[i - 1]];
		for(int i = 1; i <= n; i++) putchar(out[i]);
	}
	return 0;
} /*
3 2 -2
1 2 3
*/