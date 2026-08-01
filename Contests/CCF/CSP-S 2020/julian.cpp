#include<cstdio>
using namespace std;
#define ll long long
int T,st1[13]={0,31,28,31,30,31,30,31,31,30,31,30,31},st2[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
ll n;
void doit1(int tp){for(int i=1;i<=12;i++)if(tp<st1[i]){printf("%d %d",tp+1,i);return;}else tp-=st1[i];}
void doit2(int tp){for(int i=1;i<=12;i++)if(tp<st2[i]){printf("%d %d",tp+1,i);return;}else tp-=st2[i];}
void solve()
{
	if(n<1178*1461)
	{
		int nw=4713;
		int tp=n/1461;
		nw-=4*tp;n-=1461*tp;
		if(n<366){doit2(n);printf(" %d BC\n",nw);}
		else for(int i=1;i<=3;i++){if(n-i*365-1<365){doit1(n-i*365-1),printf(" %d BC\n",nw-1);break;}nw--;}
		return;
	}
	n-=1178*1461;
	if(n<366){doit2(n);printf(" 1 BC\n");return;}
	int nw=1;n-=366;
	int tp=n/1461;
	if(tp<395)
	{
		n-=tp*1461;
		nw+=tp*4;
		int s1=n/365;
		if(s1==4)s1=3;
		if(s1<3){doit1(n-s1*365);printf(" %d\n",nw+s1);}
		else {doit2(n-s1*365);printf(" %d\n",nw+s1);}
		return;
	}
	nw=1581;n-=395*1461;
	if(n<365){doit1(n);printf(" %d\n",nw);return;}
	n-=365;nw++;
	if(n<277){doit1(n);printf(" %d\n",nw);return;}
	if(n<355){doit1(n+10);printf(" %d\n",nw);return;}
	n-=355;nw++;
	if(n<365){doit1(n);printf(" %d\n",nw);return;}
	n-=365;nw++;
	int tp1=n/1461;
	if(tp1<4)
	{
		n-=tp1*1461;
		nw+=tp1*4;
		if(n<366){doit2(n);printf(" %d\n",nw);}
		else for(int i=1;i<=3;i++){if(n-i*365-1<365){doit1(n-i*365-1),printf(" %d\n",nw+1);break;}nw++;}
		return;
	}
	n-=4*1461;nw+=16;
	int s1=n/146097;
	nw+=400*s1;n-=1ll*146097*s1;
	if(n<366){doit2(n);printf(" %d\n",nw);return;}
	nw++;n-=366;
	int tp2=n/1461;
	if(tp2<24)
	{
		n-=tp2*1461;
		nw+=tp2*4;
		int s1=n/365;
		if(s1==4)s1=3;
		if(s1<3){doit1(n-s1*365);printf(" %d\n",nw+s1);}
		else {doit2(n-s1*365);printf(" %d\n",nw+s1);}
		return;
	}
	n-=24*1461;nw+=96;
	if(n<365*3)
	{
		int s3=n/365;nw+=s3;n-=s3*365;
		doit1(n);printf(" %d\n",nw);return;
	}
	n-=3*365;nw+=3;
	int s4=n/36524;nw+=100*s4;n-=1ll*36524*s4;
	if(n<365*4)
	{
		int s3=n/365;nw+=s3;n-=s3*365;
		doit1(n);printf(" %d\n",nw);return;
	}
	n-=4*365;nw+=4;
	int tp5=n/1461;
	n-=tp5*1461;
	nw+=tp5*4;
	if(n<366){doit2(n);printf(" %d\n",nw);}
	else for(int i=1;i<=3;i++){if(n-i*365-1<365){doit1(n-i*365-1),printf(" %d\n",nw+1);break;}nw++;}
}
int main()
{
	freopen("julian.in","r",stdin);
	freopen("julian.out","w",stdout);
	scanf("%d",&T);
	while(T--)scanf("%lld",&n),solve();
}
