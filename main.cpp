#include <iostream>
#include<windows.h>
#include<graphics.h>
#include <conio.h>
#include<ctime>
using namespace std;

//物体结构体声明
struct Node
{
	int x;
	int y;
	Node* pnext;
};


//全局变量声明

Node  *pBullet=NULL;			//子弹链表
Node  player;
Node  *pEnemy=NULL;			//敌机链表






//创建子弹链表
void CreateBulletList(int x,int y)
{
	pBullet=(Node*)malloc(sizeof(Node));
	pBullet->x=x;
	pBullet->y=y;
	pBullet->pnext=NULL;


}
//创建敌人链表
void CreateEnemyList(int x,int y)
{
	pEnemy=(Node*)malloc(sizeof(Node));
	pEnemy->x=x;
	pEnemy->y=y;
	pEnemy->pnext=NULL;
}




//初始化对象
void init()
{
	player.x=250;
	player.y=450;
	player.pnext=NULL;

	CreateBulletList(player.x,player.y);
	CreateEnemyList(300,10);
}

//增加子弹
void AddBullet(int x,int y)
{
	Node *pnew=(Node*)malloc(sizeof(Node));
	pnew->x=x;
	pnew->y=y-30;
	pnew->pnext=pBullet->pnext;
	pBullet->pnext=pnew;
}

//增加敌机
void AddEnemy(int x,int y)
{
	Node *pnew=(Node*)malloc(sizeof(Node));
	pnew->x=x;
	pnew->y=y;
	pnew->pnext=pEnemy->pnext;
	pEnemy->pnext=pnew;
}


//删除越界的子弹和敌机
void DeleteBullet()
{
	Node *pre=pBullet;
	Node *ptemp=pBullet->pnext;

	while(ptemp->pnext!=NULL)
	{
		if(ptemp->x>500||ptemp->x<0||ptemp->y<0||ptemp->y>500)
		{
			pre->pnext=ptemp->pnext;
			ptemp=pre->pnext;
		}else
		{
			pre=pre->pnext;
			ptemp=ptemp->pnext;
		}
	}


	Node *pre2=pEnemy;
	Node *ptemp2=pEnemy->pnext;
	if(ptemp2==NULL)
	{
		return;
	}
	while(ptemp2->pnext!=NULL)
	{
		if(ptemp2->x>500||ptemp2->x<0||ptemp2->y<0||ptemp2->y>500)
		{
			pre2->pnext=ptemp2->pnext;
			ptemp2=pre2->pnext;
		}else
		{
			pre2=pre2->pnext;
			ptemp2=ptemp2->pnext;
		}
	}
}

//碰撞检测
void CrashIdentify()
{
	Node* pBulletpre=pBullet;
	Node* pBulletTemp=pBullet->pnext;
	while(pBulletTemp!=NULL)
	{
		Node* pEnemypre=pEnemy;
		Node* pEnemyTemp=pEnemy->pnext;
		while(pEnemyTemp!=NULL)
		{
			if(abs(pBulletTemp->x-pEnemyTemp->x)<25&&abs(pBulletTemp->y-pEnemyTemp->y)<15)
			{
				pBulletpre->pnext=pBulletTemp->pnext;
				pBulletTemp=pBulletTemp->pnext;

				pEnemypre->pnext=pEnemyTemp->pnext;

				pEnemyTemp=pEnemyTemp->pnext;
			}
			else
			{
				pEnemypre=pEnemypre->pnext;
				pEnemyTemp=pEnemyTemp->pnext;
			}
			if(pBulletTemp==NULL)
			{
				break;
			}
		}
		if(pBulletTemp!=NULL)
		{
			pBulletpre=pBulletpre->pnext;
			pBulletTemp=pBulletTemp->pnext;
		}

	}
}


//绘图函数
void Draw()
{
	//画玩家
	setfillcolor(RGB(255,0,0));
	solidrectangle(player.x-5,player.y-25,player.x+5,player.y-10);
	setfillcolor(RGB(125,0,0));
	solidrectangle(player.x-20,player.y-10,player.x+20,player.y+10);


	//画子弹
	Node* ptemp1=pBullet->pnext;

	while(ptemp1!=NULL)
	{
		circle(ptemp1->x,ptemp1->y,5);
		ptemp1->y-=10;
		ptemp1=ptemp1->pnext;
	}

	// TODO: 画敌机
	Node* ptemp2=pEnemy->pnext;

	while(ptemp2!=NULL)
	{
		setfillcolor(RGB(0,0,255));
		solidrectangle(ptemp2->x-5,ptemp2->y-25,ptemp2->x+5,ptemp2->y-10);
		setfillcolor(RGB(0,0,125));
		solidrectangle(ptemp2->x-20,ptemp2->y-10,ptemp2->x+20,ptemp2->y+10);
		ptemp2->y+=10;
		ptemp2=ptemp2->pnext;
	}
}

void main()
{
	initgraph(500,500);
	init();
	srand((unsigned)time(NULL));
	AddEnemy(rand()%500,20);	//不断增加子弹数量
	int count=0;
	while(1)
	{
		Sleep(250);
		cleardevice();
		AddBullet(player.x,player.y);	//不断增加子弹数量
		if(count>4)
		{
			AddEnemy(rand()%500,10);	//不断增加子弹数量
			count=0;
		}
		count++;
	
		DeleteBullet();
		CrashIdentify();
		Draw();
	//	DeleteNode();
		if(_kbhit())
		{
	
			char c=(char)_getch();
			switch (c)
			{
				case 'a':
					player.x-=10;	
				break;
				case 'w':
					player.y-=10;
				break;
				case 'd':
					player.x+=10;	
				break;
				case 's':
					player.y+=10;	
				break;
				default:
					break;
			}
		}

//		system("cls");
	}

	
	

}
