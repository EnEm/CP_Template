#include <bits/stdc++.h>
#define lli long long int
#define pb push_back
#define mod 1000000007
#pragma GCC optimize ("-O2")
#define mod2 998244353
#define MAXN 1000000000
#define v32 vector<int>
#define v64 vector<lli>
#define v1024 vector <vector <int>>
#define v4096 vector <vector <lli>>
#define vt vector
#define f(x, y, z) for (lli x = y; x < z; x++)
#define fd(x, y, z) for (lli x = y; x > z; x--)
#define lb lower_bound
#define ld long double
#define m64 map<lli,lli>
#define m32 map<int,int>
#define m64it map<lli,lli>::iterator
#define m32it map<int,int>::iterator
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define ist insert
#define endl "\n"
#include <ext/pb_ds/assoc_container.hpp>
#define p_q priority_queue 
#define min_p_q priority_queue <int,vt <int>,greater <int>>
#include <time.h>
using namespace std;
using namespace __gnu_pbds; 

int main() 
{ 
  fastio;
  int t;cin>>t;
  while(t--){
    lli a,b,c;cin>>a>>b>>c;
    a--,c--;
    lli ans=0,total_counter=0;
        f(i,0,b){
          lli j=1;
          lli counter=0;
          while(j!=a+1){
              lli temp=min(c,((i+1)*(i+1))/j)-(i*i)/j;
              if(i*i/j+1>c){j++;continue;}
              if(temp<=0)break;
              counter=(counter+temp)%mod;
              j++;
          }
          total_counter=(total_counter+ counter)%mod;
          ans=(ans+counter*i)%mod;
          //cout<<i<<" "<<counter<<" "<<total_counter<<"\n";
        }
    if(a*c-1>=b*b)    
    ans=(ans+(b*((a*c-total_counter)%mod))%mod)%mod;
    cout<<(ans+mod)%mod<<"\n";
  }
  return 0; 	
}