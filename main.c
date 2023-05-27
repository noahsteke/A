#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*����ͷ�ļ�*/
#include<stdio.h>
#include<conio.h>
#include <windows.h>
/*�궨��*/
//������ռ�õ��ֽ���
#define NODE_SIZE sizeof(struct OutcomeNode)
/*ȫ�ֱ���*/
int gNodeNum;//���ݽ������
/*�ṹ�嶨��*/
//������ṹ��
struct OutcomeNode {
	int number;//ѧ��
	char name[10];//����
	int amount;//���ѽ��
	struct OutcomeNode *pNext;
};
//������ṹ��ı���
typedef struct OutcomeNode Outcome;
/*��������*/
void menu();//��ʾ�˵�
void create(Outcome *pHead);//�����������������Ӽ�¼
void load(Outcome *pHead);//����������ٴ��ļ��������ݵ�������
void search(Outcome *pHead);//����ѧ�Ų������Ѽ�¼
void del(Outcome *pHead);//����ѧ��ɾ�����Ѽ�¼
void add(Outcome *pHead);//���һ�����Ѽ�¼
void print(Outcome *pHead);//��ӡ�����е��������Ѽ�¼
void delAll(Outcome *pHead);//����������Ѽ�¼
void update(Outcome *pHead);//�޸� 
void save(Outcome *pHead);//�������е����ݱ��浽�ļ���
void clean(Outcome *pHead);//�������
int exist(Outcome *pHead,int number);//����ѧ���жϼ�¼�Ƿ���ڣ����ڷ���1�����򷵻�0
void insert(Outcome *pHead,Outcome *pData);//�������в������ݽ�㣨��ѧ���������У�
int confirm(char oper[]);//ȷ�ϲ����Ƿ�ִ�У�ִ�з���1�����򷵻�0��
/*��ʾ�˵�*/
void menu() {
	system("cls");
	printf("\n\n\n");
	HANDLE handle =GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ����̨���
	SetConsoleTextAttribute(handle,0xF9);//��Ϊ�׵׵�����
	printf("\t\t\t ѧ���������ѹ���ϵͳ\t\t\n\n");
	SetConsoleTextAttribute(handle,0xF0);//�Ļذ׵׺���
	printf("\t\t-------------------------------\n\n");
	printf("\t\t\t 1 ����ѧ�����Ѽ�¼           \n\n");
	printf("\t\t\t 2 ��ȡѧ�����Ѽ�¼           \n\n");
	printf("\t\t\t 3 ��ѯѧ�����Ѽ�¼           \n\n");
	printf("\t\t\t 4 ɾ��ѧ�����Ѽ�¼           \n\n");
	printf("\t\t\t 5 ����ѧ�����Ѽ�¼           \n\n");
	printf("\t\t\t 6 �޸�ѧ�����Ѽ�¼           \n\n");
	printf("\t\t\t 7 ��ʾ���м�¼               \n\n");
	printf("\t\t\t 8 ������м�¼               \n\n");
	printf("\t\t\t 9 �����¼���ļ�             \n\n");
	printf("\t\t\t 0 �˳���ϵͳ                 \n\n");
	printf("\t\t-----------------------------\n");
	printf("\t\tchoose(0-9):");
}

