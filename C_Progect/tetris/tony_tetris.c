////////***程序内容：俄罗斯方块********/////////////
/*
   程序共有三个文件main.c tony_tetris.c tony_tetris.h 
   一个编译文件Makefile
*/
///////////////////////////////

#include <termios.h>
#include<signal.h>
#include<unistd.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include"tony_tetris.h"

#define LINE 20 
#define ROW 24
#define VAR_LINE 8 
#define VAR_ROW 8
#define LEVEL 50  //   while score % LEVEL ==0;    level++;

static char username[32]="Tony";


//标志位声明
int up_flag=0;//var_box update;
int over_flag=0;
int change_flag=0;//看是否去改变图
int start_flag=0;//游戏启动标志位
int pause_flag=0;//游戏暂停标志位
//函数声明
static int one(void);
static int var_box(void);
static int gameover(void);//游戏结束函数
static void clear_box(void);
static int score=0,level=0;

typedef struct box{	int sbox[LINE][ROW];	int x;	int y;}BOX;

BOX tmp_box;//变形时的图

typedef struct ter {	struct  termios new,old;	}TER;//终端环境记录
static TER m_ter;

typedef struct x_y {	int x,y;	}X_Y;

typedef struct xy{	struct x_y arr_xy[64];	int count;	}XY;
XY ARR_xy;//坐标记录

typedef struct var{	int var[8][8];	int x;	int y;int typenum; int n;int color;	}VAR;
VAR *p_var;//随机图形

VAR m_old_var;//在变形时要知道老图形是什么样子
VAR *old_var;//图形
int save_old_color;


static VAR m_one={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,3,4,3,4,0,0},     ////
		{0,0,3,4,3,4,0,0},     ////
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW,
	10

};
static VAR m_two_1={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,3,4,0,0,0,0},	//
		{0,0,3,4,0,0,0,0},	//
		{0,0,3,4,0,0,0,0},	//
		{0,0,3,4,0,0,0,0},	//
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW,
	20,
	1	
};
static VAR m_two_2={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{3,4,3,4,3,4,3,4},	////////
		{0,0,0,0,0,0,0,0},	
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW,
	20,
	2	
};
static VAR m_two_two_1={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,3,4,0,0,0,0},	//
		{0,0,3,4,0,0,0,0},	//
		{0,0,0,0,0,0,0,0},	//
		{0,0,0,0,0,0,0,0},	//
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW,
	22,
	1	
};
static VAR m_two_two_2={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,3,4,3,4,0,0},	////////
		{0,0,0,0,0,0,0,0},	
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW,
	22,
	2	
};
static VAR m_three_1={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,3,4,0,0,0,0},	  //
		{3,4,3,4,3,4,0,0},	//////
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW,
	30,
	1
};
static VAR m_three_2={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,3,4,0,0,0,0},	  //
		{0,0,3,4,3,4,0,0},	  ////
		{0,0,3,4,0,0,0,0},	  //
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW,
	30,
	2
};
static VAR m_three_3={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},	  
		{3,4,3,4,3,4,0,0},	//////
		{0,0,3,4,0,0,0,0},	  //
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW,
	30,
	3
};
static VAR m_three_4={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,3,4,0,0,0,0},	  //
		{3,4,3,4,0,0,0,0},	////
		{0,0,3,4,0,0,0,0},	  //
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW,
	30,
	4
};
static VAR m_four_1={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},	//
		{3,4,0,0,0,0,0,0},	//////
		{3,4,3,4,3,4,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW	,
	40,
	1
};
static VAR m_four_2={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},	////
		{0,0,3,4,3,4,0,0},	//
		{0,0,3,4,0,0,0,0},	//
		{0,0,3,4,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},	
	},
	VAR_LINE,
	VAR_ROW	,
	40,
	2
};
static VAR m_four_3={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},	
		{0,0,0,0,0,0,0,0},	//////
		{3,4,3,4,3,4,0,0},	    //
		{0,0,0,0,3,4,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW	,
	40,
	3
};
static VAR m_four_4={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,3,4,0,0},	    //
		{0,0,0,0,3,4,0,0},	    //
		{0,0,3,4,3,4,0,0},	  ////
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW	,
	40,
	4
};
static VAR m_five_1={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,3,4,0,0},	    //
		{3,4,3,4,3,4,0,0},	//////
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW	,
	50,
	1
};
static VAR m_five_2={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,3,4,0,0,0,0},	//
		{0,0,3,4,0,0,0,0},	//
		{0,0,3,4,3,4,0,0},	////
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW	,
	50,
	2
};
static VAR m_five_3={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},	    
		{3,4,3,4,3,4,0,0},	//////
		{3,4,0,0,0,0,0,0},	//
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW	,
	50,
	3
};
static VAR m_five_4={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,3,4,3,4,0,0},	 ////
		{0,0,0,0,3,4,0,0},	   //
		{0,0,0,0,3,4,0,0},	   //
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW	,
	50,
	4
};
static VAR m_six_1={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,3,4,3,4,0,0},	////
		{0,0,0,0,3,4,3,4},	  ////
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW	,
	60,
	1
};
static VAR m_six_2={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,3,4,0,0},	   //
		{0,0,3,4,3,4,0,0},	////
		{0,0,3,4,0,0,0,0},     //
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW	,
	60,
	2
};
static VAR m_seven_1={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,3,4,3,4,0,0},	   ////
		{3,4,3,4,0,0,0,0},	////
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW	,
	70,
	1
};
static VAR m_seven_2={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,3,4,0,0,0,0},	   //
		{0,0,3,4,3,4,0,0},	   ////
		{0,0,0,0,3,4,0,0},	    //
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW	,
	70,
	2
};
static VAR m_eight_1={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{3,4,0,0,0,0,0,0},	   //
		{3,4,3,4,3,4,0,0},	   ////
		{0,0,0,0,3,4,0,0},	    //
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW	,
	80,
	1	
};
static VAR m_eight_2={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,3,4,3,4},	   //
		{0,0,0,0,3,4,0,0},	   ////
		{0,0,3,4,3,4,0,0},	    //
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW	,
	80,
	2
};
static VAR m_nine_1={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},	   
		{3,4,0,0,3,4,0,0},	    // //
		{3,4,3,4,3,4,0,0},	   //////
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW	,
	90,
	1	
};
static VAR m_nine_2={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,3,4,3,4,0,0},	   ////
		{0,0,3,4,0,0,0,0},	   //
		{0,0,3,4,3,4,0,0},	   ////
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW	,
	90,
	2
};
static VAR m_nine_3={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,3,4,3,4,3,4},	   //////
		{0,0,3,4,0,0,3,4},	   //  //
		{0,0,0,0,0,0,0,0},	   
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW	,
	90,
	3
};
static VAR m_nine_4={
	{
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,3,4,3,4,0,0},	   ////
		{0,0,0,0,3,4,0,0},	   //
		{0,0,3,4,3,4,0,0},	   ////
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
	},
	VAR_LINE,
	VAR_ROW	,
	90,
	4
};


