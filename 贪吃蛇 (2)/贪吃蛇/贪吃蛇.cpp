#include"pch.h"
#include"graphics.h"
#include<stdio.h>
#include<Windows.h>                      
#include<stdlib.h>
#include<time.h>
#include<conio.h>
/*********宏定义***********/
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4                         //蛇的方向：上下左右
/*******定义全局变量********/
typedef struct GREEDY_SNAKE             //蛇节
{
	int x;
	int y;
	struct GREEDY_SNAKE *next;
}GREEDY_SNAKE;

GREEDY_SNAKE *snake_head, *food, *p;             //head表示蛇头，food表示食物,p是个神奇的指针
int all_score = 0, highest_score = 0, every_eat = 6;      //总得分初始为0，最高分初始为0,每次吃到食物得6666分   
int direction, movetime = 200;         //蛇前进方向，运动间隔时间
int end = 0;                            //定义结束
LOGFONT f1, f2;                          //定义文字信息
/**********函数声明**********/
void game_start();                       //游戏开始！
void game_explaination();                //这游戏...还是要有说明的
void draw_map();                         //画个地图
void draw_greedy_snake();                 //画蛇
void draw_food();                        //变出食物来
void snake_move();                       //蛇动了
int  control_direction();                //上下左右控制方向
int bump_into_wall();                   //蛇撞墙了？！
void game_over();                        //游戏结束
void draw_end_window();                 //是继续不要停还是退出呢？
/********游戏开始!********/
void game_start()
{
	initgraph(600, 480);
	all_score = 0;                           //总得分清零
	IMAGE img;                               //img表示图片
	loadimage(&img, _T("D:\\timg.jpg"), 600, 480);        //加载图片
	putimage(0, 0, &img);
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	settextstyle(24, 0, _T("宋体"));        //设置字体
	gettextstyle(&f1);
	f1.lfQuality = ANTIALIASED_QUALITY;    // 设置输出字体效果为抗锯齿
	f1.lfWeight = FW_BLACK;                // 设置输出字体粗细
	settextstyle(&f1);                     // 设置字体样式
	outtextxy(120, 50, _T("欢迎来到有趣的贪吃蛇大作战!!!"));
	setcolor(RED);
	setfillcolor(RED);
	fillrectangle(200, 100, 350, 150);
	fillrectangle(200, 200, 350, 250);
	fillrectangle(200, 300, 350, 350);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(24, 0, _T("宋体"));
	gettextstyle(&f2);
	f2.lfQuality = ANTIALIASED_QUALITY;
	f2.lfWeight = FW_BLACK;
	settextstyle(&f2);
	outtextxy(220, 115, _T("游戏开始"));
	outtextxy(220, 215, _T("游戏说明"));
	outtextxy(220, 315, _T("退出游戏"));
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		//如果鼠标移动到“游戏开始”上，背景变为白色
		if (m.x >= 200 && m.x <= 350 && m.y >= 100 && m.y <= 150)
		{
			setcolor(RED);
			setfillcolor(WHITE);
			fillrectangle(200, 100, 350, 150);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(24, 0, _T("宋体"));
			gettextstyle(&f2);
			f2.lfQuality = ANTIALIASED_QUALITY;
			f2.lfWeight = FW_BLACK;
			settextstyle(&f2);
			outtextxy(220, 115, _T("游戏开始"));
		}
		else            //否则重新画出矩形
		{
			setcolor(RED);
			setfillcolor(RED);
			fillrectangle(200, 100, 350, 150);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(24, 0, _T("宋体"));
			gettextstyle(&f2);
			f2.lfQuality = ANTIALIASED_QUALITY;
			f2.lfWeight = FW_BLACK;
			settextstyle(&f2);
			outtextxy(220, 115, _T("游戏开始"));
		}
		if (m.x >= 200 && m.x <= 350 && m.y >= 200 && m.y <= 250)  //同上
		{
			setcolor(RED);
			setfillcolor(WHITE);
			fillrectangle(200, 200, 350, 250);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(24, 0, _T("宋体"));
			gettextstyle(&f2);
			f2.lfQuality = ANTIALIASED_QUALITY;
			f2.lfWeight = FW_BLACK;
			settextstyle(&f2);
			outtextxy(220, 215, _T("游戏说明"));
		}
		else
		{
			setcolor(RED);
			setfillcolor(RED);
			fillrectangle(200, 200, 350, 250);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(24, 0, _T("宋体"));
			gettextstyle(&f2);
			f2.lfQuality = ANTIALIASED_QUALITY;
			f2.lfWeight = FW_BLACK;
			settextstyle(&f2);
			outtextxy(220, 215, _T("游戏说明"));
		}
		if (m.x >= 200 && m.x <= 350 && m.y >= 300 && m.y <= 350)
		{
			setcolor(RED);
			setfillcolor(WHITE);
			fillrectangle(200, 300, 350, 350);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(24, 0, _T("宋体"));
			gettextstyle(&f2);
			f2.lfQuality = ANTIALIASED_QUALITY;
			f2.lfWeight = FW_BLACK;
			settextstyle(&f2);
			outtextxy(220, 315, _T("退出游戏"));
		}
		else
		{
			setcolor(RED);
			setfillcolor(RED);
			fillrectangle(200, 300, 350, 350);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(24, 0, _T("宋体"));
			gettextstyle(&f2);
			f2.lfQuality = ANTIALIASED_QUALITY;
			f2.lfWeight = FW_BLACK;
			settextstyle(&f2);
			outtextxy(220, 315, _T("退出游戏"));
		}
		switch (m.uMsg)
		{
			//如果鼠标左键按下
		case(WM_LBUTTONDOWN):
			if (m.x >= 200 && m.x <= 350 && m.y >= 100 && m.y <= 150)
			{
				closegraph();
				goto L2;                              //跳转到游戏地图
			}
			if (m.x >= 200 && m.x <= 350 && m.y >= 200 && m.y <= 250)
			{
				closegraph();
				goto L3;                             //跳转到游戏说明
			}
			if (m.x >= 200 && m.x <= 350 && m.y >= 300 && m.y <= 350)
			{
				closegraph();
				exit(0);                             //退出游戏
			}
		}
	}
