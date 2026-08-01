#include<bits/stdc++.h>
using namespace std;
const double eps=1e-8;
double p,q;
int main(){
    int T;scanf("%d",&T); 
    while(T--){
        scanf("%lf%lf",&p,&q);
        if(p-q<eps)puts("N0 M0R3 BL4CK 1CE TEA!");
        else puts("ENJ0Y YOURS3LF!");
    }
    return 0;
} 