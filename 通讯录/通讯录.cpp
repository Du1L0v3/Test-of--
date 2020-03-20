/*
 *  @author:  duidui
 *  @name:    通讯录
 *  @time:    2020 - 03 - 07
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>

struct Human
{
	char name[10];
	char sex[10];
	char phone[20];
	struct Human* next;
};

FILE* fp;  // 文件指针

void HideCursor(int i);  // 隐藏与恢复光标

void Color(const unsigned short color);  // 颜色控制

void interface_main_init();  // 初始化主界面

void interface_address_init();  // 初始化通讯录界面

void interface_address_init_show();  // 初始化通讯录界面

void interface_address_init_make();  // 初始化通讯录界面

void introduce();  // 介绍界面

void menu();  // 菜单界面

void Address_make();  // 通讯录操作

void add_human();  // 添加联系人

void delete_human();  // 删除联系人

void edit_human();  // 修改联系人

void sort();  // 排序

struct Human* sortList(struct Human* head, int t);  // 归并排序

int main(void)
{
    fp = fopen("Data_storage.txt", "a");
    fclose(fp);
    menu();
}

void HideCursor(int i)  //隐藏与恢复光标
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, i };  //i 为 0 的时候隐藏光标，i 为 1 的时候恢复
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void Color(const unsigned short color)  //颜色控制
{   /*仅限改变0-15的颜色;如果在0-15那么实现他的颜色   因为如果超过15后面的改变的是文本背景色。*/
	if (color >= 0 && color <= 15)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
/*  颜色对应值：
　　0=黑色                8=灰色　　
	1=蓝色                9=淡蓝色                　　
　　2=绿色                10=淡绿色     　　
　　3=湖蓝色              11=淡浅绿色
　　4=红色                12=淡红色 　
　　5=紫色                13=淡紫色
　　6=黄色                14=淡黄色
　　7=白色                15=亮白色
*/

/************************************* 显示模块——START *************************************/

void interface_main_init()  // 初始化主界面
{
	/* 纯粹为了显示而已 */
	HideCursor(0);
	system("cls");  // 清屏
	Color(14);
	printf("\n\n\n\n\n\n\t\t     *******_                         ");
	Color(13);
	printf("_**======**_");
	Color(14);
	printf("                         _*******");
	Color(14);
	printf("\n\t\t    *");
	Color(11);
	printf("=================================|");
	Color(12);
	printf("我的通讯录");
	Color(11);
	printf("|=================================");
	Color(14);
	printf("*");
	printf("\n\t\t    *");
	Color(11);
	printf("|                                                                            |");
	Color(14);
	printf("*");
	printf("\n\t\t    *");
	Color(11);
	printf("|                                                                            |");
	Color(14);
	printf("*");
	printf("\n\t\t    *");
	Color(11);
	printf("|                               ");
	Color(3);
	printf("1. 查看通讯录");
	Color(11);
	printf("                                |");
	Color(14);
	printf("*");
	printf("\n\t\t    *");
	Color(11);
	printf("|                                                                            |");
	Color(14);
	printf("*");
	printf("\n\t\t    |");
	Color(11);
	printf("|                                                                            |");
	Color(14);
	printf("|");
	printf("\n\t\t    *");
	Color(11);
	printf("|                               ");
	Color(3);
	printf("2. 概览  说明");
	Color(11);
	printf("                                |");
	Color(14);
	printf("*");
	printf("\n\t\t    *");
	Color(11);
	printf("|                                                                            |");
	Color(14);
	printf("*");
	Color(11);
	printf("\n\t\t     |                                                                            | ");
	Color(14);
	printf("\n\t\t    *");
	Color(11);
	printf("|                               ");
	Color(3);
	printf("3. 项目  分析");
	Color(11);
	printf("                                |");
	Color(14);
	printf("*");
	printf("\n\t\t    *");
	Color(11);
	printf("|                                                                            |");
	Color(14);
	printf("*");
	printf("\n\t\t    |");
	Color(11);
	printf("|                                                                            |");
	Color(14);
	printf("|");
	Color(14);
	printf("\n\t\t    *");
	Color(11);
	printf("================================@|>$**==**$<|@================================");
	Color(14);
	printf("*");
	printf("\n\t\t     *******~");
	Color(10);
	printf("                         ~**======**~");
	Color(14);
	printf("                         ~*******");
	Color(7);
}

