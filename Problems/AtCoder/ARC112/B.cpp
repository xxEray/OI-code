#include <cstdio>
#include <algorithm>

typedef long long LL;

#define make_range(id, l_, r_)\
if((l_) > (r_)) l##id = (r_), r##id = (l_);\
else l##id = (l_), r##id = (r_);

#define debug() \
	printf("[%lld .. %lld]\n", l1, r1);\
	printf("[%lld .. %lld]\n", l2, r2);\
	printf("[%lld .. %lld]\n", l3, r3);\
	printf("[%lld .. %lld]\n-----\n", l4, r4);

#define merge_range(a, b) merge_range_(l##a, r##a, l##b, r##b)

void merge_range_(LL &l1, LL &r1, LL &l2, LL &r2) {
	if(l1 >= l2) std::swap(l1, l2), std::swap(r1, r2);
	if(r1 >= r2) l2 = 1, r2 = 0;
	else if(r1 < l2) ;
	else r1 = r2, l2 = 1, r2 = 0;
}

int main() {
	LL b, c;
	scanf("%lld%lld", &b, &c);
	LL l1, r1, l2, r2, l3, r3, l4, r4;
	make_range(1, b, b - c / 2);
	make_range(2, -(b - (c - 1) / 2), -b);
	make_range(3, -b - (c - 1) / 2, -b);
	make_range(4, -(-b - (c - 2) / 2), b);
	// debug();
	merge_range(1, 2);
	merge_range(1, 3);
	merge_range(1, 4);
	merge_range(2, 3);
	merge_range(2, 4);
	merge_range(3, 4);
	merge_range(1, 2);
	merge_range(1, 3);
	merge_range(1, 4);
	merge_range(2, 3);
	merge_range(2, 4);
	merge_range(3, 4);
	printf("%lld\n", r1 - l1 + r2 - l2 + r3 - l3 + r4 - l4 + 4);
	return 0;
}