#include <bits/stdc++.h>
using namespace std;

map<string, int> days = {
	{"Monday", 1},
	{"Tuesday", 2},
	{"Wednesday", 3},
	{"Thursday", 4},
	{"Friday", 5}
};

int main() {
	string s;
	cin >> s;
	int x = days[s];
	printf("%d\n", 6 - x);
	return 0;
}