void interface_address_init()  // 初始化通讯录界面
{
	interface_address_init_show();
	interface_address_init_make();
}

void interface_address_init_show()  // 初始化通讯录界面显示列表
{
	HideCursor(0);
	system("cls");  // 清屏

	/* 显示列表 */
	Color(14);
	printf("\n\n\t\t     *******_                         ");
	Color(13);
	printf("_**======**_");
	Color(14);
	printf("                         _*******");
	Color(14);
	printf("\n\t\t    *");
	Color(11);
	printf("=================================|");
	Color(12);
	printf("我的通讯录");
	Color(11);
	printf("|=================================");
	Color(14);
	printf("*");
	printf("\n\t\t     ****");
	Color(11);
	printf("                                                                      ");
	Color(14);
	printf("****");

	struct Human* q = (struct Human*)malloc(sizeof(struct Human));
	struct Human* p;
	q->next = NULL;
	if ((fp = fopen("Data_storage.txt", "r")) == NULL)
	{
		Color(4);
		printf("\n\t\t\t\t\t\t 打开文件失败！\n");
		Color(7);
		Sleep(700);
		exit(1);
	}
	Color(8);
	printf("\n");
	printf("\t\t\t\t   ID  姓名（Name）        性别（Sex）       电话（Phone）");
	fseek(fp, 0, SEEK_END);
	int len = ftell(fp);
	if (len == 0)
	{
		Color(4);
		printf("\n\n\t\t\t\t   —————————还没有联系人哟—————————");
		fclose(fp);
	}
	else
	{
		int ID = 1;
		fp = fopen("Data_storage.txt", "r");
		Color(3);
		while (!feof(fp))
		{
			p = (struct Human*)malloc(sizeof(struct Human));
			fscanf_s(fp, "姓名：%s\n", &p->name, sizeof(p->name));
			fscanf_s(fp, "性别：%s\n", &p->sex, sizeof(p->sex));
			fscanf_s(fp, "电话：%s\n\n", &p->phone, sizeof(p->phone));
			printf("\n\t\t\t\t   %-4d%-20s%-18s%-s", ID, p->name, p->sex, p->phone);
			ID++;
			p->next = NULL;
			q->next = p;
			q = p;
		}
		fclose(fp);
	}

	Color(14);
	printf("\n\t\t     ****");
	Color(11);
	printf("                                                                      ");
	Color(14);
	printf("****");
	Color(14);
	printf("\n\t\t    *");
	Color(11);
	printf("================================@|>$**==**$<|@================================");
	Color(14);
	printf("*");
	printf("\n\t\t     *******~");
	Color(10);
	printf("                         ~**======**~");
	Color(14);
	printf("                         ~*******");
	Color(7);
}

void interface_address_init_make()  // 初始化通讯录界面操作列表
{
	/* 操作列表 */
	Color(14);
	printf("\n\n\n\t\t     *******_                         ");
	Color(13);
	printf("_**======**_");
	Color(14);
	printf("                         _*******");
	Color(14);
	printf("\n\t\t    *");
	Color(11);
	printf("=================================|");
	Color(12);
	printf("选择  操作");
	Color(11);
	printf("|=================================");
	Color(14);
	printf("*");
	printf("\n\t\t     ****");
	Color(11);
	printf("                                                                      ");
	Color(14);
	printf("****");

	Color(3);
	printf("\n");
	printf("\t\t\t\t\t\t     1. 添加联系人");
	printf("\n\n");
	printf("\t\t\t\t\t\t     2. 删除联系人");
	printf("\n\n");
	printf("\t\t\t\t\t\t     3. 修改联系人");
	printf("\n\n");
	printf("\t\t\t\t\t\t     4. 选择排序法");
	printf("\n\n");
	printf("\t\t\t\t\t\t     5. 退出通讯录");

	Color(14);
	printf("\n\t\t     ****");
	Color(11);
	printf("                                                                      ");
	Color(14);
	printf("****");
	Color(14);
	printf("\n\t\t    *");
	Color(11);
	printf("================================@|>$**==**$<|@================================");
	Color(14);
	printf("*");
	printf("\n\t\t     *******~");
	Color(10);
	printf("                         ~**======**~");
	Color(14);
	printf("                         ~*******");
	Color(7);
}