L2:draw_map();
L3:game_explaination();
}
/******游戏说明***********/
void game_explaination()
{
	initgraph(640, 480);
	IMAGE img;
	loadimage(&img, _T("D:\\gsimg.jpg"), 640, 480);
	putimage(0, 0, &img);
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	settextstyle(16, 0, _T("宋体"));
	gettextstyle(&f1);
	f1.lfQuality = ANTIALIASED_QUALITY;
	f1.lfWeight = FW_BLACK;
	settextstyle(&f1);
	outtextxy(30, 50, _T("1.按上下左右键来控制贪吃蛇，按F1键来加速，按F2键来减速,按F3产生更多食物"));
	outtextxy(30, 150, _T("2.贪吃蛇每吃掉一个食物就增长一个蛇节,得到6个积分"));
	outtextxy(30, 250, _T("3.贪吃蛇咬到自己或是撞墙就算死亡"));
	outtextxy(30, 350, _T("4.游戏时会有得分显示，游戏结束后有历史最高分显示"));
	outtextxy(30, 450, _T("5.可以按空格进行暂停，再按一下继续游戏"));
	setcolor(RED);
	setfillcolor(RED);
	fillrectangle(500, 400, 600, 480);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, _T("宋体"));
	gettextstyle(&f2);
	f2.lfQuality = ANTIALIASED_QUALITY;
	f2.lfWeight = FW_BLACK;
	settextstyle(&f2);
	outtextxy(530, 430, _T("返回"));
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		if (m.x >= 500 && m.x <= 600 && m.y >= 400 && m.y <= 480)
		{
			setcolor(RED);
			setfillcolor(WHITE);
			fillrectangle(500, 400, 600, 480);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(20, 0, _T("宋体"));
			gettextstyle(&f2);
			f2.lfQuality = ANTIALIASED_QUALITY;
			f2.lfWeight = FW_BLACK;
			settextstyle(&f2);
			outtextxy(530, 430, _T("返回"));
		}
		else
		{
			setcolor(RED);
			setfillcolor(RED);
			fillrectangle(500, 400, 600, 480);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(20, 0, _T("宋体"));
			gettextstyle(&f2);
			f2.lfQuality = ANTIALIASED_QUALITY;
			f2.lfWeight = FW_BLACK;
			settextstyle(&f2);
			outtextxy(530, 430, _T("返回"));
		}
		switch (m.uMsg)
		{
			//如果鼠标左键按下
		case(WM_LBUTTONDOWN):
			if (m.x >= 500 && m.x <= 600 && m.y >= 400 && m.y <= 480)
			{
				closegraph();
				goto L4;
			}
		}
	}
