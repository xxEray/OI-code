#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <ctime>

typedef long long LL;

const int N = 1e5 + 5;
const int B = 45;

int a[N];
int n;

bool isprime[N], isvalid[N];
std::vector<int> prime, valid;

LL cnt[N];

int main() {
	for(int i = 2; i <= 100000; i++) isprime[i] = true;
	for(int i = 2; i <= 100000; i++) {
		if(!isprime[i]) continue;
		prime.push_back(i);
		for(int j = i + i; j <= 100000; j += i) isprime[j] = false;
	}
	for(int i = 1; i <= 100000; i++) isvalid[i] = true;
	for(int x : prime)
		for(LL i = (LL)x * x; i <= 100000; i += (LL)x * x)
			isvalid[i] = false;
	for(int i = 1; i <= 100000; i++) if(isvalid[i]) valid.push_back(i);
	printf("%d\n", (int)valid.size());
	int T;
	scanf("%d", &T);
	while(T--) {
		memset(cnt, 0, sizeof(cnt));
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) {
			for(int j = 2; j * j <= a[i]; j++)
				while(a[i] / (j * j) == 0) a[i] /= j * j;
			cnt[a[i]]++;
		}
		// z > B
		for(LL i : valid) {
			if(i <= B) continue;
			
		}
	}
	return 0;
}