static BOX box={
	{
		/*v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23*/
		{ 2,  2, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1,  1,  1,  1 , 1,  1,  1,  1 , 1 , 2, 2},
		{ 1,  1, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 1},
		{ 1,  1, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 1},
		{ 1,  1, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  4,  1, 1},
		{ 1,  1, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  4,  1, 1},
		{ 1,  1, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  4,  1, 1},
		{ 1,  1, 0, 3, 4, 3, 4, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  4,  1, 1},
		{ 1,  1, 0, 3, 4, 3, 4, 0, 0, 0, 0,  0,  0,  0,  0,  0,  3,  4,  0,  0,  0,  0,  1, 1},
		{ 1,  1, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  3,  4,  3,  4,  3,  4,  0,  0,  1, 1},
		{ 1,  1, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 1},
		{ 1,  1, 0, 3, 4, 3, 4, 0, 0, 0, 0,  0,  0,  0,  0,  0,  3,  4,  3,  4,  0,  0,  1, 1},
		{ 1,  1, 0, 3, 4, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  3,  4,  3,  4,  1, 1},
		{ 1,  1, 0, 3, 4, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 1},
		{ 1,  1, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  3,  4,  3,  4,  0,  0,  0,  1, 1},
		{ 1,  1, 0, 3, 4, 0, 0, 0, 0, 0, 0,  0,  0,  3,  4,  3,  4,  0,  0,  0,  0,  0,  1, 1},
		{ 1,  1, 0, 3, 4, 3, 4, 3, 4, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 1},
		{ 1,  1, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 1},
		{ 1,  1, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 1},
		{ 1,  1, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 1},
		{ 2 , 2, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1,  1,  1,  1 , 1,  1,  1,  1 , 1 , 2, 2},
	},
	LINE,
	ROW
};
static void drow_color3(int a)
{
	switch(a)
	{
		case 40:	printf("\33[32;40m{\33[0m");break;//黑
		case 41:	printf("\33[41m{\33[0m");break;//红
		case 42:	printf("\33[42m{\33[0m");break;//绿
		case 43:	printf("\33[43m{\33[0m");break;//黄
		case 44:	printf("\33[33;44m{\33[0m");break;//蓝
		case 45:	printf("\33[45m{\33[0m");break;//紫红色
		case 46:	printf("\33[31;46m{\33[0m");break;//青蓝色
		case 47:	printf("\33[47m{\33[0m");break;//白色
	}
}
static void drow_color4(int a)
{
	switch(a)
	{
		case 40:	printf("\33[32;40m}\33[0m");break;
		case 41:	printf("\33[41m}\33[0m");break;
		case 42:	printf("\33[42m}\33[0m");break;
		case 43:	printf("\33[43m}\33[0m");break;
		case 44:	printf("\33[33;44m}\33[0m");break;
		case 45:	printf("\33[45m}\33[0m");break;
		case 46:	printf("\33[31;46m}\33[0m");break;
		case 47:	printf("\33[47m}\33[0m");break;
	}
}
static void drow_typenum3(int a)
{
	int tmp;
	tmp=a/100;
	switch(tmp)
	{
		case 10:a=a-tmp*100;drow_color3(a);break;
		case 20:a=a-tmp*100;drow_color3(a);break;
		case 22:a=a-tmp*100;drow_color3(a);break;
		case 30:a=a-tmp*100;drow_color3(a);break;
		case 40:a=a-tmp*100;drow_color3(a);break;
		case 50:a=a-tmp*100;drow_color3(a);break;
		case 60:a=a-tmp*100;drow_color3(a);break;
		case 70:a=a-tmp*100;drow_color3(a);break;
		case 80:a=a-tmp*100;drow_color3(a);break;
		case 90:a=a-tmp*100;drow_color3(a);break;
	}
}
static void drow_typenum4(int a)
{
	int tmp;
	tmp=a/100;
	switch(tmp)
	{
		case 10:a=a-tmp*100;drow_color4(a);break;
		case 20:a=a-tmp*100;drow_color4(a);break;
		case 22:a=a-tmp*100;drow_color4(a);break;
		case 30:a=a-tmp*100;drow_color4(a);break;
		case 40:a=a-tmp*100;drow_color4(a);break;
		case 50:a=a-tmp*100;drow_color4(a);break;
		case 60:a=a-tmp*100;drow_color4(a);break;
		case 70:a=a-tmp*100;drow_color4(a);break;
		case 80:a=a-tmp*100;drow_color4(a);break;
		case 90:a=a-tmp*100;drow_color4(a);break;
	}
}
static void drow_byte(int a)
{
	int tmp=0;
	if(a>30000 && a <50000)
	{
		tmp=a/10000;
		//printf("tmp=%d,a=%d  ",tmp,a);
		//fflush(NULL);
		//sleep(1);
		if(tmp==3)
		{
			a=(a-tmp*10000);
			drow_typenum3(a);
		}
		if(tmp==4)
		{
			a=(a-tmp*10000);
			drow_typenum4(a);
		}
	}

	if((  a>='A' && a <= 'Z')||(a >= 'a' && a <= 'z'))
		printf("\33[31m%c\33[0m",a);
	
	switch (a)
	{
		case  0:	printf(" ");break;
		case  1:	printf("\33[30;45m|\33[0m");break;
		case  2:	printf("\33[30;46m*\33[0m");break;
		case  3:	printf("\33[42m[\33[0m");break;
		case  4:	printf("\33[42m]\33[0m");break;
		
		case  '@':	case  '!':	case  '&':	case  '^':	case  '~':
			printf("\33[32m%c\33[0m",a);break;
		
		case  '-':	case  '|':
			printf("\33[30;41m%c\33[0m",a);break;
	}
}
static void drow(void)
{
	int i,j,var_x=0,var_y=0;
	BOX * p_box=&box;
	if(change_flag==1)
	{
	//	clear_box();
		box=tmp_box;
	}
	//printf("\33[u");//取出保存的光标位置
	//printf("\33[2J\33[2;10H\n");//清一下屏
	printf("\33[u\33[2;10H\n");//清一下屏
	for (i=0;i< p_box->x; i++)
	{
		printf("\33[0m               ");//15个空格
		for(j=0;j< p_box->y;j++)
		{
			drow_byte(p_box->sbox[i][j]);
		}
#if 1 
		printf("   ");
		if( i< p_var->x)
		{	if(var_x < 8)
			{
				for(var_y=0;var_y < p_var->y;var_y++)
				{	drow_byte(p_var->var[var_x][var_y]);
				//	printf("%d ",p_var->var[var_x][var_y]);
				//	fflush(NULL);
				//	sleep(1);
				}
			var_x++;
			}
		}
		if(i==8)	printf("USER NAME");
		if(i==9)	printf("\33[35m  %s\33[0m",username);
		if(i==11)	printf("SCORE");
		if(i==12)	printf("\33[35m  %d\33[0m",score);
		if(i==14)	printf("LEVEL");
		if(i==15)	printf("\33[35m  %d\33[0m",level);
#endif
		printf("\33[?25l");//隐藏光标
		printf("\n");
	}
		change_flag=0;

}
static void line_move(int line)
{
	BOX *p_box=&box;
	int i,j;
	for(i=line; i>1; i--)
	{
		for(j=2;j < p_box->y-2 ; j++)
		{
			p_box->sbox[i][j]=p_box->sbox[i-1][j];
		}
	}
}
static int clear_line(void)
{
	BOX *p_box=&box;
	int i,j,count=2,tmp=0;
	i = p_box->x-2;
	while(i>1)
	{
		for(j=2;j < p_box->y-2 ; j++ )
		{
			if( p_box->sbox[i][j] == 0)
			{
				i--;
				count=2;
				break;
			}
			else count++;
		}
		if(count == p_box->y-2)
		{
			line_move(i);//让后一行去覆盖当前行就可以抵消
			tmp++;
			count=2;
		}
	}
	score +=tmp;//加分
	if(score%LEVEL==0 && score !=0 && tmp !=0)
		level++;
	return -1;
}
static void clear_box(void)
{
	BOX *p_box=&box;
	int i,j;

	for(i=1; i < p_box->x-1; i++)
	{
		for(j=2;j < p_box->y-2 ; j++)
		{
			if( p_box->sbox[i][j] >=30000 && p_box->sbox[i][i] <= 50000)
					p_box->sbox[i][j]=0;
			if( p_box->sbox[i][j] >='A' && p_box->sbox[i][i] <= 'Z')
					p_box->sbox[i][j]=0;
			if( p_box->sbox[i][j] >='a' && p_box->sbox[i][i] <= 'z')
					p_box->sbox[i][j]=0;
			switch (p_box->sbox[i][j])
			{
				case  '@':	case  '!':	case  '&':	case  '^':	case  '~':
				case  '-':	case  '|':	case 3:		case 4:
					p_box->sbox[i][j]=0;break;
			}
		}
	}
}
static int box_up(void)
{
	int i,j,have=0;
	BOX *p_box=&box;
	XY save_x_y;
	for(i=0;i < ARR_xy.count;i++)
	{
		if(p_box->sbox[ ARR_xy.arr_xy[i].x-1][ARR_xy.arr_xy[i].y] != 0)
		{
			save_x_y.arr_xy[0] = ARR_xy.arr_xy[i];
			for(j=0;j < ARR_xy.count;j++)
			{
				if( (ARR_xy.arr_xy[j].x == (save_x_y.arr_xy[0].x-1) )&& ( ARR_xy.arr_xy[j].y == (save_x_y.arr_xy[0].y) ))
				{
					have=1;		break;
				}
				else	have=0;
			}
			if( have == 0 )
			{
				return -1;
			}
		}
	}

	for(i=0;i<ARR_xy.count;i++)//由于最初是由上而下遍历的所以现在先把最下面的往下将
	{
		p_box->sbox[ ARR_xy.arr_xy[i].x-1 ][ARR_xy.arr_xy[i].y] = \
				p_box->sbox[ ARR_xy.arr_xy[i].x ][ARR_xy.arr_xy[i].y];
		p_box->sbox[ ARR_xy.arr_xy[i].x ][ARR_xy.arr_xy[i].y]=0;
	      	ARR_xy.arr_xy[i].x ++;
	}	
	return 0;
}
static int box_down(void)
{
	int i,j,have=0;
	BOX *p_box=&box;
	XY save_x_y;
	//save_x_y.arr_xy[0].y = ARR_xy.arr_xy[0].y;
	//save_x_y.count=0;
	for(i=0;i < ARR_xy.count;i++)
	{
		if(p_box->sbox[ ARR_xy.arr_xy[i].x+1][ARR_xy.arr_xy[i].y] != 0)
		{
			save_x_y.arr_xy[0] = ARR_xy.arr_xy[i];
			for(j=0;j < ARR_xy.count;j++)
			{
				if( (ARR_xy.arr_xy[j].x == (save_x_y.arr_xy[0].x+1) )&& ( ARR_xy.arr_xy[j].y == (save_x_y.arr_xy[0].y) ))
				{
					have=1;		break;
				}
				else	have=0;
			}
			if( have == 0 )
			{
				//printf("save_x_y.count=%d i=%d,have=%d",save_x_y.arr_xy[0].x,i,have);
				//fflush(NULL);
				//sleep(1);
			return -1;
			}
		}
	}

	for(i=ARR_xy.count-1;i>=0;i--)//由于最初是由上而下遍历的所以现在先把最下面的往下将
	{
		p_box->sbox[ ARR_xy.arr_xy[i].x+1 ][ARR_xy.arr_xy[i].y] = \
				p_box->sbox[ ARR_xy.arr_xy[i].x ][ARR_xy.arr_xy[i].y];
		p_box->sbox[ ARR_xy.arr_xy[i].x ][ARR_xy.arr_xy[i].y]=0;
	      	ARR_xy.arr_xy[i].x ++;
	}	
	return 0;
}
static int overtop()
{
	int i,j;
	BOX *p_box=&box;
	i=1;
	for(j=2;j < p_box->y-2 ; j++)
	{
		if( p_box->sbox[i][j] >='A' && p_box->sbox[i][i] <= 'Z')
			return -1;//	p_box->sbox[i][j]=0;
		switch (p_box->sbox[i][j])
		{
			case 3:		case 4:
				return -1;//p_box->sbox[i][j]=0;break;
		}
	}
	return 0;

}
static void fall_box(int signo)
{
	int ret=0,retclear=0;
	int m_level=level;//将级别给他
	while(1)
	{
		ret=box_down();
		if(m_level==0|| ret ==-1)
			break;
		drow();
		m_level--;//这样就可以用级别控制下降速度的快慢
	}
	if(ret !=-1)
	{
		//if(change_flag!=1)
		drow();
		alarm(1);
	}
	else 
	{
		while(1)
		{
			retclear=clear_line();
			if(retclear == -1)
				break;
		}
		 over_flag=overtop();
		 if(over_flag == -1)
		 {
			start_flag=1;//游戏启动标志位
			 alarm(0);
			 clear_box();
			 gameover();
			 drow();
			 return;
			// exit(0);
		 }
		drow();
		one();
		var_box();//下降完就换个新的	
		drow();
		alarm(1);
		return ;
	}

}
static int setcolor(void)
{
	int i,j;
	for(i=0;i<p_var->x;i++)
		for(j=0;j<p_var->y;j++)
			if(p_var->var[i][j]!=0)
			{
				if(p_var->var[i][j] >30000 && p_var->var[i][j] < 50000)

					p_var->var[i][j]=(p_var->var[i][j]/100)*100+p_var->color;
				
				else p_var->var[i][j]=p_var->var[i][j]*10000+p_var->typenum*100+p_var->color;
			//	printf("%d ",p_var->var[i][j]);
			//	fflush(NULL);
			//	sleep(1);
			}
	return 0;
	
}
static int color_box(void)
{
	//return 0;
	//switch (1)
	switch (rand()%8)
	{
		case 0:p_var->color=40;       setcolor();       break;
		case 1:p_var->color=41;       setcolor();       break;
		case 2:p_var->color=42;       setcolor();       break;
		case 3:p_var->color=43;       setcolor();	break;
		case 4:p_var->color=44;       setcolor();       break;
		case 5:p_var->color=45;       setcolor();       break;
		case 6:p_var->color=46;       setcolor();       break;
		case 7:p_var->color=47;       setcolor();       break;
	}
	return 0;
}
static int var_box(void)
{
	int i,j;
	i=(rand()%10+1);
	//i=2;//这可以设置总是产生某一种图形
	switch (i)
	{
		case 1:	p_var=&m_one;color_box();	break;
		case 2:	
			switch((rand()%2+1))
			{
				case 1:p_var=&m_two_1;color_box();break;
				case 2:p_var=&m_two_2;color_box();break;
			}
			break;
		case 10:	
			switch((rand()%2+1))
			{
				case 1:p_var=&m_two_two_1;color_box();break;
				case 2:p_var=&m_two_two_2;color_box();break;
			}
			break;
		case 3:	
			switch((rand()%4+1))
			{
				case 1:p_var=&m_three_1;color_box();break;
				case 2:p_var=&m_three_2;color_box();break;
				case 3:p_var=&m_three_3;color_box();break;
				case 4:p_var=&m_three_4;color_box();break;
			}
			break;

		case 4:	
			switch((rand()%4+1))
			{
				case 1:	p_var=&m_four_1;color_box();break;
				case 2:	p_var=&m_four_2;color_box();break;
				case 3:	p_var=&m_four_3;color_box();break;
				case 4:	p_var=&m_four_4;color_box();break;
				
			}
			break;
		case 5:	
			switch((rand()%4+1))
			{
				case 1:	p_var=&m_five_1;color_box();break;
				case 2:	p_var=&m_five_2;color_box();break;
				case 3:	p_var=&m_five_3;color_box();break;
				case 4:	p_var=&m_five_4;color_box();break;
			}
			break;
		case 6:	
			switch((rand()%2+1))
			{
				case 1:	p_var=&m_six_1;	color_box();break;
				case 2:	p_var=&m_six_2;	color_box();break;
			}
			break;
		case 7:	
			switch((rand()%2+1))
			{
				case 1:	p_var=&m_seven_1;color_box();break;
				case 2:	p_var=&m_seven_2;color_box();break;
			}
			break;
		case 8:	
			switch((rand()%2+1))
			{
				case 1:	p_var=&m_eight_1;color_box();break;
				case 2:	p_var=&m_eight_2;color_box();break;
			}
			break;
		case 9:	
			switch((rand()%4+1))
			{
				case 1:	p_var=&m_nine_1;color_box();break;
				case 2:	p_var=&m_nine_2;color_box();break;
				case 3:	p_var=&m_nine_3;color_box();break;
				case 4:	p_var=&m_nine_4;color_box();break;
			}
			break;
	}
	return 0;
}

