#include <cstdio>
#include <algorithm>

int cnt[15];

int main() {
	for(int i = 1; i <= 5; i++) { int x; scanf("%d", &x); cnt[x]++; }
	int cnt2 = 0, cnt3 = 0;
	for(int i = 1; i <= 13; i++)
		if(cnt[i] == 2) cnt2++;
		else if(cnt[i] == 3) cnt3++;
	puts(cnt2 == 1 && cnt3 == 1 ? "Yes" : "No");
	return 0;
}