#include "iostream"
#include "cmath"
#include "fstream"
#include "algorithm"
using namespace std;

/*
t(i)��ʾ��{p1,p2...pi}�����˫��TSP��·������p1,p2..pi��x��������
t(i) = min{t(k) + D(k,i) + d(k-1,i) - d(k-1,k)}  1<k<i
t(1) = 0   t(1) = 2d(1,2)
d(i,j)Ϊpi,pj֮��ľ���
D(i,j)Ϊpi,pi+1,pi+1...pj֮���ۼӾ���

��s(i)=d(1,2) + d(2,3) +...+ d(i-1,i)
��D(k, i) = s(k) - s(i); d(k-1, k) = s(k) - s(k-1)
����t(i) = min{t(k) + s(i) + s(k-1) - 2s(k) + d(k-1, i)}  1<k<i
 */

const int MAX = 100;
double s[MAX];
double t[MAX];
int N;  //�������

struct Point
{
    int x;  //x����
    int y;  //y����

    bool operator < (const Point &p) const
    {
        return x < p.x;
    }
};

Point point[MAX];

double dist(Point p1, Point p2) //����֮��ľ���
{
    return sqrt( pow((p1.x-p2.x),2) + pow((p1.y-p2.y),2) );
}

//t(i) = min{t(k) + s(i) + s(k-1) - 2s(k) + d(k-1, i)}  1<k<i
double dyna()
{
    sort(point, point+N);  //��x��������
    int i, k;
    s[1] = 0;
    for(i=2; i<=N; i++)
        s[i] = s[i-1] + dist(point[i-1], point[i]);

    t[1] = 0;
    t[2] = 2 * dist(point[1], point[2]);
    double temp;
    for(i=3; i<=N; i++)
    {
        t[i] = t[2] + s[i] + s[1] - 2*s[2] + dist(point[1], point[i]);
        for(k=3; k<i; k++)  
        {
            temp = t[k] + s[i] + s[k-1] - 2*s[k] + dist(point[k-1], point[i]);
            if(temp < t[i])
                t[i] = temp;
        }
    }
    return t[N];
}

int main()
{
    ifstream fin("����.txt");
    cout << "������������";
    fin >> N; cout << N;
    cout << "\n�����������꣺\n";
    int i;
    for(i=1; i<=N; i++)
    {
        fin >> point[i].x >> point[i].y;
        cout << point[i].x << " " << point[i].y << endl;
    }
    cout << "���˫��TSP��·����Ϊ��" << dyna() << endl;
	ofstream fout("���.txt");
    fin.close();
    return 0;
} 