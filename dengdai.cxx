#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
 
using namespace std;
int a[1000];
int ser[100];//���񴰿ڵĹ˿͵ȴ�ʱ��
int sum[100];//���񴰿ڹ˿͵ȴ�ʱ����ܺ͡�
int main()
{
    int n,s;
    while(~scanf("%d%d",&n,&s))
    {
        for(int i=0;i<n;i++)
        {
         scanf("%d",&a[i]);
        }
        sort(a,a+n);
        memset(ser,0,sizeof(ser));
        memset(sum,0,sizeof(sum));
        int y=0;
        int j=0;
        while(y<n)
        {
            ser[j]+=a[y];
            sum[j]+=ser[j];
            y++,j++;
            if(j==s)
                j=0;
 
        }
        double t=0;
        for( i=0;i<n;i++)
        {
            t+=sum[i];
        }
        t/=n;
        printf("%0.3lf\n",t);
    }
    return 0;
}