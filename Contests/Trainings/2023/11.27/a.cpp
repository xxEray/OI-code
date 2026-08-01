#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

typedef long long LL;

const int N = 1e7 + 5;

bool isprm[N];
std::vector<int> prime;
int phi[N];
void preprocess(int mx) {
	phi[1] = 1;
	for(int i = 2; i <= mx; i++) isprm[i] = true;
	for(int i = 2; i <= mx; i++) {
		if(isprm[i]) prime.push_back(i), phi[i] = i - 1;
		for(int p : prime) {
			if((LL)p * i > mx) break;
			isprm[i * p] = false;
			if(i % p == 0) {
				phi[i * p] = p * phi[i];
				break;
			}
			phi[i * p] = phi[i] * phi[p];
		}
	}
}

LL qpow(LL x, LL y, LL mod) { LL ret = 1; while(true) { if(y & 1) ret = ret * x % mod; if(!(y >>= 1)) return ret; x = x * x % mod; } }

LL f(LL x, LL y) {
	if(y == 1) return 0;
	return qpow(x, f(x, phi[y]) + phi[y], y);
}

int main() {
	preprocess(1e7);
	int T; scanf("%d", &T);
	while(T--) {
		LL x, y;
		x = rand() % 1000 + 2, y = rand() % 1000 + 2;`
		LL val = f(x, y * phi[y]);
		if(!val) val += y * phi[y];
		if(val < phi[y]) puts("hello");
		if(T % 1000000 == 0) puts("done");
		assert(qpow(x, val, y) == val % y);
	}
	return 0;
}