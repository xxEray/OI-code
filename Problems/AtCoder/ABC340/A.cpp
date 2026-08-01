#include <bits/stdc++.h>

int main() {
	int A, B, D;
	scanf("%d%d%d", &A, &B, &D);
	for(int i = A; i <= B; i += D) printf("%d ", i);
	return 0;
}