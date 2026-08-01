// 	author:LGM_Joanna_

#include <bits/stdc++.h>
#define marry return
#define int long long
#define lowbit(x) (x&-x)
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<48||ch>57)f=ch=='-'?-1:1,ch=getchar();
	while(ch>=48&&ch<=57)x=x*10+(ch^48),ch=getchar();
	return x*f;}
using namespace std;

const int inf=1e18;
const int F=0;
const int mod=114514;

int n,m,q;
int nowa[500005],nowb[500005];
int a[500005],b[5000005];
int mx[500005],mn[500005];
inline bool check(bool flag)
{
	if(flag)
	{
		int top=1;
		mx[1]=mn[1]=a[1];
		for(int i=2;i<=n;++i)
		{
			mn[top]=min(mn[top],a[i]);
			if(a[i]>mx[top])
				mx[++top]=a[i],mn[top]=a[i];			
		}
		int res=inf,now=1;
		for(int i=1;i<=m;++i)
		{
			if(b[i]>=mx[now])
				marry false;
			while(b[i]<mn[now]&&now<top)
				++now;
			if(now==top)
			{
				res=i;
				break;
			}
		}
		reverse(a+1,a+n+1);
		reverse(b+1,b+m+1);
		res=m-res+1;
		top=1;
		mx[1]=a[1],mn[1]=a[1];
		for(int i=2;i<=n;++i)
		{
			mn[top]=min(mn[top],a[i]);
			if(a[i]>mx[top])
				mx[++top]=a[i],mn[top]=a[i];
		}
		now=1;
		for(int i=1;i<=m;++i)
		{
			if(b[i]>=mx[now])
				marry false;
			while(b[i]<mn[now]&&now<top)
				++now;
			if(now==top)
			{
				if(i<=res)
					marry true;
				else
					marry false;
			}
		}
		marry false;
	}
	else
	{
		int top=1;
		mx[1]=b[1],mn[1]=b[1];
		for(int i=2;i<=m;++i)
		{
			if(b[i]>mx[top])
				mx[++top]=b[i],mn[top]=b[i];
			else
				mn[top]=min(mn[top],b[i]);
		}

		int res=inf,now=1;
		for(int i=1;i<=n;++i)
		{
			if(a[i]>=mx[now])
				marry false;
			while(a[i]<mn[now]&&now<top)
				++now;
			if(now==top)
			{
				res=i;
				break;
			}
		}
		reverse(a+1,a+n+1);
		reverse(b+1,b+m+1);
		res=n-res+1;
		top=1;
		mx[1]=b[1],mn[1]=b[1];
		for(int i=2;i<=m;++i)
		{
			if(b[i]>mx[top])
				mx[++top]=b[i],mn[top]=b[i];
			else
				mn[top]=min(mn[top],b[i]);
		}
		now=1;
		for(int i=1;i<=n;++i)
		{
			if(a[i]>=mx[now])
				marry false;
			while(a[i]<mn[now]&&now<top)
				++now;
			if(now==top)
			{
				if(i<=res)
					marry true;
				else
					marry false;
			}
		}
		marry false;
		
	}
}

signed main()
{
	
	int c=read();
	n=read(),m=read(),q=read();
	for(int i=1;i<=n;++i)
		nowa[i]=read();
	for(int i=1;i<=m;++i)
		nowb[i]=read();
	for(int T=0;T<=q;++T)
	{
		for(int i=1;i<=n;++i)
			a[i]=nowa[i];
		for(int i=1;i<=m;++i)
			b[i]=nowb[i];
		int kx,ky;
		if(T)
		{
			kx=read(),ky=read();
			for(int i=1;i<=kx;++i)
			{
				int p=read();
				a[p]=read();
			}
			for(int i=1;i<=ky;++i)
			{
				int p=read();
				b[p]=read();	
			}
		}	
		int mxa=0,mxb=0;
		for(int i=1;i<=n;++i)
			mxa=max(mxa,a[i]);
		for(int i=1;i<=m;++i)
			mxb=max(mxb,b[i]);
		if(a[1]>b[1]&&a[n]>b[m]&&mxa>mxb)
		{
			if(check(1))
				printf("1");
			else
				printf("0");
		}
		else if(a[1]<b[1]&&a[n]<b[m]&&mxa<mxb)
		{
			if(check(0))
				printf("1");
			else
				printf("0");
		}
		else
			printf("0");
	}
	
	marry F;
}