void introduce()  // 介绍
{
	HideCursor(0);
	system("cls");  // 清屏
	Color(14);
	printf("\n\n\n\n\t\t     *******_                         ");
	Color(13);
	printf("_**======**_");
	Color(14);
	printf("                         _*******");
	Color(14);
	printf("\n\t\t    *");
	Color(11);
	printf("=================================|");
	Color(12);
	printf("我的通讯录");
	Color(11);
	printf("|=================================");
	Color(14);
	printf("*");
	printf("\n\t\t     ****");
	Color(11);
	printf("                                                                      ");
	Color(14);
	printf("****");
	Color(3);
	printf("\n\n\t\t\t\t               程序名称：简易通讯录");
	printf("\n\n\t\t\t\t               开发人员：陈树雄（堆堆）");
	printf("\n\n\t\t\t\t               开发日期：2020年3月19日");
	printf("\n\n\t\t\t\t                      程序用途");
	printf("\n\n\t\t\t\t               进行简单的联系人存储，以及算法实现\n\n");
	Color(14);
	printf("\t\t     **********_                    ");
	printf("                                     _*********\n");
	Color(14);
	printf("\t\t    *");
	Color(11);
	printf("=================|");
	Color(4);
	printf("Copyright 2020 duidui  All Rights Reserved");
	Color(11);
	printf("|=================");
	Color(14);
	printf("*");
	printf("\n\t\t     ***~");
	Color(11);
	printf("            ~@>$**==================================**$<@~2            ");
	Color(14);
	printf("~***");
	printf("\n\n\t\t\t\t                    ");
	Color(2);
	system("pause");
	Color(7);
	menu();
}

/************************************** 显示模块——END **************************************/

/******************************************* 显示 ********************************************/

void menu()  // 菜单界面
{
	interface_main_init();

	char hand_in = _getch();  // 用户做出选择

	if (hand_in == '1')
		Address_make();
	else if (hand_in == '2')
		introduce();
	else if (hand_in == '3')
	{
		Color(4);
		printf("\n\n\n\t\t\t\t\t\t        Welcome!\n\n");
		Color(7);
		system("start https://duitutu.cn/2020/03/19/Address-Book/");
		Sleep(700);
	}
	else
	{
		Color(4);
		printf("\n\n\n\n\t\t\t\t\t          输入错误！请重新输入\n\n");
		Color(7);
		Sleep(700);
	}
	menu();
}

void Address_make()  // 通讯录操作
{
r:
	interface_address_init();

	char hand_in = _getch();  // 用户做出选择

	if (hand_in == '1')  // 添加联系人
		add_human();
	else if (hand_in == '2')  // 删除联系人
		delete_human();
	else if (hand_in == '3')  // 修改联系人
		edit_human();
	else if (hand_in == '4')  // 排序
		sort();
	else if (hand_in == '5')
		return;
	else
	{
		Color(4);
		printf("\n\n\n\n\t\t\t\t\t          输入错误！请重新输入\n\n");
		Color(7);
		Sleep(700);
	}
	goto r;
}

