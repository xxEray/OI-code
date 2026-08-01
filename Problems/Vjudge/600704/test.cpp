#include <bits/stdc++.h>

const int N = 1e6;
const double eps = 1e-6;

struct Node {
	double x, y;
	double square_length() const { return x * x + y * y; }
} a[N + 5];
double cross(Node x, Node y) { return x.x * y.y - x.y * y.x; }
bool operator<(const Node &x, const Node &y) {
	double val = cross(x, y);
	return std::abs(val) <= eps ? x.square_length() < y.square_length() : val < 0;
}

int main() {
    std::mt19937 mt(std::random_device{}());
    std::uniform_real_distribution<double> rnd(-1e18, 1e18);
    for(int i = 1; i <= N; i++) a[i].x = rnd(mt), a[i].y = rnd(mt);
	std::sort(a + 1, a + N + 1);
	printf("%.5f %.5f\n", a[1].x, a[1].y);
	printf("%.5f %.5f\n", a[N].x, a[N].y);
    return 0;
}