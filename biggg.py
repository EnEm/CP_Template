q=int(input())

while q>0:
    q-=1
    a,b,n=map(int,input().split())
    at=[]
    an=0
    bt=[]
    bn=0
    while a>0:
        at+=[a%10]
        a//=10
        an+=1
    while b>0:
        bt+=[b%10]
        b//=10
        bn+=1
    fn=[an,bn]
    fnn=2
    if n<=an:
        print(at[an-n])
    elif n<=bn:
        print(bt[bn-n])
    else:
        while 1>0:
            t=fn[fnn-2]+fn[fnn-1]
            fn+=[t]
            fnn+=1
            if(n>=t):
                i=fnn-1
                while i>=2:
                    print(i)
                    if n>fn[i-2]:
                        n-=fn[i-2]
                        i-=1
                    else:
                        i-=2
                if i==1:
                    print(at[an-n])
                else:
                    print(bt[bn-n])
                break

