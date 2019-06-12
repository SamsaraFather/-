#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct point
{
    int t;
    bool f;
};

bool cmp(point x,point y)
{
    return x.t<y.t;
}

int greedy(vector<point> x)
{
    int max=0,cur=0,n=x.size();
    sort(x.begin(),x.end(),cmp);
    for(int i=0;i<n;i++)
    {
        if(x[i].f) 
            cur++;
        else
            cur--;
        if((i==n-1 || x[i].t<x[i+1].t) && cur>max)//����x[i]==x[i+1]�����
            max=cur;                              //��cur>max��x[i]==x[i+1]ʱ��iʱ��϶��ǿ�ʼʱ�䣬i+1ʱ������ǿ�ʼʱ�䣬Ҳ�����ǽ���ʱ��
    }                                              //����ǽ���ʱ�䣬˵��ĳ���ʼʱ��ͽ���ʱ����ͬ������Ҫ�᳡���ʲ���max����;����ǿ�ʼʱ�䣬����i+1�θ���maxЧ��һ��
    return max;                                   //���i�β����и���
}

int main()
{
    vector<point> x;
    int n,i;
    point temp;
    while(cin>>n,n)
    {
        for(i=0;i<n;i++)
        {
            temp.f=true;
            cin>>temp.t;
            x.push_back(temp);
            temp.f=false;
            cin>>temp.t;
            x.push_back(temp);
        }
        cout<<greedy(x)<<endl;
        x.clear();
    }
    return 0;
}