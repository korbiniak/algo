#include <bits/stdc++.h>


using namespace std;

const int roz=(1<<18);
int tt[roz * 2 +10][2];

void dd(int lo,int hi,int u,int a,int b,int val)
{
    if(lo==a && b==hi)
    {
        tt[u][0]+=val;
        tt[u][1]+=(hi-lo)*val;
        return;
    }
    if(b<=a) return;
    int mid=(lo+hi)/2;
    dd(lo,mid,u*2,a,min(b,mid),val);
    dd(mid,hi,u*2+1,max(a,mid),b,val);
    tt[u][1]=tt[u*2][1]+tt[u*2+1][1]+(hi-lo)*tt[u][0];
    return;
}

int qq(int lo,int hi,int u,int a,int b)
{
    if(lo==a && b==hi)
    {
        return tt[u][1];
    }
    if(b<=a) return 0;
    int mid=(lo+hi)/2;
    int l=qq(lo,mid,u*2,a,min(b,mid));
    int r=qq(mid,hi,u*2+1,max(a,mid),b);
    return l+r+(b-a)*tt[u][0];
}

int main()
{
    int q; cin>>q;
    while(q--)
    {
        int t; cin>>t;
        if(t==1)
        {
            int lo,hi,val;
            cin>>lo>>hi>>val;
            dd(0,roz/2,1,lo,hi+1,val);
        }
        else
        {
            int lo,hi; cin>>lo>>hi;
            cout<<qq(0,roz/2,1,lo,hi+1)<<endl;
        }
    }
    return 0;
}