void add_human()  // 添加联系人
{
	interface_address_init_show();

	printf("\n\n\n\t\t           ");
	Color(8);
	printf("---------------------------|");
	Color(15);
	printf("添加联系人");
	Color(8);
	printf("|---------------------------");

	struct Human* p = (struct Human*)malloc(sizeof(struct Human));
	if ((fp = fopen("Data_storage.txt", "a")) == NULL)
	{
		Color(4);
		printf("\n\t\t\t\t\t\t 打开文件失败！\n");
		Color(7);
		Sleep(700);
		exit(1);
	}

	HideCursor(1);
	printf("\n\n\t\t\t\t\t           姓名：");
	scanf_s("%s", &p->name, sizeof(p->name));
	printf("\n\t\t\t\t\t           性别：");
	scanf_s("%s", &p->sex, sizeof(p->sex));
	printf("\n\t\t\t\t\t           电话：");
	scanf_s("%s", &p->phone, sizeof(p->phone));
	p->next = NULL;

	fprintf(fp, "姓名：%s\n", &p->name, sizeof(p->name));
	fprintf(fp, "性别：%s\n", &p->sex, sizeof(p->sex));
	fprintf(fp, "电话：%s\n\n", &p->phone, sizeof(p->phone));
	fclose(fp);
}

