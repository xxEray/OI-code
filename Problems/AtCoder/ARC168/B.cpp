#include <bits/stdc++.h>

const int N = 2.5e5 + 5;

int n;
int a[N];

std::map<int, int> mp;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), mp[a[i]] ^= 1;
	int xor_sum = 0;
	for(int i = 1; i <= n; i++) xor_sum ^= a[i];
	if(xor_sum) { puts("-1"); return 0; }
	while(!mp.empty()) {
		// printf("> %d %d\n", mp.rbegin()->first, mp.rbegin()->second);
		if(!mp.rbegin()->second) mp.erase(mp.rbegin()->first);
		else { printf("%d\n", mp.rbegin()->first - 1); return 0; }
	}
	puts("0");
	return 0;
}