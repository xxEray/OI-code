#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 4000 + 5;
const LL MOD = 998244353;

int n, Q, seqsize;
bool seq[N]; // W -> true, E -> false
char s[10];
int a[N], asize;

LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }

void calc() {
	asize = 2;
	a[0] = 0, a[1] = 1;
	for(int i = 1; i <= seqsize; i++)
		if(seq[i]) a[asize - 1]++;
		else if(a[asize - 1] == 1) a[asize - 2]++;
		else a[asize - 1]--, a[asize] = 1, a[asize + 1] = 1, asize += 2;
	LL x = a[asize - 1], y = 1;
	for(int i = asize - 2; i >= 0; i--) {
		// At first, x/y = a_{k + 1}
		std::swap(x, y);
		// Now, x/y = 1/a_{k + 1}
		x += a[i] * y;
		// Then, x/y = a_k + 1/a_{k + 1}
		x /= gcd(x, y), y /= gcd(x, y);
		x %= MOD, y %= MOD;
	}
	printf("%lld %lld\n", x, y);
}

int main() {
	freopen("code.in", "r", stdin);
	freopen("code.out", "w", stdout);
	scanf("%d%d%s", &n, &Q, s);
	for(int i = 0; i < n; i++) seq[i + 1] = (s[i] == 'W');
	seqsize = n;
	calc();
	while(Q--) {
		int l, r;
		scanf("%s", s);
		if(s[0] == 'A') { // APPEND
			scanf("%s", s);
			seq[++seqsize] = (s[0] == 'W');
		} else if(s[0] == 'F') { // FLIP
			scanf("%d%d", &l, &r);
			for(int i = l; i <= r; i++) seq[i] = !seq[i];
		} else { // REVERSE
			scanf("%d%d", &l, &r);
			std::reverse(seq + l, seq + r + 1);
		}
		calc();
	}
	return 0;
}