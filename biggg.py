ntc=1
#ntc=(int)(input())
for tc in range(1,ntc+1):
    n=(int)(input())

    res=input().split()
    a=[]
    for i in res:
        a+=[int(i)]

    print(tc,end=' ')
    print(a,end=' ')
    print(n)