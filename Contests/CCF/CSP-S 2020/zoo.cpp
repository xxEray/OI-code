#include<cstdio>
using namespace std;
#define ul unsigned long long
int n,m,c,k,s,b,c1;
ul tp,a,as,s2,s3;
int main()
{
	freopen("zoo.in","r",stdin);
	freopen("zoo.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&c,&k);
	for(int i=1;i<=n;i++)scanf("%llu",&a),tp|=a;
	s2=k<64?((1ull<<k)-1):-1;s3=s2;
	for(int i=1;i<=m;i++)scanf("%d%d",&s,&b),s2&=s3^(1ull<<s);
	tp|=s2;
	as=1;
	for(int i=1;i<=k;i++,tp>>=1)if(tp&1)as*=2,c1++;
	if(c1==64&&!n){printf("18446744073709551616\n");return 0;}
	as-=n;
	printf("%llu\n",as);
}
