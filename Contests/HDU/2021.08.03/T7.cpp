#include <cstdio>
#include <algorithm>

typedef long long LL;

const LL MOD = 1e9 + 7;
const LL inv2 = (MOD + 1) / 2;
const LL inv6 = (MOD + 1) / 6;

LL n;

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%lld", &n);
        n %= MOD;
        LL mx = 0, mn = 0;
        LL ret1 = n * (n + 1) % MOD * inv2 % MOD; // 1 + 2 + ... + n
        LL ret2 = n * (n + 1) % MOD * (2 * n + 1) % MOD * inv6 % MOD; // 1^2 + 2^2 + 3^2 + ... + n^2
        // LL ret3 = ret1 * ret1 % MOD; // 1^3 + 2^3 + ... + n^3
        LL ret4 = (ret1 + MOD - 1) % MOD; // 2 + 3 + 4 + ... + n
        LL ret5 = (ret2 + MOD - 1) % MOD; // 2^2 + 3^2 + 4^2 + ... + n^2
        // printf("%lld %lld %lld %lld: \n", ret1, ret2, ret3, ret4);
        mn = (ret1 * ret2 % MOD + ret4 * ret4 % MOD + ret4 * ret5 % MOD) % MOD;
        mx = n * n % MOD * ret2 % MOD * ret1 % MOD;
        printf("%lld\n%lld\n", mn, mx);
    }
    return 0;
}