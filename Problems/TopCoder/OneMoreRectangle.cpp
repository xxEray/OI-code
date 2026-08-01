#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
using std::vector;
using std::string;

const int N = 50 + 5;

int xa[N], xb[N], ya[N], yb[N];
int n;

class OneMoreRectangle {
public:
	int maxCover(vector<string> rect, int qa, int qb) {
		n = rect.size();
		for(int i = 1; i <= n; i++) {
			std::istringstream sin(rect[i - 1]);
			sin >> xa[i] >> ya[i] >> xb[i] >> yb[i];
		}
		int ans = 0;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				for(int t = 0; t <= 1; t++) {
					int xl = xa[i], yl = ya[j];
					int xr = xl + (t ? qa : qb), yr = yl + (t ? qb : qa);
					int cnt = 0;
					for(int k = 1; k <= n; k++)
						cnt += (xl <= xa[k] && yl <= ya[k] && xr >= xb[k] && yr >= yb[k]);
					ans = std::max(ans, cnt);
				}
		return ans;
	}
};