#include <stdio.h>
#include<math.h>
int main ()
{
    long long n;
    scanf ("%lld", &n);
    long long m= pow(10,9) +7;
    for (long long i=0; i<n; n++)
    {
        long long k;
        scanf ("%lld", &k);
        long long p=10;
        for (long long j=0; j<k-1; j++)
        {
            p=(p*2)%m;
        }
        printf ("%lld\n", p);
    }
    return (0);
}