static int one(void)
{
	BOX *p_box=&box;
	int ret,i,j,box_x=1,box_y,flag=0;
	ARR_xy.count=0;
	
	m_old_var=*p_var;//这将目前的数据和他的属性提前作好备份，为了是在变形的时候使用
	old_var=&m_old_var;
	//setcolor();
	save_old_color=old_var->color;

	for (i=0;i< p_var->x ;i++)
	{
		for(j=0;j< p_var->y;j++)
		{
			if(p_var->var[i][j] !=0)
			{
				p_box->sbox[box_x][j+8] = p_var->var[i][j];
				flag=1;
				ARR_xy.arr_xy[ ARR_xy.count ].x=box_x;
				ARR_xy.arr_xy[ ARR_xy.count ].y=j+8;
				//printf("i=%d,j=%d",i,j);
				//fflush(NULL);
				//getchar();
				ARR_xy.count ++;
			}
		}
		if(flag==1)
		{
			box_x ++;
			flag=0;
		}
	}
	return 0;
}

static VAR *change__()
{
	switch (old_var->typenum)
	{
		case 10:	return NULL;//方块不用变形
			break;
		case 20://长条
			switch ((old_var->n)%2+1)
			{
				case 1:	return &m_two_1;break;
				case 2:	return &m_two_2;break;
			}break;
		case 22://小条
			switch ((old_var->n)%2+1)
			{
				case 1:	return &m_two_two_1;break;
				case 2:	return &m_two_two_2;break;
			}break;
		case 30://
			switch ((old_var->n)%4+1)
			{
				case 1:	return &m_three_1;break;
				case 2:	return &m_three_2;break;
				case 3:	return &m_three_3;break;
				case 4:	return &m_three_4;break;
			}break;
		case 40://
			switch ((old_var->n)%4+1)
			{
				case 1:	return &m_four_1;break;
				case 2:	return &m_four_2;break;
				case 3:	return &m_four_3;break;
				case 4:	return &m_four_4;break;
			}break;
		case 50:
			switch ((old_var->n)%4+1)
			{
				case 1:	return &m_five_1;break;
				case 2:	return &m_five_2;break;
				case 3:	return &m_five_3;break;
				case 4:	return &m_five_4;break;
			}break;
		case 60:
			switch ((old_var->n)%2+1)
			{
				case 1:	return &m_six_1;break;
				case 2:	return &m_six_2;break;
			}break;
		case 70:
			switch ((old_var->n)%2+1)
			{
				case 1:	return &m_seven_1;break;
				case 2:	return &m_seven_2;break;
			}break;
		case 80:
			switch ((old_var->n)%2+1)
			{
				case 1:	return &m_eight_1;break;
				case 2:	return &m_eight_2;break;
			}break;
		case 90:
			switch ((old_var->n)%4+1)
			{
				case 1:	return &m_nine_1;break;
				case 2:	return &m_nine_2;break;
				case 3:	return &m_nine_3;break;
				case 4:	return &m_nine_4;break;
			}break;
	}
	return NULL;
}

