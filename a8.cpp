#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define M1 1000000007
#define M2 998244353
#define ll long long
#define pll pair<long,long>
#define REP(i,a,b) for(ll i=a;i<b;i++)
#define REPI(i,a,b) for(ll i=b-1;i>=a;i--)
#define F first
#define S second
#define PB push_back
#define DB pop_back
#define MP make_pair
#define MT make_tuple
#define G(a,b) get<a>(b)
#define V(a) vector<a>

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

    ll ntc=1;
    cin>>ntc;
    REP(tc,1,ntc+1)
    {
        //cout<<"Case #"<<tc<<": ";

        ll n,k;
        cin>>n>>k;
        if(k==2)
        {
            if(n==1) cout<<5;
            else 
            {
                ll x=powM(10,n-1,M1);
                x--;
                if(x<0) x+=M1;
                x*=modI(9,M1);
                x%=M1;
                x*=20;
                x%=M1;
                x+=5;
                x%=M1;
                cout<<x;
            }
        }
        else if(k==3)
        {
            ll x=powM(10,n,M1);
            x--;
            if(x<0) x+=M1;
            x*=modI(3,M1);
            x++;
            x%=M1;
            cout<<x;
        }
        else if(k==4)
        {
            if(n==1) cout<<3;
            else if(n==2) cout<<9;
            else if(n==3) cout<<59;
            else 
            {
                ll x=powM(10,n-3,M1);
                x--;
                if(x<0) x+=M1;
                x*=modI(9,M1);
                x%=M1;
                x*=(20*25);
                x%=M1;
                x+=59;
                x%=M1;
                cout<<x;
            }
        }
        else if(k==5)
        {
            if(n==1) cout<<2;
            else 
            {
                ll x=powM(10,n-1,M1);
                x--;
                if(x<0) x+=M1;
                x*=modI(9,M1);
                x%=M1;
                x*=2;
                x%=M1;
                x+=2;
                x%=M1;
                cout<<x;
            }
        }
        else if(k==6)
        {
            if(n==1) cout<<2;
            else 
            {
                ll x=powM(10,n-1,M1);
                x--;
                if(x<0) x+=M1;
                x*=modI(9,M1);
                x%=M1;
                x-=n-1;
                if(x<0) x+=M1;
                x*=modI(3,M1);
                x%=M1;
                x*=20;
                x%=M1;
                x+=6*(n-1)+2;
                x%=M1;
                cout<<x;
            }
        }
        else if(k==7)
        {
            
        }
        else if(k==8)
        {
            if(n==1) cout<<2;
            else if(n==2) cout<<4;
            else if(n==3) cout<<17;
            else if(n==4) cout<<142;
            else if(n==5) cout<<1392;
            else 
            {
                ll x=powM(10,n-5,M1);
                x--;
                if(x<0) x+=M1;
                x*=modI(9,M1);
                x%=M1;
                x*=(100*125);
                x%=M1;
                x+=1392;
                x%=M1;
                cout<<x;
            }
        }
        else if(k==9)
        {
            ll x=powM(10,n,M1);
            x--;
            if(x<0) x+=M1;
            x*=modI(9,M1);
            x++;
            x%=M1;
            cout<<x;
        }
        else if(k==10)
        {
            cout<<1;
        }

        cout<<'\n';
    }

    return 0;
}