L4:game_start();
}
/********画个地图********/
void draw_map()
{
	initgraph(480, 320);
	setbkcolor(YELLOW);
	cleardevice();
	draw_greedy_snake();
	draw_food();
	snake_move();
}
/*******画个蛇*******/
void draw_greedy_snake()
{
	GREEDY_SNAKE *snake_tail;
	int i;
	snake_tail = (GREEDY_SNAKE*)malloc(sizeof(GREEDY_SNAKE));     //先定下尾巴
	snake_tail->x = 240;
	snake_tail->y = 160;
	snake_tail->next = NULL;
	for (i = 1; i < 5; i++)
	{
		snake_head = (GREEDY_SNAKE*)malloc(sizeof(GREEDY_SNAKE));  //再定个头
		snake_head->next = snake_tail;                             //头尾相连
		snake_head->x = 240 + i * 16;
		snake_head->y = 160;
		snake_tail = snake_head;                                   //蛇头变成蛇尾，继续循环 
	}
	while (snake_tail != NULL)
	{
		setcolor(RED);
		setfillcolor(RED);
		fillcircle(snake_tail->x, snake_tail->y, 8);
		snake_tail = snake_tail->next;
	}
}
/*****变个食物出来*****/
void draw_food()
{
	int draw_food_flag;
	while (true)
	{
		draw_food_flag = TRUE;
		GREEDY_SNAKE *food_1;
		srand((unsigned)time(NULL));                                //初始化随机数
		food_1 = (GREEDY_SNAKE*)malloc(sizeof(GREEDY_SNAKE));        //初始化food_1
		do
		{
			food_1->x = rand() % 480;
		} while (food_1->x % 16 != 0 || food_1->x == 0);
		do
		{
			food_1->y = rand() % 320;
		} while (food_1->y % 16 != 0 || food_1->y == 0 || food_1->y == 1);    //设置食物出现边界
		p = snake_head;
		while (p != NULL)
		{
			if (p->x == food_1->x&&p->y == food_1->y)                 //判断蛇身是否和食物重合 
			{
				draw_food_flag = FALSE;                               //如果重合则创建失败
				break;
			}
			p = p->next;
		}
		if (FALSE == draw_food_flag)                                    //如果失败则重新创建
		{
			continue;
		}
		food = food_1;
		setcolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(food->x, food->y, 4);
		break;
	}
}
/*******蛇撞墙了？*******/
int bump_into_wall()
{
	if (snake_head->x == 0 || snake_head->x == 480 || snake_head->y == 0 || snake_head->y == 320) //如果蛇头撞墙
	{
		closegraph();
		return 1;
	}
	else
	{
		return 0;
	}
}
int control_direction()
{
	GREEDY_SNAKE * snake_next;
	char s[5];
	snake_next = (GREEDY_SNAKE*)malloc(sizeof(GREEDY_SNAKE));     //下一步
	if (direction == UP)
	{
		snake_next->x = snake_head->x;
		snake_next->y = snake_head->y - 16;                       //蛇向上时，y-16,x不动                                           
		if (snake_next->x == food->x&&snake_next->y == food->y)  //如果下一步是食物
		{
			snake_next->next = snake_head;
			snake_head = snake_next;
			p = snake_head;
			while (p != NULL)
			{
				setcolor(RED);
				setfillcolor(RED);
				fillcircle(p->x, p->y, 8);                      //将食物换成蛇头，蛇增长1
				p = p->next;
			}
			all_score += every_eat;                            //吃掉食物加分
			setcolor(YELLOW);
			setfillcolor(YELLOW);
			fillrectangle(80, 0, 120, 20);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(12, 0, _T("宋体"));
			gettextstyle(&f2);
			f2.lfQuality = ANTIALIASED_QUALITY;
			f2.lfWeight = FW_BLACK;
			settextstyle(&f2);
			outtextxy(0, 0, _T("得分为："));
			sprintf(s, "%d", all_score);                        //将数据写入字符数组中
			int n = MultiByteToWideChar(0, 0, s, -1, NULL, 0);
			wchar_t *wide = new wchar_t[n];
			MultiByteToWideChar(0, 0, s, -1, wide, n);         //将char型的s转换成LPCTSTR型wide
			outtextxy(100, 0, wide);                            //输出wide
			draw_food();                                       //再画个食物
		}
		else                                                   //如果没遇到食物
		{
			snake_next->next = snake_head;
			snake_head = snake_next;
			p = snake_head;                                    //蛇前进一格
			while (p->next->next != NULL)
			{
				if (snake_head->x == p->next->x&&snake_head->y == p->next->y)  //如果咬到自己就结束游戏
				{
					closegraph();
					return 1;
				}
				setcolor(RED);
				setfillcolor(RED);
				fillcircle(p->x, p->y, 8);                                   //蛇正常往前走
				p = p->next;
			}
			setcolor(YELLOW);
			setfillcolor(YELLOW);
			fillcircle(p->next->x, p->next->y, 8);
			setcolor(RED);
			setfillcolor(RED);
			fillcircle(p->x, p->y, 8);
			free(p->next);
			p->next = NULL;
		}
	}
	if (direction == DOWN)                                    //向下走同上，只是y+16
	{
		snake_next->x = snake_head->x;
		snake_next->y = snake_head->y + 16;
		if (snake_next->x == food->x&&snake_next->y == food->y)
		{
			snake_next->next = snake_head;
			snake_head = snake_next;
			p = snake_head;
			while (p != NULL)
			{
				setcolor(RED);
				setfillcolor(RED);
				fillcircle(p->x, p->y, 8);
				p = p->next;
			}
			all_score += every_eat;                            //吃掉食物加分
			setcolor(YELLOW);
			setfillcolor(YELLOW);
			fillrectangle(80, 0, 120, 20);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(12, 0, _T("宋体"));
			gettextstyle(&f2);
			f2.lfQuality = ANTIALIASED_QUALITY;
			f2.lfWeight = FW_BLACK;
			settextstyle(&f2);
			outtextxy(0, 0, _T("得分为："));
			sprintf(s, "%d", all_score);                        //将数据写入字符数组中
			int n = MultiByteToWideChar(0, 0, s, -1, NULL, 0);
			wchar_t *wide = new wchar_t[n];
			MultiByteToWideChar(0, 0, s, -1, wide, n);         //将char型的s转换成LPCTSTR型wide
			outtextxy(100, 0, wide);                            //输出wide
			draw_food();                                       //再画个食物
		}
		else
		{
			snake_next->next = snake_head;
			snake_head = snake_next;
			p = snake_head;
			while (p->next->next != NULL)
			{
				if (snake_head->x == p->next->x&&snake_head->y == p->next->y)
				{
					closegraph();
					return 1;
				}
				setcolor(RED);
				setfillcolor(RED);
				fillcircle(p->x, p->y, 8);
				p = p->next;
			}
			setcolor(YELLOW);
			setfillcolor(YELLOW);
			fillcircle(p->next->x, p->next->y, 8);
			setcolor(RED);
			setfillcolor(RED);
			fillcircle(p->x, p->y, 8);
			free(p->next);
			p->next = NULL;
		}
	}
	if (direction == LEFT)                                        //向左走x-16，y不变
	{
		snake_next->x = snake_head->x - 16;
		snake_next->y = snake_head->y;
		if (snake_next->x == food->x&&snake_next->y == food->y)
		{
			snake_next->next = snake_head;
			snake_head = snake_next;
			p = snake_head;
			while (p != NULL)
			{
				setcolor(RED);
				setfillcolor(RED);
				fillcircle(p->x, p->y, 8);
				p = p->next;
			}
			all_score += every_eat;                            //吃掉食物加分
			setcolor(YELLOW);
			setfillcolor(YELLOW);
			fillrectangle(80, 0, 120, 20);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(12, 0, _T("宋体"));
			gettextstyle(&f2);
			f2.lfQuality = ANTIALIASED_QUALITY;
			f2.lfWeight = FW_BLACK;
			settextstyle(&f2);
			outtextxy(0, 0, _T("得分为："));
			sprintf(s, "%d", all_score);                        //将数据写入字符数组中
			int n = MultiByteToWideChar(0, 0, s, -1, NULL, 0);
			wchar_t *wide = new wchar_t[n];
			MultiByteToWideChar(0, 0, s, -1, wide, n);         //将char型的s转换成LPCTSTR型wide
			outtextxy(100, 0, wide);                            //输出wide
			draw_food();
		}
		else
		{
			snake_next->next = snake_head;
			snake_head = snake_next;
			p = snake_head;
			while (p->next->next != NULL)
			{
				if (snake_head->x == p->next->x&&snake_head->y == p->next->y)
				{
					closegraph();
					return 1;
				}
				setcolor(RED);
				setfillcolor(RED);
				fillcircle(p->x, p->y, 8);
				p = p->next;
			}
			setcolor(YELLOW);
			setfillcolor(YELLOW);
			fillcircle(p->next->x, p->next->y, 8);
			setcolor(RED);
			setfillcolor(RED);
			fillcircle(p->x, p->y, 8);
			free(p->next);
			p->next = NULL;
		}
	}
	if (direction == RIGHT)                                     //向右走x+16,y不变
	{
		snake_next->x = snake_head->x + 16;
		snake_next->y = snake_head->y;
		if (snake_next->x == food->x&&snake_next->y == food->y)
		{
			snake_next->next = snake_head;
			snake_head = snake_next;
			p = snake_head;
			while (p != NULL)
			{
				setcolor(RED);
				setfillcolor(RED);
				fillcircle(p->x, p->y, 8);
				p = p->next;
			}
			all_score += every_eat;                            //吃掉食物加分
			setcolor(YELLOW);
			setfillcolor(YELLOW);
			fillrectangle(80, 0, 120, 20);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(12, 0, _T("宋体"));
			gettextstyle(&f2);
			f2.lfQuality = ANTIALIASED_QUALITY;
			f2.lfWeight = FW_BLACK;
			settextstyle(&f2);
			outtextxy(0, 0, _T("得分为："));
			sprintf(s, "%d", all_score);                        //将数据写入字符数组中
			int n = MultiByteToWideChar(0, 0, s, -1, NULL, 0);
			wchar_t *wide = new wchar_t[n];
			MultiByteToWideChar(0, 0, s, -1, wide, n);         //将char型的s转换成LPCTSTR型wide
			outtextxy(100, 0, wide);                            //输出wide
			draw_food();
		}
		else
		{
			snake_next->next = snake_head;
			snake_head = snake_next;
			p = snake_head;
			while (p->next->next != NULL)
			{
				if (snake_head->x == p->next->x&&snake_head->y == p->next->y)
				{
					closegraph();
					return 1;
				}
				setcolor(RED);
				setfillcolor(RED);
				fillcircle(p->x, p->y, 8);
				p = p->next;
			}
			setcolor(YELLOW);
			setfillcolor(YELLOW);
			fillcircle(p->next->x, p->next->y, 8);
			setcolor(RED);
			setfillcolor(RED);
			fillcircle(p->x, p->y, 8);
			free(p->next);
			p->next = NULL;
		}
	}
	end = bump_into_wall();
	if (end == 1) { return 1; }
	else { return 0; }
}
/*****蛇动了****/
void snake_move()
{
	direction = RIGHT;                                   //初始蛇向右动
	while (1)
	{
		//如果蛇不是向下动，按向上键，执行向上操作
		if (GetAsyncKeyState(VK_UP) && direction != DOWN)
		{
			direction = UP;
		}
		//如果蛇不是向上动，按向下键，执行向下操作
		else if (GetAsyncKeyState(VK_DOWN) && direction != UP)
		{
			direction = DOWN;
		}
		//如果蛇不是向右动，按向左键，执行向左操作
		else if (GetAsyncKeyState(VK_LEFT) && direction != RIGHT)
		{
			direction = LEFT;
		}
		//如果蛇不是向左动，按向右键，执行向右操作
		else if (GetAsyncKeyState(VK_RIGHT) && direction != LEFT)
		{
			direction = RIGHT;
		}
		if (GetAsyncKeyState(VK_SPACE))                      //按空格键，暂停函数
		{
			while (1)
			{
				Sleep(300);
				if (GetAsyncKeyState(VK_SPACE))
				{
					break;
				}
			}
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			break;
		}
		if (GetAsyncKeyState(VK_F1))
		{
			Sleep(50);
			goto L1;
		}
		else if (GetAsyncKeyState(VK_F2))
		{
			Sleep(400);
			goto L1;
		}
		Sleep(movetime);
	L1: end = control_direction();                                    //不按键时，蛇保持前进
		if (end == 1) { break; }
	}
	game_over();
}
void game_over()
{
	initgraph(600, 480);
	IMAGE img;
	loadimage(&img, _T("D:\\dimg.jpg"), 640, 480);
	putimage(0, 0, &img);
	Sleep(1000);
	closegraph();
	draw_end_window();
}
void draw_end_window()
{
	initgraph(640, 480);
	char s[5];
	IMAGE img;
	loadimage(&img, _T("D:\\gimg.jpg"), 640, 480);
	putimage(0, 0, &img);
	setcolor(RED);
	setfillcolor(WHITE);
	fillrectangle(100, 350, 250, 400);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(24, 0, _T("宋体"));
	gettextstyle(&f2);
	f2.lfQuality = ANTIALIASED_QUALITY;
	f2.lfWeight = FW_BLACK;
	settextstyle(&f2);
	outtextxy(120, 365, _T("重玩一局"));
	setcolor(RED);
	setfillcolor(WHITE);
	fillrectangle(400, 350, 550, 400);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(24, 0, _T("宋体"));
	gettextstyle(&f2);
	f2.lfQuality = ANTIALIASED_QUALITY;
	f2.lfWeight = FW_BLACK;
	settextstyle(&f2);
	outtextxy(420, 365, _T("退出游戏"));
	outtextxy(220, 50, _T("历史最高纪录是："));
	if (highest_score < all_score) { highest_score = all_score; } //取历史最高分
	sprintf(s, "%d", highest_score);                        //将数据写入字符数组中
	int n = MultiByteToWideChar(0, 0, s, -1, NULL, 0);
	wchar_t *wide = new wchar_t[n];
	MultiByteToWideChar(0, 0, s, -1, wide, n);         //将char型的s转换成LPCTSTR型wide
	outtextxy(450, 50, wide);                            //输出wide
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		//如果鼠标移动到“游戏开始”上，背景变为白色
		if (m.x >= 100 && m.x <= 250 && m.y >= 350 && m.y <= 400)
		{
			setcolor(RED);
			setfillcolor(WHITE);
			fillrectangle(100, 350, 250, 400);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(24, 0, _T("宋体"));
			gettextstyle(&f2);
			f2.lfQuality = ANTIALIASED_QUALITY;
			f2.lfWeight = FW_BLACK;
			settextstyle(&f2);
			outtextxy(120, 365, _T("重来一局"));
		}
		else            //否则重新画出矩形
		{
			setcolor(RED);
			setfillcolor(RED);
			fillrectangle(100, 350, 250, 400);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(24, 0, _T("宋体"));
			gettextstyle(&f2);
			f2.lfQuality = ANTIALIASED_QUALITY;
			f2.lfWeight = FW_BLACK;
			settextstyle(&f2);
			outtextxy(120, 365, _T("重来一局"));
		}
		if (m.x >= 400 && m.x <= 550 && m.y >= 350 && m.y <= 400)  //同上
		{
			setcolor(RED);
			setfillcolor(WHITE);
			fillrectangle(400, 350, 550, 400);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(24, 0, _T("宋体"));
			gettextstyle(&f2);
			f2.lfQuality = ANTIALIASED_QUALITY;
			f2.lfWeight = FW_BLACK;
			settextstyle(&f2);
			outtextxy(420, 365, _T("退出游戏"));
		}
		else
		{
			setcolor(RED);
			setfillcolor(RED);
			fillrectangle(400, 350, 550, 400);
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(24, 0, _T("宋体"));
			gettextstyle(&f2);
			f2.lfQuality = ANTIALIASED_QUALITY;
			f2.lfWeight = FW_BLACK;
			settextstyle(&f2);
			outtextxy(420, 365, _T("退出游戏"));
		}
		switch (m.uMsg)
		{
			//如果鼠标左键按下
		case(WM_LBUTTONDOWN):
			if (m.x >= 100 && m.x <= 250 && m.y >= 350 && m.y <= 400)
			{
				closegraph();
				goto L2;                              //重新游戏
			}
			if (m.x >= 400 && m.x <= 550 && m.y >= 350 && m.y <= 400)
			{
				closegraph();
				exit(0);
			}
		}
	}
L2:game_start();
}
int main()
{
	game_start();
	return 0;
}