static VAR change_tmp;//本来想进行行列互换，但考虑到实现问题，就没再作
static  VAR *linetorow(VAR *tmp_var)
{
	int i,j;

	change_tmp=*tmp_var;
	
	for(i=0;i< tmp_var->x;i++)
		for(j=0;j<tmp_var->y;j++)
		{
			change_tmp.var[j][i]=tmp_var->var[i][j];
				//printf("i=%d,j=%d",i,j);
				//fflush(NULL);
				//sleep(1);
		}

	return &change_tmp;

}
static int change(void)
{
	int i,j,x=0,box_x,box_y,save_x,save_y,flag=0,have=0;
	int have_flag=0;//在同一行要判断两个方块是否想挨着，否则要在两个方块直接要加上下面的空格
	int space_count=0;
	//BOX *p_box=&box,tmp_box = box;
	BOX *p_box=&box;
	tmp_box = box;
	X_Y save_xy;
	XY save_x_y;
	save_x_y.count=0;

	save_xy=ARR_xy.arr_xy[0];
	save_x=box_x=save_xy.x;
	save_y=box_y=save_xy.y;
	
	VAR *tmp_var;
	
	tmp_var=change__();
	if(tmp_var==NULL)//方块或者错误时会返回NULL
		return -1;
	m_old_var=*tmp_var;//将当前的新的形状作记录保存
	
	//tmp_var = linetorow(&m_old_var);
	change_flag=1;
	//alarm(2);
#if 1   

	for(i=0;i<ARR_xy.count;i++)//先将原位置清零;
	{
		tmp_box.sbox[ARR_xy.arr_xy[i].x][ARR_xy.arr_xy[i].y]=0;

	}
	for (i=0;i< tmp_var->x ;i++)
	{
		for(j=0;j< tmp_var->y;j++)
		{
			if(tmp_var->var[i][j] !=0)//遍历到新的图形不等于0时
			{
				have_flag=1;

				if(save_x != box_x)
				{
					
					space_count=0;
					save_x =box_x;
					box_y  = box_y-save_y+j-1;//因为进入了下一行所以要考虑对齐的问题

				}
				//if(tmp_box.sbox[box_x][box_y] ==1 )
				//	return -1;
				if( box_x>=tmp_box.x-1 || box_x<1 || box_y >=tmp_box.y-2||box.y<2)
				{
					change_flag=0;
					return -1;//检测是否是边界
				}
				if(space_count!=0)
				{
					box_y +=space_count;
					space_count=0;

				}
				if(tmp_box.sbox[box_x][box_y] !=0 )
				{
					for(j=0;j < ARR_xy.count;j++)
					{
						if( (ARR_xy.arr_xy[j].x == (box_x) )&& ( ARR_xy.arr_xy[j].y == (box_y) ))
						{	have=1;
							break;
						}
						else have=0;
					}
					if(have==0)
					{
						change_flag=0;
						return -1;
					}
				}

					
				tmp_box.sbox[box_x][box_y] = tmp_var->var[i][j];
				
				if((tmp_box.sbox[box_x][box_y]>30000)&&(tmp_box.sbox[box_x][box_y]<50000))
					 tmp_box.sbox[box_x][box_y]=tmp_box.sbox[box_x][box_y]/100*100+save_old_color;//是将老的颜色复制过来

				else tmp_box.sbox[box_x][box_y]=tmp_box.sbox[box_x][box_y]*10000+tmp_var->typenum*100+save_old_color;
				
					flag=1;
					save_x_y.arr_xy[ save_x_y.count ].x=box_x;
					save_x_y.arr_xy[ save_x_y.count ].y=box_y;
					save_x_y.count ++;
					box_y++;
					save_y=j;
			}
			else if(have_flag==1)
				space_count++;
		}
		if(flag==1)
		{
			box_x ++;
			flag=0;
		}
	}


	ARR_xy=save_x_y;//最后将坐标记录也赋值回去
				//printf("i=%d,j=%d",ARR_xy.count,save_x_y.count);
				//fflush(NULL);
				//alarm(1);
				//sleep(0.5);

#endif
	return 0;
}

