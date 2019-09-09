#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define M 1000000007
#define ll long long
#define REP(i,a,b) for(ll i=a;i<b;i++)
#define REPI(i,a,b) for(ll i=b-1;i>=a;i--)
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define G(a,b) get<a>(b)
#define VI vector<int>
#define VLL vector<long long>

#define o_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define o_setll tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>
//member functions :
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set

ll modI(ll a, ll m);
ll gcd(ll a, ll b);
ll powM(ll x, unsigned ll y, unsigned ll m);
void pairsort(int a[], int b[], int n);
void pairsortll(ll a[],ll b[],ll n);
ll logint(ll x,ll y);


ll gcd(ll x,ll y)
{
    if(x==0) return y;
    return gcd(y%x,x);
}

ll powM(ll x,ll y,ll m)
{
    if(y==0) return 1;
    ll p=powM(x,y/2,m)%m;
    p=(p*p)%m;
    return (y%2==0)?p:(x*p)%m;
}

ll modI(ll a, ll m)
{
    ll m0=m,y=0,x=1;
    if(m==1) return 0;
    while(a>1)
    {
        ll q=a/m;
        ll t=m;
        m=a%m;
        a=t;
        t=y;
        y=x-q*y;
        x=t;
    }
    if(x<0) x+=m0;
    return x;
}

void pairsort(int a[],int b[],int n)
{
    pair<int,int> v[n];
    REP(i,0,n)
    {
        v[i].F=a[i];
        v[i].S=b[i];
    }
    sort(v,v+n);
    REP(i,0,n)
    {
        a[i]=v[i].F;
        b[i]=v[i].S;
    }
}

void pairsortll(ll a[],ll b[],ll n)
{
    pair<ll,ll> v[n];
    REP(i,0,n)
    {
        v[i].F=a[i];
        v[i].S=b[i];
    }
    sort(v,v+n);
    REP(i,0,n)
    {
        a[i]=v[i].F;
        b[i]=v[i].S;
    }
}

ll logint(ll x,ll y)
{
    ll ans=0;
    ll a=1;
    for(ll i=0;i<=x;i++)
    {
        if(x<a)
        {
            return ans;
        }
        ans++;
        a*=y;
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    /*
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    */

    static ll fct[200005];
    fct[0]=1;
    REP(i,1,200005)
    {
        fct[i]=fct[i-1]*i;
        fct[i]%=M;
    }
    static ll pr[200005];
    static ll dpr[200005];
    REP(i,2,200005)
    {
        if(pr[i]==0)
        {
            for(ll j=i;j<200005;j+=i)
            {
                if(pr[j]==0)
                {
                    pr[j]=i;
                }
            }
        }
    }
    dpr[1]=1;
    dpr[2]=1;
    dpr[3]=2;
    REP(i,4,2005)
    {
        dpr[i]=2*i;
        REP(j,1,i)
        {
            if(j*j>i) break;
            else if(i%j==0)
            {
                if(j*j==i)
                {
                    dpr[i]-=j;
                }
                else
                {
                    dpr[i]-=j;
                    dpr[i]-=i/j;
                }
            }
        }
    }
    ll q,k;
    cin>>q>>k;
    static ll dp[200005];
    dp[k]=1;
    REP(i,k+1,2005)
    {
        ll t=0;
        REP(j,1,i+1)
        {
            if(j*j>i) break;
            else if(i%j==0)
            {
                if(j*j==i)
                {
                    if((i-1)/j>=k-1) t+=dpr[j]*(fct[(i-1)/j]*modI((fct[k-1]*fct[(i-1)/j-(k-1)])%M,M))%M;
                    t%=M;
                    if(t<0) t+=M;
                }
                else
                {
                    if((i-1)/j>=k-1) t+=dpr[j]*((fct[(i-1)/j]*modI((fct[k-1]*fct[(i-1)/j-(k-1)])%M,M))%M);
                    t%=M;
                    if(t<0) t+=M;
                    if((i-1)/(i/j)>=k-1) t+=dpr[(i/j)]*((fct[(i-1)/(i/j)]*modI((fct[k-1]*fct[(i-1)/(i/j)-(k-1)])%M,M))%M);
                    t%=M;
                    if(t<0) t+=M;
                }
            }
        }
        dp[i]=(t+dp[i-1])%M;
    }
    REP(i,0,q)
    {
        ll n;
        cin>>n;
        cout<<(dp[n]*modI((fct[n]*modI((fct[k]*fct[n-k])%M,M))%M,M))%M<<'\n';
    }
    return 0;
}