int main(int argc,char *argv[]) {
	int num;//���������ѡ��
	/*����ͷ��㣨��ͷ����������������ȽϷ��㣩*/
	Outcome *pHead = (Outcome*)malloc(NODE_SIZE);
	pHead->pNext = NULL;
	system("color F0");//���ÿ���̨Ϊ�׵׺���
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ����̨���
	while(1) { //ѭ����ʾ�˵�
		menu();
		scanf("%d",&num);
		getchar();//�������У�����Ժ���Ķ�ȡ������Ӱ��
		switch(num) {
			case 1:
                create(pHead);
				break;
			case 2:
                load(pHead); 
				break;
			case 3:
                search(pHead);
				break;
			case 4:
                del(pHead);
				break;
			case 5:
                add(pHead);
				break;
			case 6:
				update(pHead); 
				break;
			case 7:
                print(pHead);
				break;
			case 8:
                delAll(pHead);
				break;
			case 9:
                save(pHead);
				break;
			case 0:
				exit(0);
			default:
				SetConsoleTextAttribute(handle,0xFC);//��Ϊ�׵׵�����
				printf("\t\t  ������0~9֮������֣�");
				SetConsoleTextAttribute(handle,0xF0);//�Ļذ׵׺���
				getch();//ͣ���������������ַ���س�����
				break;

		}
	}
	return 0;
}
/*
*ȷ�ϲ����Ƿ�ִ��
*oper����������
*
*����1��ִ�У�����0����ִ��
*/
int confirm(char oper[]){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle,0xFC);//��Ϊ�׵׵�����
	printf("\n\n\t  ��ȷ��Ҫ%s��(y/n)",oper);
	char choice = getchar();
	SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺���
	if(choice !='y'&&choice !='Y')
	return 0;
	return 1; 
} 
/*
*�ж�ѧ�����������Ƿ��Ѵ���
*pHead��ͷָ��
*number��ѧ��
*
*����1�����ڣ�����0��������
*/
int exist(Outcome* pHead,int number) {
	Outcome *pData = pHead->pNext;
	while(pData) {
		if(pData->number == number)
			return 1;
		else
			pData = pData->pNext;
	}
	return 0;
}
/**
*��ѧ�����򽫽�������Ӧ��λ��
*pHead:ͷָ��
*pData����������ָ��
*/
void insert(Outcome *pHead, Outcome *pData) {
	Outcome *p = pHead;
	while (p->pNext) {
		if(p->pNext->number > pData->number)//�ҵ��˲���λ��
			break;
		else//ָ�����
			p = p->pNext;
	}
	//�������в���
	pData->pNext = p->pNext;
	p->pNext = pData;
	//�������1
	gNodeNum++;
}
/*
*������ݽ��
*ʵ�ַ�ʽ����ǰ������һ�ͷŽ��
*pHead��ͷָ��
*/
void clean(Outcome *pHead) {
	Outcome *pCurr = pHead;
	Outcome *pNext = pHead->pNext;
	while(pNext) {
		pCurr = pNext;
		pNext = pCurr->pNext;
		free(pCurr);
	}
	pHead->pNext = NULL;
	gNodeNum = 0;
}
void create(Outcome *pHead) {
	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ����̨���
	if(!confirm("��ղ�����ѧ�����Ѽ�¼"))//��������
		return;
	clean(pHead);//�������
	SetConsoleTextAttribute(handle,0xF9);//��Ϊ�׵׵�����
	printf("\n\n\t\t\t����ѧ�����Ѽ�¼\n\n");
	SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺���
	printf("\t ������ѧ����Ϣ(ѧ�ŷ�����ʱ����������)��\n\n");
	Outcome *pData;
	while(1) { //ѭ������
		pData = (Outcome*)malloc(NODE_SIZE);//����һ���½��
		printf("\t ������ѧ�ţ�");//����ѧ�ţ�ѧ��Ӧ����0
		scanf("%d",&pData->number);
		if(pData->number <= 0) { //ѧ�ŷǷ���ֹͣ����
			free(pData);//�ͷŽ��
			break;
		}
		if(exist(pHead,pData->number)) { //�ж�ѧ���Ƿ��Ѵ���
			SetConsoleTextAttribute(handle,0xFC);//��Ϊ�׵׵�����
			printf("\t ѧ���ظ������������룡\n");
			SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺���
			free(pData);//�ͷŽڵ�
			continue;//���¿�ʼ����
		}
		printf("\t ������������");
		scanf("%s",pData->name);//����ѧ������
		printf("\t �������");//�������ѽ��
		scanf("%d",&pData->amount);
		printf("\t  ----------------------------------\n");
		insert(pHead,pData);//������������
	}
	printf("\t ������");
	SetConsoleTextAttribute(handle,0xF5);//��Ϊ�׵�����
	printf("%d",gNodeNum);
	SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺���
	printf("��ѧ�����Ѽ�¼��\n");
	getch();//ͣ��������������ַ������
}
/*
*��ӡ�����е����м�¼
*pHead:ͷָ��
*/
void print(Outcome *pHead) {
	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ����̨���
	SetConsoleTextAttribute(handle,0xF9);//��Ϊ�׵׵�����
	printf("\n\n\t\t\t��ʾ����ѧ�����Ѽ�¼(%d)\n",gNodeNum);
	SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺���
	if(gNodeNum == 0) { //�޼�¼
		SetConsoleTextAttribute(handle,0xFC);//��Ϊ�׵׵�����
		printf("\n\t\tϵͳ�л�û�м�¼���봴����¼!\n");
		SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺���
	} else {
		printf("\t\t----------------------------------------\n");
		printf("\t\t|  number  |    name    |    amount     |\n");
		printf("\t\t----------------------------------------\n");
		Outcome *p = pHead->pNext;
		while(p) {
			printf("\t\t|%12d|%20s|%14d|\n",p->number,p->name,p->amount);
			printf("\t\t-----------------------------------------------\n");//��ӡ�е��±߿�
			p=p->pNext;
		}
	}
	getch();//ͣ��������������ַ������
}
/**
*������м�¼(Ҫ��ȷ��)
*pHead:ͷָ��
*/
void delAll(Outcome *pHead){
	system("cls");
	if(confirm("������м�¼")){
		clean(pHead);//������ݽ��
		
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle,0xFA);//��Ϊ�׵׵�����
		printf("\n\t\t��¼����գ�"); 
		SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺���
		getch();//ͣ�������س����� 
	}
} 
/**
*�������е����ݱ��浽�ļ���
*pHead��ͷָ��
*/
void save(Outcome *pHead) {
 system("cls");
 //�ļ�·��
 char filePath[50];
 HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ����̨���
 SetConsoleTextAttribute(handle,0xF9);//��Ϊ�׵׵�����
 printf("\n\n\t\t\t����ѧ�����Ѽ�¼\n");
 SetConsoleTextAttribute(handle,0xF0);//��Ϊ�׵׺���
 printf("\n\n\t\t�������ļ�·�����ļ�����(��f:\\mr.txt):\n\n\t\t\t   ");
 SetConsoleTextAttribute(handle,0xF5);//��Ϊ�׵�����
 scanf("%s",filePath);//�����ļ�·��
 SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺���
 FILE *fp;
 if((fp = fopen(filePath,"w")) == NULL) { //������ֻд�����ı��ļ�
  SetConsoleTextAttribute(handle,0xFC);//��Ϊ�׵׵�����
  printf("\n\t\t�����ļ�ʧ�ܣ�\n");
  SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺���
 } else {
  Outcome *pData = pHead->pNext;
  while(pData) {
   //д���ļ�ʱ��ʹ�ÿո�ָ�����
   fprintf(fp,"%d %s %d\n",pData->number,pData->name,pData->amount);
   pData = pData->pNext;
  }
  SetConsoleTextAttribute(handle,0xFA);//��Ϊ�׵׵�����
  printf("\n\t\t�ļ�������");
  SetConsoleTextAttribute(handle,0xF5);//��Ϊ�׵�����
  printf("%s",filePath);
  SetConsoleTextAttribute(handle,0xF0);//��Ϊ�׵׺���
  fclose(fp);
 }
 getch();//ͣ�������س�����
}
/**
*���ļ��м������ݵ��б���
*pHead��ͷָ��
*/
void load (Outcome *pHead){
	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ���� ̨���
	if(!confirm("��ղ�����ѧ�����Ѽ�¼") )
	return;
	clean(pHead);//�������
	SetConsoleTextAttribute(handle,0xF9);//��Ϊ�׵׵�����
	printf("\n\n\t\t\t���ļ�����ѧ�����Ѽ�¼\n");
	SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺���
	printf("\n\n\t\t�������ļ�·�����ļ����ƣ���f:\\mr.txt):\n\n\t\t\t    ");
	SetConsoleTextAttribute(handle,0xF5);//��Ϊ�׵�����
	//�ļ�·��
	char filePath[50];
	FILE *fp;
	scanf("%s",filePath);//�����ļ�·��
	SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺���
	if((fp = fopen(filePath,"r"))==NULL){//�ԡ�ֻ������ʽ���ı��ļ�
	SetConsoleTextAttribute(handle,0xFC);//��Ϊ�׵׵�����
	printf("\n\n\t\t���ܴ򿪴��ļ���\n");
	SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺���
	getch();//ͣ�������س�����
	return; 
	} else{
		Outcome *pData;
		int num;//ÿ�ζ�ȡ����������
		while(!feof(fp)){
			pData=(Outcome*)malloc(NODE_SIZE);//�´���һ�����
			//fscanf���Կհ׷�Ϊ���ݷָ���
			num = fscanf(fp,"%d%s%d",&pData->number,pData->name,&pData->amount);
			if(num == 3){//��ȡ����
			if(!exist(pHead,pData->number)){//ѧ�Ų��ظ��Ͳ�������
			insert(pHead,pData); 
			} 
			} else{//��ȡ����
			free(pData);//�ͷŽ��
			break; 
			}
		}
	
	}
    if(gNodeNum > 0){
    	SetConsoleTextAttribute(handle,0xFA);//��Ϊ�׵׵�����
		printf("\n\n\t\t����ȡ��");
		SetConsoleTextAttribute(handle,0xF5);//��Ϊ�׵�����
		printf("%d",gNodeNum);
		SetConsoleTextAttribute(handle,0xFA);//��Ϊ�׵׵�����
		printf("������\n");
		SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺��� 
	}else{
		SetConsoleTextAttribute(handle,0xFC);//��Ϊ�׵׵�����
		printf("\n\n\t\tδ��ȡ����Ч���ݣ�\n");
		SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺��� 
			}
			fclose(fp);//�ر��ļ�
			getch();//ͣ�������س����� 
} 
/**
*��ѯѧ�����Ѽ�¼������ѭ����ѯ
*pHead:ͷָ��
*/
void search(Outcome *pHead){
	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ����̨���
	
	if(gNodeNum == 0){
		SetConsoleTextAttribute(handle,0xFC);//��Ϊ�׵׵�����
		printf("\n\t\tϵͳ�л�û�м�¼���봴����¼��\n");
		SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺���
		getch();//ͣ�������س�����
		return; 
	}
	SetConsoleTextAttribute(handle,0xF9);//��Ϊ�׵׵�����
	printf("\n\n\t\t\t��ѯѧ������\n");
	SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺���
	
    int number;
	Outcome *pData;
	while(1){
		printf("\n\n\t ������Ҫ��ѯ��ѧ��ѧ�ţ�����������˳���ѯ(number):");
		scanf("%d",&number);
		if(number <= 0)
		    return;
		printf("\t\t-----------------------------------------------\n");
		printf("\t\t|    number    |     name     |     amount    |\n");
		printf("\t\t-----------------------------------------------\n");
		pData = pHead->pNext;//ÿ�β�ѯҪ��ָ��ָ���һ�����ݽ��
		while(pData && pData->number != number){
			pData = pData->pNext;
		} 
		if(pData){//�ҵ���
		printf("\t\t|%12d|%20s|%14d|\n",pData->number,pData->name,pData->amount);
		printf("\t\t----------------------------------------------\n");//��ӡ�е��±߿� 
		}else{
			printf("\t\tѧ��Ϊ");
			SetConsoleTextAttribute(handle,0xFC);//��Ϊ�׵׵�����
			printf("  %d  ",number);
			SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺���
			printf("��ѧ�������ڣ�\n"); 
		} 
	} 
}
/**
*ɾ��ѧ�����Ѽ�¼ 
*pHead:ͷ��� 
*/
void del(Outcome *pHead){
	system("cls");
	int number;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);   //��ȡ����̨��� 
	
	if(gNodeNum == 0){
		SetConsoleTextAttribute(handle, 0xFC);   //��Ϊ�׵׵����� 
		printf("\n\t\t ϵͳ�л�û�м�¼,�봴����¼!\n");
		SetConsoleTextAttribute(handle,0xF0);   //�ָ��׵׺��� 
		getch(); //ͣ���� ,�س�����
		return; 
	}
	SetConsoleTextAttribute(handle, 0xF9);   //��Ϊ�׵׵����� 
	printf("\n\n\t\t\tɾ��ѧ������\n");
	SetConsoleTextAttribute(handle, 0xF0);   //�ָ��׵׺���
	printf("\n\n\t  ������Ҫɾ����ѧ��ѧ��, ����������˳�ɾ��(number):");
	
	scanf("%d", &number);
	getchar(); //��������,����Ժ���confirm�����еĶ�ȡ������Ӱ��
	if(number <= 0)
	return;
	
	/* ��λ���,pCurr��ǰһ�����,pNext���ҵ��Ľ�� */
	Outcome *pCurr = pHead;
	Outcome *pNext = pHead->pNext;
	while(pNext && pNext->number !=number){
		pCurr = pNext;
		pNext = pCurr->pNext;
	} 
	if(pNext){  //�ҵ���
	   //sprintf��������ʽ��������浽�ַ�����
	   char strWarning[50];
	   sprintf(strWarning,"ɾ��ѧ��Ϊ %d �ļ�¼", number);
	   if(!confirm(strWarning))
	   return;
	   
	   pCurr->pNext = pNext->pNext; //�ƹ��ҵ��Ľ��
	   free(pNext); //�ͷ��ҵ��Ľ��
	   SetConsoleTextAttribute(handle, 0xFA);   //��Ϊ�׵׵�����
	   printf("\n\t\t\tѧ��Ϊ ");
	   SetConsoleTextAttribute(handle, 0xF5);   //��Ϊ�׵����� 
	   printf("%d", number);
	   SetConsoleTextAttribute(handle, 0xFA);   //��Ϊ�׵׵�����
	   printf(" �ļ�¼��ɾ����\n");
	   SetConsoleTextAttribute(handle, 0xF0);   //��Ϊ�׵׺��� 
	   gNodeNum--;
	} else {
		SetConsoleTextAttribute(handle, 0xFC);   //��Ϊ�׵׵�����
		printf("\n\t\t\tѧ��Ϊ ");
		SetConsoleTextAttribute(handle, 0xF5);   //��Ϊ�׵�����
		printf("%d", number);
		SetConsoleTextAttribute(handle, 0xFC);   //��Ϊ�׵׵�����
		printf("��ѧ�������ڣ�\n");
		SetConsoleTextAttribute(handle, 0xF0);   //��Ϊ�׵׺���
	}
	getch();  //ͣ����,�س����� 
}
/**
*���һ��ѧ�����Ѽ�¼
*pHead:ͷָ��
*/
void add(Outcome *pHead){
	system("cls");
	Outcome *pData = (Outcome*)malloc(NODE_SIZE);//����һ���½��
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ����̨���
	
	SetConsoleTextAttribute(handle, 0xF9);//��Ϊ�׵׵�����
	printf("\n\n\t\t\t����ѧ�����Ѽ�¼\n");
	SetConsoleTextAttribute(handle, 0xF0);//�ָ��׵׺���
	
	while(1){
		printf("\n\n\t   ������Ҫ��ӵ�ѧ��ѧ�ţ�����������˳���number����");
		scanf("%d",&pData->number);
		if(pData->number <= 0){
			free(pData);
			return; 
		} 
		if(exist(pHead,pData->number)){
			SetConsoleTextAttribute(handle, 0xFC);//��Ϊ�׵׵�����
			printf("\n\t   number�ظ������������룡\n");
			SetConsoleTextAttribute(handle, 0xF0);//�ָ��׵׺���
			continue;//���¿�ʼ���� 
		}else{
			break;
		} 
	} 
	printf("\t   ������ѧ����������");
	scanf("%s",pData->name);
	printf("\t  ������ѧ�������ѽ�");
	scanf("%d",&pData->amount);
	
	insert(pHead,pData);//�����������
	
	SetConsoleTextAttribute(handle, 0xFA);//��Ϊ�׵׵�����
	printf("\t   ��ӳɹ������ڹ��� ");
 
	SetConsoleTextAttribute(handle, 0xF5);//��Ϊ�׵�����
	printf("%d",gNodeNum);
	SetConsoleTextAttribute(handle, 0xFA);//��Ϊ�׵׵�����
	printf("��ѧ�����Ѽ�¼��\n");
	SetConsoleTextAttribute(handle, 0xF0);//��Ϊ�׵׺���
	getch();//ͣ�������س����� 
} 
/**
*�޸�һ��ѧ�����Ѽ�¼
*pHead:ͷָ��
*/ 
void update(Outcome *pHead){
	system("cls");
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);//��ÿ���̨��� 
	
	if(gNodeNum==0){
		SetConsoleTextAttribute(handle,0xFC);//��Ϊ�׵׵����� 
		printf("\n\n\t\tϵͳ�л�û�м�¼���봴����¼��\n");
		SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺���
		getch();//ͣ�������س�����
		return; 
	}
	SetConsoleTextAttribute(handle,0xF9);//��Ϊ�׵׵����� 
	printf("\n\n\t\t\t�޸�ѧ�����Ѽ�¼\n");
	SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺��� 
	
	
	int number;
	Outcome *pData;
	
	while(1){
	
	printf("\n\n\t	������Ҫ���µ�ѧ��ѧ�ţ�����������˳��޸�(number):");
	scanf("%d",&number);
	if(number<=0)
		return;
	printf("\t\t----------------------------------------------------\n");
	printf("\t\t|    number    |        name        |    amount    |\n");
	printf("\t\t----------------------------------------------------\n");
	pData=pHead->pNext;//ÿ�β�ѯҪ��ָ��ָ�����һ�����ݽ��
	while(pData&&pData->number!=number){
			pData=pData->pNext;
		}
	if(pData){//����ҵ��� 
		printf("\t\t|%12d|%20s|%14d|\n",pData->number,pData->name,pData->amount);
		printf("\t\t------------------------------------------------\n");
		printf("\n\t	������Ҫ�޸ĵĽ�");
		scanf("%d",&pData->amount);//�������ֵ��ֵ��amount 
		printf("\t\t----------------------------------------------------\n");
		printf("\t\t|    number    |        name        |    amount    |\n");
		printf("\t\t----------------------------------------------------\n");
		printf("\t\t|%12d|%20s|%14d|\n",pData->number,pData->name,pData->amount);
		printf("\t\t------------------------------------------------\n");
		printf("\n\t\t	�޸ĳɹ���");
	}else{
		printf("\t\tѧ��Ϊ");
		SetConsoleTextAttribute(handle,0xFC);//��Ϊ�׵׵�����
		printf("%d",number);			
		SetConsoleTextAttribute(handle,0xF0);//�ָ��׵׺���
		printf("��ѧ�������ڣ�\n"); 
		}
	}
}