static int  leftmove(void)//左移动
{
	int i,x=0;
	BOX *p_box=&box;
	X_Y save_xy;
	save_xy=ARR_xy.arr_xy[0];
	for(i=0;i < ARR_xy.count;i++)
	{
		if(save_xy.x == ARR_xy.arr_xy[i].x)
		{
			if(save_xy.y >= ARR_xy.arr_xy[i].y) 
			{
				save_xy = ARR_xy.arr_xy[i];
			}
		}
		else 
		{
			if(p_box->sbox[ save_xy.x ][save_xy.y-2] != 0)
			{
				return -1;
			}
			save_xy = ARR_xy.arr_xy[i];
		}
	}
	if(p_box->sbox[ save_xy.x ][save_xy.y-2] != 0)//整体跳出时还要在判断一次
		return -1;
	
	for(i=0;i<ARR_xy.count;i++)
	{
		p_box->sbox[ ARR_xy.arr_xy[i].x ][ARR_xy.arr_xy[i].y-2] = \
				p_box->sbox[ ARR_xy.arr_xy[i].x ][ARR_xy.arr_xy[i].y];
		p_box->sbox[ ARR_xy.arr_xy[i].x ][ARR_xy.arr_xy[i].y]=0;
	      	ARR_xy.arr_xy[i].y--;
	      	ARR_xy.arr_xy[i].y--;
	}	
	return 0;
}
static int rightmove(void)//右移动
{
	int i;
	BOX *p_box=&box;
	X_Y save_xy;
	save_xy=ARR_xy.arr_xy[ARR_xy.count-1];
	//printf("ARR.count=%d ",ARR_xy.count);
	//fflush(NULL);
	for(i=ARR_xy.count-1; i>=0;i--)
	{
		if(save_xy.x == ARR_xy.arr_xy[i].x)
		{
			if(save_xy.y <= ARR_xy.arr_xy[i].y) 
			{
				save_xy = ARR_xy.arr_xy[i];
			}
		}
		else 
		{
			//printf("nowline=%d,minrow=%dsave_xy.y=%d %d",nowline,minrow,save_xy.x,save_xy.y-2);
			//printf("save_xy=%d %d",save_xy.x,save_xy.y+2);
			//fflush(NULL);
				if(p_box->sbox[ save_xy.x ][save_xy.y+2] != 0)
					return -1;
		
				save_xy = ARR_xy.arr_xy[i];
		}
	}
	if(p_box->sbox[ save_xy.x ][save_xy.y+2] != 0)
		return -1;
	
	for(i=ARR_xy.count-1;i>=0;i--)//由于最初是由上而下遍历的所以现在先把最下面的往下将
	{
		p_box->sbox[ ARR_xy.arr_xy[i].x ][ARR_xy.arr_xy[i].y+2] = \
				p_box->sbox[ ARR_xy.arr_xy[i].x ][ARR_xy.arr_xy[i].y];
		p_box->sbox[ ARR_xy.arr_xy[i].x ][ARR_xy.arr_xy[i].y]=0;
	      	ARR_xy.arr_xy[i].y++;
	      	ARR_xy.arr_xy[i].y++;
	}	
	return 0;

}
static void gameover__(const char *s,int i,int j)
{
	BOX *p_box=&box;
	while( (*s !='\0')&&(j<p_box->y-2))
	{
		if(*s !=' ')//防止空格
			p_box->sbox[i][j]=(int)*(s++);
		else {
			p_box->sbox[i][j]=0;
			s++;
		}
		j++;
	}

}
static int gameover(void)
{
	int i,j;
	BOX *p_box=&box;
	char *s1=" GAME OVER";
	char *s2=" b   RESTART";
	char *s3=" q   QUIT";
	char *s4="|  ^     ^  |";
	char *s5="|  @     @  |";
	char *s6="|  ~  !  ~  |";
	char *s7="|     &     |";
	char *s8="-------------";

	i=2;j=6;gameover__(s8,i,j);
	i=3;j=6;gameover__(s4,i,j);
	i=4;j=6;gameover__(s5,i,j);
	i=5;j=6;gameover__(s6,i,j);
	i=6;j=6;gameover__(s7,i,j);
	i=7;j=6;gameover__(s8,i,j);
	i=11;j=6;gameover__(s2,i,j);
	i=13;j=6;gameover__(s3,i,j);
	
	if(start_flag==1)
	{
		i=9;j=6;gameover__(s1,i,j);//如果没开始就不要显示它；
	}

}
static int setchar()//设置行列坐标
{
	int i;
	BOX *p_box=&box;
	for(i=0;i<p_box->y;i++)
	{
		p_box->sbox[0][i]=i+'A';
	}
	for(i=0;i<p_box->x;i++)
	{
		p_box->sbox[i][0]=i+'A';
	}
	return 0;

}
static void getusername()//获得玩家姓名，在执行程序时输出
{
	char *ch;
	
	while(1)
	{	
		printf("Please input your name:\n");
		ch=fgets(username,32-1,stdin);
		
		if(username[0] != '\0')
		{
			if(strlen(username)<=1)
			{
				printf("You input character too short,please input you name agin\n");
			}
			else{
			username[strlen(username)-1]='\0';//有于fgets在读取字符窜是会把换行符读入，然后在换行符后加空格，所以要自己将它往后减一位再添加'\0'
			break;
			}
		}
	}
	
}
static void gamehelp()
{
	int i=0;

	//printf("\33[u");//
//	printf("\33[u\33[2;10H\n");//清一下屏
	printf("\33[u\33[2J\33[2;10H\n");//清一下屏
	printf("\t\tWelcome use this game program\n");
	printf("\t\tThis game program's deviser  is \33[31mLinZhao\33[0m(Tony)\n");
	printf("\t\tb   -----   bagin game \n");
	printf("\t\tp   -----   pause game \n");
	printf("\t\tq   -----   quit game \n");
	printf("\t\th   -----   help  \n");
	printf("\t\ta or  direchtion left  -----  left move \n");
	printf("\t\td or  direchtion right -----  right move \n");
	printf("\t\ts or  direchtion down  -----  fall quick  \n");
	printf("\t\tx  -----  fall last quick  \n");
	printf("\t\tw   space or  direchtion up-----  change graph \n");
	printf("\n");
	printf("\n");
	while(1)
	{
		printf("\t\tPlease input any key continue ......^_^ \n");
		getchar();
		printf("\33[u\33[2J\33[2;10H\n");//清一下屏
		break;
	}
	

}

