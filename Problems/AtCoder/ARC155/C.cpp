#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2e5 + 5;

int n;
int a[N], b[N];

std::vector<int> g[2], gt[2];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for(int i = 1; i <= n; i++) g[a[i] & 1].push_back(a[i]), gt[b[i] & 1].push_back(b[i]);
	if(g[0].empty()) {
		bool flag = true;
		for(int i = 1; i <= n; i++) flag &= a[i] == b[i];
		puts(flag ? "Yes" : "No");
		return 0;
	}
	int ind = 0, indt = 0;
	for(int i = 1; i <= n - 1; i++) if((a[i] & 1) && (a[i + 1] & 1)) { ind = i; break; }
	for(int i = 1; i <= n - 2; i++) if((a[i] & 1) && (a[i + 2] & 1)) { ind = i; break; }
	for(int i = 1; i <= n - 1; i++) if((b[i] & 1) && (b[i + 1] & 1)) { indt = i; break; }
	for(int i = 1; i <= n - 2; i++) if((b[i] & 1) && (b[i + 2] & 1)) { indt = i; break; }
	if(ind == 0) {
		std::vector<int> v, vt;
		bool flag = true;
		for(int i = 1; i <= n; i++)
			if(a[i] & 1) {
				if(v.size() > 2) std::sort(v.begin(), v.end()), std::sort(vt.begin(), vt.end());
				flag &= v == vt;
				v.clear(), vt.clear();
				flag &= a[i] == b[i];
			} else v.push_back(a[i]), vt.push_back(b[i]);
		if(v.size() > 2) std::sort(v.begin(), v.end()), std::sort(vt.begin(), vt.end());
		flag &= v == vt;
		puts(flag ? "Yes" : "No");
		return 0;
	}
	bool flag = true;
	if(g[0].size() > 2) std::sort(g[0].begin(), g[0].end()), std::sort(gt[0].begin(), gt[0].end());
	std::sort(g[1].begin(), g[1].end()), std::sort(gt[1].begin(), gt[1].end());
	flag &= g[0] == gt[0] && g[1] == gt[1];
	if(indt == 0) flag = false;
	puts(flag ? "Yes" : "No");
	return 0;
} /*
no 0s
no near 1s
only 2 or less 0s
ans has no near 1s
*/