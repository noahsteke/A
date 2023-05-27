#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*包含头文件*/
#include<stdio.h>
#include<conio.h>
#include <windows.h>
/*宏定义*/
//链表结点占用的字节数
#define NODE_SIZE sizeof(struct OutcomeNode)
/*全局变量*/
int gNodeNum;//数据结点数量
/*结构体定义*/
//链表结点结构体
struct OutcomeNode {
	int number;//学号
	char name[10];//姓名
	int amount;//消费金额
	struct OutcomeNode *pNext;
};
//链表结点结构体的别名
typedef struct OutcomeNode Outcome;
/*函数声明*/
void menu();//显示菜单
void create(Outcome *pHead);//先清空链表，再批量添加记录
void load(Outcome *pHead);//先清空链表，再从文件加载数据到链表中
void search(Outcome *pHead);//根据学号查找消费记录
void del(Outcome *pHead);//根据学号删除消费记录
void add(Outcome *pHead);//添加一个消费记录
void print(Outcome *pHead);//打印链表中的所有消费记录
void delAll(Outcome *pHead);//清空所有消费记录
void update(Outcome *pHead);//修改 
void save(Outcome *pHead);//将链表中的数据保存到文件中
void clean(Outcome *pHead);//清空链表
int exist(Outcome *pHead,int number);//根据学号判断记录是否存在，存在返回1，否则返回0
void insert(Outcome *pHead,Outcome *pData);//向链表中插入数据结点（按学号升序排列）
int confirm(char oper[]);//确认操作是否执行，执行返回1，否则返回0；
/*显示菜单*/
void menu() {
	system("cls");
	printf("\n\n\n");
	HANDLE handle =GetStdHandle(STD_OUTPUT_HANDLE);//获取控制台句柄
	SetConsoleTextAttribute(handle,0xF9);//设为白底淡蓝字
	printf("\t\t\t 学生个人消费管理系统\t\t\n\n");
	SetConsoleTextAttribute(handle,0xF0);//改回白底黑字
	printf("\t\t-------------------------------\n\n");
	printf("\t\t\t 1 创建学生消费记录           \n\n");
	printf("\t\t\t 2 读取学生消费记录           \n\n");
	printf("\t\t\t 3 查询学生消费记录           \n\n");
	printf("\t\t\t 4 删除学生消费记录           \n\n");
	printf("\t\t\t 5 增加学生消费记录           \n\n");
	printf("\t\t\t 6 修改学生消费记录           \n\n");
	printf("\t\t\t 7 显示所有记录               \n\n");
	printf("\t\t\t 8 清空所有记录               \n\n");
	printf("\t\t\t 9 保存记录到文件             \n\n");
	printf("\t\t\t 0 退出本系统                 \n\n");
	printf("\t\t-----------------------------\n");
	printf("\t\tchoose(0-9):");
}