int init(void)
{
	int ret;
	//getusername();//获得玩家姓名
	srand(getpid());
	
	var_box();//提前获得一个随机图形

	ret = tcgetattr(0,&m_ter.old);//先保护现场  0  biaozhun  in    zhe shi bu neng yong  stdin 
	ret = tcgetattr(0,&m_ter.new);//将环境取到new中，
	m_ter.new.c_lflag = m_ter.new.c_lflag & ~(ICANON | ECHO);//将显示和  置零
	m_ter.new.c_cc[VMIN] = 1;//zuxiao in  1
	m_ter.new.c_cc[VTIME] = 0;// yan  shi  0; li  ji huo de 

	tcsetattr(0,TCSANOW,&m_ter.new);//sheng  xiao zhong duan 
	
	signal(SIGALRM,fall_box);// init fall time signal 

	printf("\33[2J\33[s");//保存光标位置

	//gamehelp();
	clear_box();
	gameover();
	drow();	

	return 0;

}
static int control__(const int ch)
{
	char key;
	int ret;
	switch(ch)
	{
		case 'b':
			start_flag=1;//游戏启动标志位
			pause_flag=0;
			score=0;level=0;
			clear_box();//setchar();
			one();var_box();drow();alarm(1);break;
		case 'p':
			if(start_flag==0)
				break;
			if(pause_flag==1)
			{
				
				pause_flag=0;
				alarm(1);
			}
			else {
				pause_flag=1;
				alarm(0);
			}
			break;
		case 'C':
			if(start_flag==0 || pause_flag==1)
				break;
			clear_box();drow();break;
		case 'a':
			if(start_flag==0 || pause_flag==1)
				break;
			leftmove();drow();break;
		case 'd':
			if(start_flag==0 || pause_flag==1)
				break;
			rightmove();drow();break;
		case 's':
			if(start_flag==0 || pause_flag==1)
				break;
			ret=box_down();
			drow();
			break;
		case 'u':
			if(start_flag==0 || pause_flag==1)
				break;
			alarm(0);
			ret=box_up();
			drow();
			alarm(1);
			break;
		case 'x':
			if(start_flag==0 || pause_flag==1)
				break;
			while(ret != -1)
				ret=box_down();
			drow();
			break;
		case 'w':	case ' ':
			if(start_flag==0 || pause_flag==1)
				break;
			if(change_flag != 1)
			{
				change();
				drow();
			}
			break;
		case 'l':
			if(start_flag==0 || pause_flag==1)
				break;
			clear_line();break;
		case 'h':
			if(start_flag==0 || pause_flag==1)
				break;
			alarm(0);gamehelp();drow();alarm(1);break;
			
		case 0x5b:
			if(start_flag==0 || pause_flag==1)
				break;
			key=getchar();
			switch (key)
			{
				case 0x41:
					if(change_flag !=1)
					{
						change();
						drow();
					}
					break;
				case 0x42:box_down();drow();break;
				case 0x43:rightmove();drow();break;
				case 0x44:leftmove();drow();break;
			}
			break;
	}
	return 0;
}
int control(void)
{
	char ch;
	int i;
	while(1)
	{
		ch = getchar();
		if(ch == 'q')
			return -1;
		control__(ch);//去判断按键值
		//printf("%x  ",ch);
		//fflush(NULL);
	}
	return 0;
	
}
void quit(void)
{
	tcsetattr(0,TCSANOW,&m_ter.old);//还原现场 
	printf("gameover\n");
	printf("\33[?25h");//恢复光标
}

