#include <bits/stdc++.h>

const int N = 2e5 + 5;

int n;

std::vector<int> prime;
bool isprm[N];
int mpf[N]; // minimum prime factor
void sieve(int mx) {
	for(int i = 2; i <= mx; i++) isprm[i] = true;
	for(int i = 2; i <= mx; i++) {
		if(isprm[i]) prime.emplace_back(i), mpf[i] = i;
		for(int p : prime) {
			if((long long)p * i > mx) break;
			isprm[p * i] = false;
			mpf[i * p] = p;
			if(i % p == 0) break;
		}
	}
}

int cpm(int x) { // count prime factor
	int ret = 0;
	while(x > 1) {
		int factor = mpf[x];
		while(mpf[x] == factor) x /= factor;
		ret++;
	}
	return ret;
}

int main() {
	sieve(2e5);
	long long ans = 0;
	for(int i = 1; i <= 200000; i++) ans += (1 << cpm(i));
	printf("%lld\n", ans);
	return 0;
}