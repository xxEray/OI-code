#include <bits/stdc++.h>

typedef long long LL;

const int N = 2e6 + 5;

int n, m;
struct Node { LL t, d; } a[N], b[N];

LL ts[2 * N], ad[2 * N], bd[2 * N];

std::vector<std::pair<LL, LL>> vct[2];

void add(LL l, LL r) {
	assert((l & 1) == (r & 1));
	if(l > r) std::swap(l, r);
	// printf("add [%lld, %lld]\n", l, r);
	vct[l & 1].emplace_back(l, 1), vct[l & 1].emplace_back(r + 2, -1);
}

void addboth(LL l, LL r) {
	if(l > r) std::swap(l, r);
	// printf("addboth [%lld, %lld]\n", l, r);
	int fix = ((l & 1) != (r & 1));
	vct[l & 1].emplace_back(l, 1), vct[l & 1].emplace_back(r - fix + 2, -1);
	vct[~l & 1].emplace_back(l + 1, 1), vct[~l & 1].emplace_back(r - !fix + 2, -1);
}

int main() {
	freopen("robot.in", "r", stdin);
	freopen("robot.out", "w", stdout);
	int T; scanf("%d", &T);
	while(T--) {
		vct[0].clear(), vct[1].clear();
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%lld%lld", &a[i].d, &a[i].t), a[i].t += a[i - 1].t, ts[i] = a[i].t;
		scanf("%d", &m);
		for(int i = 1; i <= m; i++) scanf("%lld%lld", &b[i].d, &b[i].t), b[i].t += b[i - 1].t, ts[i + n] = b[i].t;
		std::sort(ts + 1, ts + n + m + 1);
		for(int i = 1, j = 1; i <= n + m; i++) {
			while(j <= n && a[j].t < ts[i]) j++;
			ad[i] = a[j].d;
		}
		for(int i = 1, j = 1; i <= n + m; i++) {
			while(j <= m && b[j].t < ts[i]) j++;
			bd[i] = b[j].d;
		}
		// for(int i = 1; i <= n + m; i++) printf("t=%lld ad=%lld bd=%lld\n", ts[i], ad[i], bd[i]);
		LL suma = 0, sumb = 0;
		LL lastt = 0;
		add(0, 0);
		for(int i = 1; i <= n + m; i++) {
			if(i > 1 && ts[i] == ts[i - 1]) continue;
			if(ad[i] == bd[i]) {
				vct[(suma - sumb) & 1].emplace_back(suma - sumb, ts[i] - lastt);
				vct[(suma - sumb) & 1].emplace_back(suma - sumb + 2, -(ts[i] - lastt));
				// printf("addspot [%lld] %lld\n", suma - sumb, ts[i] - lastt - 1);
			} else if(std::abs(ad[i]) == 1 && std::abs(bd[i]) == 1)
				add(suma - sumb + (ad[i] == 1 ? -2 : 2), suma - sumb + (ad[i] == 1 ? -2 : 2) * (ts[i] - lastt));
			else if(ad[i] == 1 || bd[i] == -1) addboth(suma - sumb - 1, suma - sumb - (ts[i] - lastt));
			else if(ad[i] == -1 || bd[i] == 1) addboth(suma - sumb + 1, suma - sumb + (ts[i] - lastt));
			suma -= (ts[i] - lastt) * ad[i], sumb -= (ts[i] - lastt) * bd[i];
			lastt = ts[i];
		}
		// printf("vct[0]: "); for(auto [x, y] : vct[0]) printf("(%lld,%lld) ", x, y); puts("");
		// printf("vct[1]: "); for(auto [x, y] : vct[1]) printf("(%lld,%lld) ", x, y); puts("");
		std::sort(vct[0].begin(), vct[0].end()), std::sort(vct[1].begin(), vct[1].end());
		LL ans = 0, sum = 0;
		for(int i = 0; i < (int)vct[0].size(); i++) sum += vct[0][i].second, ans = std::max(ans, sum);
		sum = 0;
		for(int i = 0; i < (int)vct[1].size(); i++) sum += vct[1][i].second, ans = std::max(ans, sum);
		printf("%lld\n", ans);
	}
	return 0;
}