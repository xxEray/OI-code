#include <bits/stdc++.h>

typedef long long LL;

const int N = 3e5 + 5;

int n;
int a[N], b[N];

LL sum[N];

std::set<int> va, vb;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]), sum[i] = sum[i - 1] + (LL)a[i] * b[i];
	LL ans = 1, now = 0;
	va.emplace(1), vb.emplace(1), now++;
	for(int i = 2; i <= n; i++) {
		int eva = 0, evb = 0;
		if(a[i] > a[i - 1]) {
			int l = 1, r = i - 1;
			while(l < r) {
				int mid = (l + r) >> 1;
				if(sum[i - 1] - sum[mid - 1] <= (LL)a[i] * b[i - 1]) r = mid;
				else l = mid + 1;
			}
			if(sum[i - 1] - sum[l - 1] == (LL)a[i] * b[i - 1] && vb.count(l)) eva = l;
		}
		if(b[i] > b[i - 1]) {
			int l = 1, r = i - 1;
			while(l < r) {
				int mid = (l + r) >> 1;
				if(sum[i - 1] - sum[mid - 1] <= (LL)b[i] * a[i - 1]) r = mid;
				else l = mid + 1;
			}
			if(sum[i - 1] - sum[l - 1] == (LL)b[i] * a[i - 1] && va.count(l)) evb = l;
		}
		if(a[i] == a[i - 1] && b[i] == b[i - 1]);
		else if(a[i] != a[i - 1] && b[i] == b[i - 1]) va.clear(), now = vb.size();
		else if(b[i] != b[i - 1] && a[i] == a[i - 1]) vb.clear(), now = va.size();
		else va.clear(), vb.clear(), now = 0;
		if(eva) now += !va.count(eva) && !vb.count(eva), va.emplace(eva);
		if(evb) now += !va.count(evb) && !vb.count(evb), vb.emplace(evb);
		va.emplace(i), vb.emplace(i), now++;
		ans += now;
		// printf("%d: now = %lld\n", i, now);
		// printf("  va: "); for(int x : va) printf("%d ", x); puts("");
		// printf("  vb: "); for(int x : vb) printf("%d ", x); puts("");
	}
	printf("%lld\n", ans);
	return 0;
}