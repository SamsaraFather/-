#include <stdio.h>
#include <stdlib.h>
#include<string>


typedef struct JDian
{
	double hypothesisZuiYou; //�����洢���ѡ��һ����Ʒ����ô��ֵ�Ƕ���
	double realityJiaZhi; 	//�����洢��ǰ��ֵ��
	int *backRongLiang;		//������ʾ�����Ѿ�װ�˶��ٶ���

	int XuanShei; //������¼ѡ���ĸ���Ʒ

	struct JDian* XYiChu;
} heapJDian;	

heapJDian *head,*tail;//root


 

//����������ͳ�ʼ��
double *realityJiaZhi;
int **attribute;
int nUM;
int nUM_attr;
double check;
int *limitation; 

double bestv; 
int *DangQianRongliang;// ��ǰ��������
double c_realityJiaZhi;//��ǰ������ֵ
//��̬��ά����Ĵ洢
void dongTaiFenPei ();
double shiXianGuCe(int t);
double fenZhiXianJieShiXian();
heapJDian* chuDui();
int shiXianBiJiao(int opr, int *l, int *target);
int stact_empty();
void ruDui(double upe, double crealityJiaZhi, int* cons, int XuanShei);
int compare(int* target, int index);
void minus(int* target, int index);

int main(void){
	FILE *f = fopen("����.txt","r");//���ļ���ȡ����
	fscanf(f,"%d %d %lf",&nUM,&nUM_attr,&check);
	dongTaiFenPei();
	int i,j;
	
	//��ֵ¼��
	for(i = 0; i < nUM; i++){
		fscanf(f,"%lf",&realityJiaZhi[i]);
	}

	//����¼��
	for(i = 0 ; i < nUM_attr;i++)
		for(j = 0; j < nUM; j++)
			fscanf(f,"%d", &attribute[i][j]);

	//��������¼��
	for(i = 0 ; i < nUM_attr;i++)
		fscanf(f,"%d", &limitation[i]);

	double result = fenZhiXianJieShiXian();
	printf("my result is %lf\ntarget is %lf", result,check);

}
//��̬�����ά����ռ�
void dongTaiFenPei(){
	realityJiaZhi = (double*)malloc(sizeof(double) * nUM);
	attribute = (int**)malloc(sizeof(int*) * nUM_attr);
	int i;
	for(i = 0 ; i < nUM_attr;i++)
		*(attribute + i) = (int*)malloc(sizeof(int) * nUM);

	limitation = (int*)malloc(sizeof(int) * nUM_attr);
	DangQianRongliang = (int*)malloc(sizeof(int) * nUM_attr);
	memset(DangQianRongliang,0,sizeof(int)*nUM_attr);
	head = NULL;
	tail = NULL;
}

//ʵ�����ֵ�Ĺ�������������ֵ�ıȽϣ�����������Ʒ�ɷָ�
double shiXianGuCe(int t){
	double bound = c_realityJiaZhi;//ѡ�Ͳ�ѡ����Ʒ��˼�룬���ѡ����ô�����I+1����Ʒ�ļ�ֵ�Ƿ���ڵ�ǰ������ֵ�����������ļ�ֵ��������û�е�ǰ�ļ�ֵ����ô����Ͳ��ü����ˡ�
	int *left = (int*)malloc(sizeof(int) * nUM_attr);
	int i,j;
	for(i = 0; i<nUM_attr; i++)
		*(left + i) = *(limitation + i) - *(DangQianRongliang + i);
	while(t < nUM && compare(left, t)){
		minus(left, t);
		bound += realityJiaZhi[t];
		t++;
	}

	if(t < nUM){
		bound += (realityJiaZhi[t]/attribute[0][t]) * left[0];
	}
	return bound;

}

//ʵ������Ԫ�صıȽϣ��磺A��ÿ��Ԫ���Ƿ񶼱�B��
int shiXianBiJiao (int opr, int *l, int *target){
	int i;
	if(opr == 0){
		for(i = 0;i<nUM_attr;i++){
			 if(l[i] < target[i])
			 	return 0;
		}
	}

	else if(opr == 1){
		for(i = 0;i<nUM_attr;i++){
			*(l+i) -=*(target+i);
		}

	}

	else if(opr == 2){
		for(i = 0;i<nUM_attr;i++){
			l[i]+= target[i];
		}
	
	}
	return 1;

}

//��֧�޽編��ѡ��
double fenZhiXianJieShiXian(){
	int i = 0,j;
	double hypothesisZuiYou = shiXianGuCe(i);
	
	while(1){

		int *c_weight = (int*)malloc(sizeof(int)*nUM_attr);
		memset(c_weight,0,sizeof(int)*nUM_attr);

		for(j = 0;j<nUM_attr;j++){
			c_weight[j] = attribute[j][i] + DangQianRongliang[j];
		}
		
		if(shiXianBiJiao(0, limitation,c_weight)){
			if(c_realityJiaZhi + realityJiaZhi[i] > bestv)
				bestv = c_realityJiaZhi + realityJiaZhi[i];
			ruDui(hypothesisZuiYou,c_realityJiaZhi + realityJiaZhi[i], c_weight, i + 1); //���ֵ��Ԥ���Ǽ�������Ʒ���Էֽ�ģ����豳��ȫ�����������Լ۱�����ȷš�
		}
		hypothesisZuiYou = shiXianGuCe(i + 1);
		if(hypothesisZuiYou >= bestv)
			ruDui(hypothesisZuiYou, c_realityJiaZhi, DangQianRongliang, i + 1);
		if(stact_empty()) 
			return bestv;
		heapJDian *JDian = chuDui(); 
		DangQianRongliang = JDian->backRongLiang;
		c_realityJiaZhi = JDian->realityJiaZhi;
		hypothesisZuiYou = JDian->hypothesisZuiYou;
		i = JDian->XuanShei;
		free(JDian);
		JDian = NULL;
	}
}

//ʵ�ֶ���Ԫ�صĳ���
heapJDian* chuDui(){
	if(head == tail)
		tail == NULL;
	heapJDian* item = head;
	head = item->XYiChu;
	return item;	
}

//ʵ��Ԫ�ص����
void ruDui(double upe, double crealityJiaZhi, int* cons, int XuanShei){
	heapJDian *temp = (heapJDian*)malloc(sizeof(heapJDian));
	temp->hypothesisZuiYou = upe;
	temp->realityJiaZhi = crealityJiaZhi;
	temp->backRongLiang = cons;
	temp->XuanShei = XuanShei;
	temp->XYiChu = NULL;
	if(XuanShei <= nUM){
		if(stact_empty()){
			head = temp;
			tail = temp;
		}
		else{
			tail->XYiChu = temp;
			tail= temp;	
		}
		
	}
}

//�жϵ�ǰ�����Ƿ�Ϊ��
int stact_empty(){
	return (head == NULL);
}
//ʵ�ֶ�ά�����λ�ñ仯
int compare(int* target, int index){
	int i;
	for(i = 0; i < nUM_attr; i++){
		if(target[i] < attribute[i][index])
			return 0;

	}
	return 1;		//ʵ�ֵ��Ƕ�ά�����λ�ñ任����Ϊ����ֻ�ܺ������������Ҫ��������������ÿ�����Ժ���
}

void minus(int* target, int index){
	int i;
	for(i = 0; i < nUM_attr; i++){
		target[i] -= attribute[i][index];
	}

}