int main(int argc,char *argv[]) {
	int num;//保存输入的选项
	/*创建头结点（带头结点的链表操作起来比较方便）*/
	Outcome *pHead = (Outcome*)malloc(NODE_SIZE);
	pHead->pNext = NULL;
	system("color F0");//设置控制台为白底黑字
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取控制台句柄
	while(1) { //循环显示菜单
		menu();
		scanf("%d",&num);
		getchar();//读掉换行，以免对后面的读取代码有影响
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
				SetConsoleTextAttribute(handle,0xFC);//设为白底淡红字
				printf("\t\t  请输入0~9之间的数字！");
				SetConsoleTextAttribute(handle,0xF0);//改回白底黑字
				getch();//停下来，输入任意字符后回车继续
				break;

		}
	}
	return 0;
}
/*
*确认操作是否执行
*oper：操作名称
*
*返回1：执行，返回0：不执行
*/
int confirm(char oper[]){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle,0xFC);//设为白底淡红字
	printf("\n\n\t  你确定要%s吗？(y/n)",oper);
	char choice = getchar();
	SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字
	if(choice !='y'&&choice !='Y')
	return 0;
	return 1; 
} 
/*
*判断学号在链表中是否已存在
*pHead：头指针
*number：学号
*
*返回1：存在，返回0：不存在
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
*按学号升序将结点插入相应的位置
*pHead:头指针
*pData：待插入结点指针
*/
void insert(Outcome *pHead, Outcome *pData) {
	Outcome *p = pHead;
	while (p->pNext) {
		if(p->pNext->number > pData->number)//找到了插入位置
			break;
		else//指针后移
			p = p->pNext;
	}
	//在链表中插入
	pData->pNext = p->pNext;
	p->pNext = pData;
	//结点数加1
	gNodeNum++;
}
/*
*清空数据结点
*实现方式：从前往后逐一释放结点
*pHead：头指针
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
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取控制台句柄
	if(!confirm("清空并创建学生消费记录"))//放弃操作
		return;
	clean(pHead);//清空链表
	SetConsoleTextAttribute(handle,0xF9);//设为白底淡蓝字
	printf("\n\n\t\t\t创建学生消费记录\n\n");
	SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字
	printf("\t 请输入学生信息(学号非正数时，结束创建)：\n\n");
	Outcome *pData;
	while(1) { //循环输入
		pData = (Outcome*)malloc(NODE_SIZE);//开辟一个新结点
		printf("\t 请输入学号：");//输入学号，学号应大于0
		scanf("%d",&pData->number);
		if(pData->number <= 0) { //学号非法，停止输入
			free(pData);//释放结点
			break;
		}
		if(exist(pHead,pData->number)) { //判断学号是否已存在
			SetConsoleTextAttribute(handle,0xFC);//设为白底淡红字
			printf("\t 学号重复，请重新输入！\n");
			SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字
			free(pData);//释放节点
			continue;//重新开始输入
		}
		printf("\t 请输入姓名：");
		scanf("%s",pData->name);//输入学生姓名
		printf("\t 请输入金额：");//输入消费金额
		scanf("%d",&pData->amount);
		printf("\t  ----------------------------------\n");
		insert(pHead,pData);//将结点插入链表
	}
	printf("\t 共输入");
	SetConsoleTextAttribute(handle,0xF5);//设为白底紫字
	printf("%d",gNodeNum);
	SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字
	printf("条学生消费记录。\n");
	getch();//停下来，随便输入字符后继续
}
/*
*打印链表中的所有记录
*pHead:头指针
*/
void print(Outcome *pHead) {
	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取控制台句柄
	SetConsoleTextAttribute(handle,0xF9);//设为白底淡蓝字
	printf("\n\n\t\t\t显示所有学生消费记录(%d)\n",gNodeNum);
	SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字
	if(gNodeNum == 0) { //无记录
		SetConsoleTextAttribute(handle,0xFC);//设为白底淡红字
		printf("\n\t\t系统中还没有记录，请创建记录!\n");
		SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字
	} else {
		printf("\t\t----------------------------------------\n");
		printf("\t\t|  number  |    name    |    amount     |\n");
		printf("\t\t----------------------------------------\n");
		Outcome *p = pHead->pNext;
		while(p) {
			printf("\t\t|%12d|%20s|%14d|\n",p->number,p->name,p->amount);
			printf("\t\t-----------------------------------------------\n");//打印行的下边框
			p=p->pNext;
		}
	}
	getch();//停下来，随便输入字符后继续
}
/**
*清空所有记录(要先确认)
*pHead:头指针
*/
void delAll(Outcome *pHead){
	system("cls");
	if(confirm("清空所有记录")){
		clean(pHead);//清空数据结点
		
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle,0xFA);//设为白底淡绿字
		printf("\n\t\t记录已清空！"); 
		SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字
		getch();//停下来，回车继续 
	}
} 
/**
*将链表中的数据保存到文件中
*pHead：头指针
*/
void save(Outcome *pHead) {
 system("cls");
 //文件路径
 char filePath[50];
 HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取控制台句柄
 SetConsoleTextAttribute(handle,0xF9);//设为白底淡蓝字
 printf("\n\n\t\t\t保存学生消费记录\n");
 SetConsoleTextAttribute(handle,0xF0);//设为白底黑字
 printf("\n\n\t\t请输入文件路径和文件名称(如f:\\mr.txt):\n\n\t\t\t   ");
 SetConsoleTextAttribute(handle,0xF5);//设为白底紫字
 scanf("%s",filePath);//输入文件路径
 SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字
 FILE *fp;
 if((fp = fopen(filePath,"w")) == NULL) { //创建“只写”的文本文件
  SetConsoleTextAttribute(handle,0xFC);//设为白底淡红字
  printf("\n\t\t创建文件失败！\n");
  SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字
 } else {
  Outcome *pData = pHead->pNext;
  while(pData) {
   //写入文件时，使用空格分隔数据
   fprintf(fp,"%d %s %d\n",pData->number,pData->name,pData->amount);
   pData = pData->pNext;
  }
  SetConsoleTextAttribute(handle,0xFA);//设为白底淡绿字
  printf("\n\t\t文件保存在");
  SetConsoleTextAttribute(handle,0xF5);//设为白底紫字
  printf("%s",filePath);
  SetConsoleTextAttribute(handle,0xF0);//设为白底黑字
  fclose(fp);
 }
 getch();//停下来，回车继续
}
/**
*从文件中加载数据到列表中
*pHead：头指针
*/
void load (Outcome *pHead){
	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取控制 台句柄
	if(!confirm("清空并加载学生消费记录") )
	return;
	clean(pHead);//清空链表
	SetConsoleTextAttribute(handle,0xF9);//设为白底淡蓝字
	printf("\n\n\t\t\t从文件读入学生消费记录\n");
	SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字
	printf("\n\n\t\t请输入文件路径和文件名称（如f:\\mr.txt):\n\n\t\t\t    ");
	SetConsoleTextAttribute(handle,0xF5);//设为白底紫字
	//文件路径
	char filePath[50];
	FILE *fp;
	scanf("%s",filePath);//输入文件路径
	SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字
	if((fp = fopen(filePath,"r"))==NULL){//以“只读”方式打开文本文件
	SetConsoleTextAttribute(handle,0xFC);//设为白底淡红字
	printf("\n\n\t\t不能打开此文件！\n");
	SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字
	getch();//停下来，回车继续
	return; 
	} else{
		Outcome *pData;
		int num;//每次读取的数据数量
		while(!feof(fp)){
			pData=(Outcome*)malloc(NODE_SIZE);//新创建一个结点
			//fscanf会以空白符为数据分隔符
			num = fscanf(fp,"%d%s%d",&pData->number,pData->name,&pData->amount);
			if(num == 3){//读取正常
			if(!exist(pHead,pData->number)){//学号不重复就插入链表
			insert(pHead,pData); 
			} 
			} else{//读取错误
			free(pData);//释放结点
			break; 
			}
		}
	
	}
    if(gNodeNum > 0){
    	SetConsoleTextAttribute(handle,0xFA);//设为白底淡绿字
		printf("\n\n\t\t共读取到");
		SetConsoleTextAttribute(handle,0xF5);//设为白底紫字
		printf("%d",gNodeNum);
		SetConsoleTextAttribute(handle,0xFA);//设为白底淡绿字
		printf("条数据\n");
		SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字 
	}else{
		SetConsoleTextAttribute(handle,0xFC);//设为白底淡红字
		printf("\n\n\t\t未读取到有效数据！\n");
		SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字 
			}
			fclose(fp);//关闭文件
			getch();//停下来，回车继续 
} 
/**
*查询学生消费记录，可以循环查询
*pHead:头指针
*/
void search(Outcome *pHead){
	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取控制台句柄
	
	if(gNodeNum == 0){
		SetConsoleTextAttribute(handle,0xFC);//设为白底淡红字
		printf("\n\t\t系统中还没有记录，请创建记录！\n");
		SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字
		getch();//停下来，回车继续
		return; 
	}
	SetConsoleTextAttribute(handle,0xF9);//设为白底淡蓝字
	printf("\n\n\t\t\t查询学生消费\n");
	SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字
	
    int number;
	Outcome *pData;
	while(1){
		printf("\n\n\t 请输入要查询的学生学号，输入非正数退出查询(number):");
		scanf("%d",&number);
		if(number <= 0)
		    return;
		printf("\t\t-----------------------------------------------\n");
		printf("\t\t|    number    |     name     |     amount    |\n");
		printf("\t\t-----------------------------------------------\n");
		pData = pHead->pNext;//每次查询要将指针指向第一个数据结点
		while(pData && pData->number != number){
			pData = pData->pNext;
		} 
		if(pData){//找到了
		printf("\t\t|%12d|%20s|%14d|\n",pData->number,pData->name,pData->amount);
		printf("\t\t----------------------------------------------\n");//打印行的下边框 
		}else{
			printf("\t\t学号为");
			SetConsoleTextAttribute(handle,0xFC);//设为白底淡红字
			printf("  %d  ",number);
			SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字
			printf("的学生不存在！\n"); 
		} 
	} 
}
/**
*删除学生消费记录 
*pHead:头结点 
*/
void del(Outcome *pHead){
	system("cls");
	int number;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);   //获取控制台句柄 
	
	if(gNodeNum == 0){
		SetConsoleTextAttribute(handle, 0xFC);   //设为白底淡红字 
		printf("\n\t\t 系统中还没有记录,请创建记录!\n");
		SetConsoleTextAttribute(handle,0xF0);   //恢复白底黑字 
		getch(); //停下来 ,回车继续
		return; 
	}
	SetConsoleTextAttribute(handle, 0xF9);   //设为白底淡蓝字 
	printf("\n\n\t\t\t删除学生消费\n");
	SetConsoleTextAttribute(handle, 0xF0);   //恢复白底黑字
	printf("\n\n\t  请输入要删除的学生学号, 输入非正数退出删除(number):");
	
	scanf("%d", &number);
	getchar(); //读掉换行,以免对后面confirm函数中的读取代码有影响
	if(number <= 0)
	return;
	
	/* 定位结点,pCurr是前一个结点,pNext是找到的结点 */
	Outcome *pCurr = pHead;
	Outcome *pNext = pHead->pNext;
	while(pNext && pNext->number !=number){
		pCurr = pNext;
		pNext = pCurr->pNext;
	} 
	if(pNext){  //找到了
	   //sprintf函数将格式化结果保存到字符串中
	   char strWarning[50];
	   sprintf(strWarning,"删除学号为 %d 的记录", number);
	   if(!confirm(strWarning))
	   return;
	   
	   pCurr->pNext = pNext->pNext; //绕过找到的结点
	   free(pNext); //释放找到的结点
	   SetConsoleTextAttribute(handle, 0xFA);   //设为白底淡绿字
	   printf("\n\t\t\t学号为 ");
	   SetConsoleTextAttribute(handle, 0xF5);   //设为白底紫字 
	   printf("%d", number);
	   SetConsoleTextAttribute(handle, 0xFA);   //设为白底淡绿字
	   printf(" 的记录已删除！\n");
	   SetConsoleTextAttribute(handle, 0xF0);   //设为白底黑字 
	   gNodeNum--;
	} else {
		SetConsoleTextAttribute(handle, 0xFC);   //设为白底淡红字
		printf("\n\t\t\t学号为 ");
		SetConsoleTextAttribute(handle, 0xF5);   //设为白底紫字
		printf("%d", number);
		SetConsoleTextAttribute(handle, 0xFC);   //设为白底淡红字
		printf("的学生不存在！\n");
		SetConsoleTextAttribute(handle, 0xF0);   //设为白底黑字
	}
	getch();  //停下来,回车继续 
}
/**
*添加一个学生消费记录
*pHead:头指针
*/
void add(Outcome *pHead){
	system("cls");
	Outcome *pData = (Outcome*)malloc(NODE_SIZE);//创建一个新结点
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取控制台句柄
	
	SetConsoleTextAttribute(handle, 0xF9);//设为白底淡蓝字
	printf("\n\n\t\t\t增加学生消费记录\n");
	SetConsoleTextAttribute(handle, 0xF0);//恢复白底黑字
	
	while(1){
		printf("\n\n\t   请输入要添加的学生学号，输入非正数退出（number）：");
		scanf("%d",&pData->number);
		if(pData->number <= 0){
			free(pData);
			return; 
		} 
		if(exist(pHead,pData->number)){
			SetConsoleTextAttribute(handle, 0xFC);//设为白底淡红字
			printf("\n\t   number重复，请重新输入！\n");
			SetConsoleTextAttribute(handle, 0xF0);//恢复白底黑字
			continue;//重新开始输入 
		}else{
			break;
		} 
	} 
	printf("\t   请输入学生的姓名：");
	scanf("%s",pData->name);
	printf("\t  请输入学生的消费金额：");
	scanf("%d",&pData->amount);
	
	insert(pHead,pData);//向链表插入结点
	
	SetConsoleTextAttribute(handle, 0xFA);//设为白底淡绿字
	printf("\t   添加成功，现在共有 ");
 
	SetConsoleTextAttribute(handle, 0xF5);//设为白底紫字
	printf("%d",gNodeNum);
	SetConsoleTextAttribute(handle, 0xFA);//设为白底淡绿字
	printf("条学生消费记录！\n");
	SetConsoleTextAttribute(handle, 0xF0);//设为白底黑字
	getch();//停下来，回车继续 
} 
/**
*修改一个学生消费记录
*pHead:头指针
*/ 
void update(Outcome *pHead){
	system("cls");
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);//获得控制台句柄 
	
	if(gNodeNum==0){
		SetConsoleTextAttribute(handle,0xFC);//设为白底淡红字 
		printf("\n\n\t\t系统中还没有记录，请创建记录！\n");
		SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字
		getch();//停下来，回车继续
		return; 
	}
	SetConsoleTextAttribute(handle,0xF9);//设为白底淡蓝字 
	printf("\n\n\t\t\t修改学生消费记录\n");
	SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字 
	
	
	int number;
	Outcome *pData;
	
	while(1){
	
	printf("\n\n\t	请输入要更新的学生学号，输入非正数退出修改(number):");
	scanf("%d",&number);
	if(number<=0)
		return;
	printf("\t\t----------------------------------------------------\n");
	printf("\t\t|    number    |        name        |    amount    |\n");
	printf("\t\t----------------------------------------------------\n");
	pData=pHead->pNext;//每次查询要将指针指向地体一个数据结点
	while(pData&&pData->number!=number){
			pData=pData->pNext;
		}
	if(pData){//如果找到了 
		printf("\t\t|%12d|%20s|%14d|\n",pData->number,pData->name,pData->amount);
		printf("\t\t------------------------------------------------\n");
		printf("\n\t	请输入要修改的金额：");
		scanf("%d",&pData->amount);//将输入的值赋值给amount 
		printf("\t\t----------------------------------------------------\n");
		printf("\t\t|    number    |        name        |    amount    |\n");
		printf("\t\t----------------------------------------------------\n");
		printf("\t\t|%12d|%20s|%14d|\n",pData->number,pData->name,pData->amount);
		printf("\t\t------------------------------------------------\n");
		printf("\n\t\t	修改成功！");
	}else{
		printf("\t\t学号为");
		SetConsoleTextAttribute(handle,0xFC);//设为白底淡红字
		printf("%d",number);			
		SetConsoleTextAttribute(handle,0xF0);//恢复白底黑字
		printf("的学生不存在！\n"); 
		}
	}
}






