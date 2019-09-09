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

    ll q=1;
    cin>>q;
    static ll dp[5005][5005];
    static ll bs[5005][5005];
    REP(i,1,5005)
    {
        dp[i][0]=0;
        bs[i][0]=0;
        REP(j,1,5005)
        {
            ll t=(i*i)/j;
            dp[i][j]=dp[i][j-1]+t;
            dp[i][j]%=M;
            bs[i][5005-j]=t;
        }
    }
    while(q--)
    {
        ll a,b,c;
        cin>>a>>b>>c;
        a--;
        c--;
        ll ans=0;
        REP(i,1,b+1)
        {
            ll t1=5005-(upper_bound(bs[i],bs[i]+5005,c)-bs[i]);
            ll t2=5005-(upper_bound(bs[i],bs[i]+5005,a)-bs[i]);
            ans+=c*(min(a,i)-max(min(t1,min(a,i)),(ll)0))-(dp[i][min(a,i)]-dp[i][max(min(t1,min(a,i)),(ll)0)]);
            ans+=a*(min(c,i)-max(min(t2,min(c,i)),(ll)0))-(dp[i][min(c,i)]-dp[i][max(min(t2,min(c,i)),(ll)0)]);
            ans%=M;
            if(ans<0) ans+=M;
            /*
            REP(j,1,min(a+1,i+1))
            {
                ll t=(i*i)/j;
                ans+=max(c-t,(ll)0);
                ans%=M;
            }
            REP(j,1,min(c+1,i+1))
            {
                ll t=(i*i)/j;
                ans+=max(a-t,(ll)0);
                ans%=M;
            }
            */
            ll t=0;
            if(a>i&&c>i)
            {
                t=(a-i)*(c-i);
            }
            t%=M;
            ans+=t;
            ans%=M;
        }
        cout<<ans<<'\n';
    }

    return 0;
}