void delete_human()  // 删除联系人
{
u:
	interface_address_init_show();

	printf("\n\n\n\t\t           ");
	Color(8);
	printf("---------------------------|");
	Color(15);
	printf("删除联系人");
	Color(8);
	printf("|---------------------------");

	struct Human* head = (struct Human*)malloc(sizeof(struct Human));
	struct Human* p, * q;
	q = head;
	q->next = NULL;
	int r = 0;
	if ((fp = fopen("Data_storage.txt", "r")) == NULL)
	{
		Color(4);
		printf("\n\t\t\t\t\t\t 打开文件失败！\n");
		Color(7);
		Sleep(700);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	int len = ftell(fp);
	if (len == 0)
	{
		Color(4);
		printf("\n\n\n\n\t\t\t\t   —————————还没有联系人哟—————————");
		Sleep(700);
		fclose(fp);
		return;
	}
	fclose(fp);
	fp = fopen("Data_storage.txt", "r");
	Color(3);
	while (!feof(fp))
	{
		p = (struct Human*)malloc(sizeof(struct Human));
		fscanf_s(fp, "姓名：%s\n", &p->name, sizeof(p->name));
		fscanf_s(fp, "性别：%s\n", &p->sex, sizeof(p->sex));
		fscanf_s(fp, "电话：%s\n\n", &p->phone, sizeof(p->phone));
		r++;
		p->next = NULL;
		q->next = p;
		q = p;
	}
	fclose(fp);

	int ID;
	HideCursor(1);
	printf("\n\n\t\t\t\t\t             要删除的 ID：");
	scanf_s("%d", &ID);
	if (ID > r || ID <= 0)
	{
		Color(4);
		printf("\n\n\n\n\t\t\t\t\t             不存在这个 ID！\n\n");
		Color(7);
		Sleep(700);
		goto u;
	}

	struct Human* visit = head->next;
	struct Human* P = head;
	P->next = visit;
	while (--ID)
	{
		visit = visit->next;
		P = P->next;
	}
	P->next = visit->next;
	visit->next = NULL;
	free(visit);

	q = head;
	if ((fp = fopen("Data_storage.txt", "w")) == NULL)
	{
		Color(4);
		printf("\n\t\t\t\t\t\t 打开文件失败！\n");
		Color(7);
		Sleep(700);
		exit(1);
	}
	while (q->next)
	{
		q = q->next;
		fprintf(fp, "姓名：%s\n", &q->name, sizeof(q->name));
		fprintf(fp, "性别：%s\n", &q->sex, sizeof(q->sex));
		fprintf(fp, "电话：%s\n\n", &q->phone, sizeof(q->phone));
	}
	fclose(fp);
}

void edit_human()  // 修改联系人
{
k:
	interface_address_init_show();

	printf("\n\n\n\t\t           ");
	Color(8);
	printf("---------------------------|");
	Color(15);
	printf("修改联系人");
	Color(8);
	printf("|---------------------------");

	struct Human* head = (struct Human*)malloc(sizeof(struct Human));
	struct Human* p, * q;
	q = head;
	q->next = NULL;
	int r = 0;
	if ((fp = fopen("Data_storage.txt", "r")) == NULL)
	{
		Color(4);
		printf("\n\t\t\t\t\t\t 打开文件失败！\n");
		Color(7);
		Sleep(700);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	int len = ftell(fp);
	if (len == 0)
	{
		Color(4);
		printf("\n\n\n\n\t\t\t\t   —————————还没有联系人哟—————————");
		Sleep(700);
		fclose(fp);
		return;
	}
	fclose(fp);
	fp = fopen("Data_storage.txt", "r");
	Color(3);
	while (!feof(fp))
	{
		p = (struct Human*)malloc(sizeof(struct Human));
		fscanf_s(fp, "姓名：%s\n", &p->name, sizeof(p->name));
		fscanf_s(fp, "性别：%s\n", &p->sex, sizeof(p->sex));
		fscanf_s(fp, "电话：%s\n\n", &p->phone, sizeof(p->phone));
		r++;
		p->next = NULL;
		q->next = p;
		q = p;
	}
	fclose(fp);

	int ID;
	HideCursor(1);
	printf("\n\n\t\t\t\t\t             要修改的 ID：");
	scanf_s("%d", &ID);
	if (ID > r || ID <= 0)
	{
		Color(4);
		printf("\n\n\n\n\t\t\t\t\t             不存在这个 ID！\n\n");
		Color(7);
		Sleep(700);
		goto k;
	}

	struct Human* visit = head->next;
	struct Human* P = head;
	P->next = visit;
	while (--ID)
	{
		visit = visit->next;
		P = P->next;
	}
	printf("\n\n\t\t\t\t\t             修改后的姓名：");
	scanf_s("%s", &visit->name, sizeof(visit->name));
	printf("\n\n\t\t\t\t\t             修改后的性别：");
	scanf_s("%s", &visit->sex, sizeof(visit->sex));
	printf("\n\n\t\t\t\t\t             修改后的电话：");
	scanf_s("%s", &visit->phone, sizeof(visit->phone));

	q = head;
	if ((fp = fopen("Data_storage.txt", "w")) == NULL)
	{
		Color(4);
		printf("\n\t\t\t\t\t\t 打开文件失败！\n");
		Color(7);
		Sleep(700);
		exit(1);
	}
	while (q->next)
	{
		q = q->next;
		fprintf(fp, "姓名：%s\n", &q->name, sizeof(q->name));
		fprintf(fp, "性别：%s\n", &q->sex, sizeof(q->sex));
		fprintf(fp, "电话：%s\n\n", &q->phone, sizeof(q->phone));
	}
	fclose(fp);
}

/******************************************* 显示 ********************************************/

/************************************       排序部分      ************************************/

void sort()  // 排序
{
m:
	interface_address_init_show();

	printf("\n\n\n\t\t           ");
	Color(8);
	printf("---------------------------|");
	Color(15);
	printf("选择排序法");
	Color(8);
	printf("|---------------------------\n");

	if ((fp = fopen("Data_storage.txt", "r")) == NULL)
	{
		Color(4);
		printf("\n\t\t\t\t\t\t 打开文件失败！\n");
		Color(7);
		Sleep(700);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	int len = ftell(fp);
	if (len == 0)
	{
		Color(4);
		printf("\n\n\n\n\t\t\t\t   —————————还没有联系人哟—————————");
		Sleep(700);
		fclose(fp);
		return;
	}
	fclose(fp);
	fp = fopen("Data_storage.txt", "r");

	printf("\n\t\t\t\t\t              1. 按姓名分");
	printf("\n\n\t\t\t\t\t              2. 按性别分");
	printf("\n\n\t\t\t\t\t              3. 按电话分");

	struct Human* head = (struct Human*)malloc(sizeof(struct Human));
	struct Human* p, * q;
	q = head;
	q->next = NULL;
	int r = 0;

	while (!feof(fp))
	{
		p = (struct Human*)malloc(sizeof(struct Human));
		fscanf_s(fp, "姓名：%s\n", &p->name, sizeof(p->name));
		fscanf_s(fp, "性别：%s\n", &p->sex, sizeof(p->sex));
		fscanf_s(fp, "电话：%s\n\n", &p->phone, sizeof(p->phone));
		r++;
		p->next = NULL;
		q->next = p;
		q = p;
	}
	fclose(fp);

	int t;
	HideCursor(1);
	printf("\n\n\t\t\t\t\t            要使用的排序法：");
	scanf_s("%d", &t);
	if (t > 3 || t <= 0)
	{
		Color(4);
		printf("\n\n\n\n\t\t\t\t\t            不存在这排序法！\n\n");
		Color(7);
		Sleep(700);
		goto m;
	}

	struct Human* nice = sortList(head, t);
	q = nice;
	if ((fp = fopen("Data_storage.txt", "w")) == NULL)
	{
		Color(4);
		printf("\n\t\t\t\t\t\t 打开文件失败！\n");
		Color(7);
		Sleep(700);
		exit(1);
	}
	while (q->next)
	{
		fprintf(fp, "姓名：%s\n", &q->name, sizeof(q->name));
		fprintf(fp, "性别：%s\n", &q->sex, sizeof(q->sex));
		fprintf(fp, "电话：%s\n\n", &q->phone, sizeof(q->phone));
		q = q->next;
	}
	fclose(fp);
}

struct Human* sortList(struct Human* head, int t)
{
	if (!head || !(head->next)) return head;
	struct Human* fast = head->next, * slow = head;
	//search the middle node
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;//寻找链表中点
	}
	struct Human* l = head, * r = slow->next;//递归自顶而下，将链表分为左右两个链表来进行归并排序
	slow->next = NULL;

	struct Human* l1 = sortList(l, t);//l1为左边归并排序好的头结点
	struct Human* r1 = sortList(r, t);//l2为右边归并排序好的头结点

	struct Human* L, * rear;
	if(t == 1)
		if (strcmp(l1->name, r1->name) < 0)
		{
			L = l1;
			l1 = l1->next;
		}
		else
		{
			L = r1;
			r1 = r1->next;
		}
	else if (t == 2)
		if (strcmp(l1->sex, r1->sex) < 0)
		{
			L = l1;
			l1 = l1->next;
		}
		else
		{
			L = r1;
			r1 = r1->next;
		}
	else
		if (strcmp(l1->phone, r1->phone) < 0)
		{
			L = l1;
			l1 = l1->next;
		}
		else
		{
			L = r1;
			r1 = r1->next;
		}
	rear = L;
	rear->next = NULL;
	//以上代码是向新链表L的第一个节点存入左右两个链表的头节点的较小的元素

	while (l1 || r1)//注意不是&&
	{
		if(t == 1)
			if (!l1)//当l1已经归并完时，用尾结点指向r1;
			{
				rear->next = r1;
				r1 = NULL;
			}
			else if (!r1)//同理
			{
				rear->next = l1;
				l1 = NULL;
			}
			else if (strcmp(l1->name, r1->name) < 0)//进行归并
			{
				rear->next = l1;
				l1 = l1->next;
				rear = rear->next;
				rear->next = NULL;
			}
			else
			{
				rear->next = r1;
				r1 = r1->next;
				rear = rear->next;
				rear->next = NULL;
			}
		else if (t == 2)
			if (!l1)//当l1已经归并完时，用尾结点指向r1;
			{
				rear->next = r1;
				r1 = NULL;
			}
			else if (!r1)//同理
			{
				rear->next = l1;
				l1 = NULL;
			}
			else if (strcmp(l1->sex, r1->sex) < 0)//进行归并
			{
				rear->next = l1;
				l1 = l1->next;
				rear = rear->next;
				rear->next = NULL;
			}
			else
			{
				rear->next = r1;
				r1 = r1->next;
				rear = rear->next;
				rear->next = NULL;
			}
		else
			if (!l1)//当l1已经归并完时，用尾结点指向r1;
			{
				rear->next = r1;
				r1 = NULL;
			}
			else if (!r1)//同理
			{
				rear->next = l1;
				l1 = NULL;
			}
			else if (strcmp(l1->phone, r1->phone) < 0)//进行归并
			{
				rear->next = l1;
				l1 = l1->next;
				rear = rear->next;
				rear->next = NULL;
			}
			else
			{
				rear->next = r1;
				r1 = r1->next;
				rear = rear->next;
				rear->next = NULL;
			}
	}
	return L;//返回新链表头结点
}

/*************************************       排序部分      ************************************/