#include <cstdio>
#include <algorithm>
#include <cmath>

typedef long double LD;
const int N = 7e4 + 5;

class TriangleXor {
public:
	int theArea(int w) {
		LD ans = 0;
		if(!(w & 1)) ans += (LD)w / 4;
		for(int i = 1; i <= w; i++) {
			if(i & 1) ans += ((LD)i / (w + i) - (LD)(i - 1) / (w + i - 1)) * w;
			else ans += ((LD)w * (1 - (LD)(2 * i - 2) / (w + i - 1))) * ((LD)i / (w + i) - (LD)(i - 2) / (w + i - 2)) / 2;
		}
		return floorl(ans);
	}
};