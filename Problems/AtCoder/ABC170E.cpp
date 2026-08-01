#include <cstdio>
#include <set>

const int N = 2e5 + 5;

int rating[N]; // the rating of the children
int n, m;

int belong[N]; // the kindergarten of each child

std::multiset<int> kinder_info[N]; // the informations of the kindergartens
std::multiset<int> answers;

#define erase_once(filter, elem) (filter).erase((filter).lower_bound((elem)))

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%d%d", &rating[i], &belong[i]);
		kinder_info[belong[i]].insert(rating[i]);
	}
	for(int i = 1; i <= (int)2e5; i++)
		if(!kinder_info[i].empty())
			answers.insert(*kinder_info[i].crbegin());
	for(int i = 1; i <= m; i++) {
		int x, y; // change child x to kindergarten y
		scanf("%d%d", &x, &y);
		if(belong[x] == y) continue;
		erase_once(answers, *kinder_info[belong[x]].crbegin());
		if(!kinder_info[y].empty()) erase_once(answers, *kinder_info[y].crbegin());
		erase_once(kinder_info[belong[x]], rating[x]);
		kinder_info[y].insert(rating[x]);
		if(!kinder_info[belong[x]].empty()) answers.insert(*kinder_info[belong[x]].crbegin());
		answers.insert(*kinder_info[y].crbegin());
		belong[x] = y;
		printf("%d\n", *answers.cbegin());
	}
	return 0;
}