#include <stdio.h>
#include<string.h>
int main(void)
{
    int n;
    scanf ("%d", &n);
    for (int i=0; i<n; i++)
    {
        int t;
        scanf ("%d", &t);
        char a[1001];
        fflush(stdin);
        scanf ("%s", a);
        int p=0;
        int f=1;
        for (int j=2; j<=t-2; i++)
        {
            if ((a[i-2]=='P' || a[i-1]=='P') && a[i]=='A' && (a[i+1]=='P' || a[i+2]=='P'))
            {
                a[i]='P';
            }
            int k=0;
            int c=0;
            while (a[k]!='\0')
            {
                if (a[k]=='P')
                {
                    c++;
                }
                k++;
            }
            if ((float)c/t >= 0.75)
            {
                f=0;
                break;
            }
            else
            p++;
        }
        if (f==0)
        {
            printf ("%d\n", p);
        }
        else
            printf ("-1");

    }
	return 0;

}
