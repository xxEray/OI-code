#include <cstdio>
#include <algorithm>
#include <cmath>

const double eps = 1e-8;

const double D = 1e-4;

class FastSpider {
public:
	int findTime(double vs, double vp) {
		double ss = 0, sp = 1; // s_spider, s_person
		double timel = 0;
		while(ss < sp) {
			ss = ss * (sp + vp * D) / sp;
			ss += vs * D;
			sp += vp * D;
			timel += D;
		}
		ss = 0, sp = 1;
		double timer = 0;
		while(ss < sp) {
			ss += vs * D;
			ss = ss * (sp + vp * D) / sp;
			sp += vp * D;
			timer += D;
		}
		return round((timel + timer) / 2);
	}
};

int main() {
	FastSpider T;
	printf("%d\n", T.findTime(0.5,
4.8877377
));
	return 0;
}