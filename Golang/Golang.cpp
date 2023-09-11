//Golang
/*
* @name:Golang
* @Language:C
* @tools:EasyX，Visual Studio commity 2022
* @author:yq
* @time:20230911

*/
#include<easyx.h>
#include<math.h>
#include<stdio.h>
#pragma comment(lib,"winmm.lib")//open the static music library


//棋盘背景图
IMAGE pic;
//设置棋盘数据结构：数组
int arrMap[20][20] = { 0 };//0表示空白   1表示黑棋   2表示白棋
//标志位
int flag = 0;//偶数表示要下黑棋   奇数表示要下白棋

//声明
void chessboard();//背景样式
void playBackgammon();//计算棋子的虚拟位置和棋盘位置；触发下棋；触发判断、弹出获胜消息并结束循环。
int judge();//判断WIN


//地图
void chessboard()
{
	//批量画图
	BeginBatchDraw();

	loadimage(NULL, _T("./背景.jpg"));
	putimage(0, 0, &pic);

	//画棋盘
	setlinecolor(BLACK);//设置当前的画线颜色是黑色
	for (int j = 1; j < 20; j++)
	{
		line(25 * j, 0, 25 * j, 500);  //画竖线
		line(0, 25 * j, 500, 25 * j); //画横线
	}
	//画边界线
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);//设置画线的样式
	line(500, 0, 500, 500);

	//显示玩家信息
	TCHAR s1[] = _T("玩家1:黑棋");
	TCHAR s2[] = _T("玩家2:白棋");
	outtextxy(512, 100, s1);
	outtextxy(512, 130, s2);

	//结束批量画图
	EndBatchDraw();
}

//下棋
void playBackgammon()
{
	int x = 0, y = 0;//落子在棋盘上的位置

	mciSendString(_T("open G弦之歌.mp3"), 0, 0, 0);//打开音乐
	mciSendString(_T("play G弦之歌.mp3"), 0, 0, 0);//播放音乐

	//鼠标消息变量 
	ExMessage msg;
	BYTE filter = EX_MOUSE;
	while (1)
	{
		//获取鼠标消息
		msg = getmessage(filter);
		
		int i = 0, j = 0;
		int a = 0, b = 0;//落子在数组的位置
		for (i = 1; i < 20; i++)
		{
			for (j = 1; j < 20; j++)
			{
				if (abs(msg.y - i * 25) < 12 && abs(msg.x - j * 25) < 12)
				{
					a = i;
					b = j;
					x = j * 25;
					y = i * 25;
				}
			}
		}

		//左键按下
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (arrMap[a][b] != 0)//落子的位置有棋子，需要重新下
			{
				continue;
			}
			if (flag % 2 == 0)//下黑棋
			{
				setfillcolor(BLACK);//设置当前设备填充颜色是黑色
				solidcircle(x, y, 10);
				arrMap[a][b] = 1;
			}
			else//下白棋
			{
				setfillcolor(WHITE);//设置当前设备填充颜色是白色
				solidcircle(x, y, 10);
				arrMap[a][b] = 2;
			}
			flag++;

			//玩家赢
			if (judge())
			{
				mciSendString(_T("close G弦之歌.mp3"), 0, 0, 0);//关闭音乐
				if (flag % 2 == 1)//黑
				{
					MessageBox(GetHWnd(), _T("玩家1：胜利!"), _T("游戏结束"), MB_OK);
					return;
				}
				else  //白
				{
					MessageBox(GetHWnd(), _T("玩家2：胜利!"), _T("游戏结束"), MB_OK);
					return;
				}
			}
		}
	}
}

//判断输赢
int judge()
{
	int i = 0, j = 0;
	int t = 2 - flag % 2;//1黑棋   2表示白棋

	for (i = 1; i < 20; i++)//i表示数组的下标
	{
		for (j = 1; j < 16; j++)
		{
			//横线
			if (arrMap[i][j] == t && arrMap[i][j + 1] == t && arrMap[i][j + 2] == t && arrMap[i][j + 3] == t
				&& arrMap[i][j + 4] == t)
			{
				return 1;
			}
		}
	}

	for (i = 1; i < 16; i++)
	{
		for (j = 1; j < 20; j++)
		{
			//竖线
			if (arrMap[i][j] == t && arrMap[i + 1][j] == t && arrMap[i + 2][j] == t && arrMap[i + 3][j] == t
				&& arrMap[i + 4][j] == t)
			{
				return 1;
			}
		}
	}

	for (i = 1; i < 16; i++)
	{
		for (j = 1; j < 16; j++)
		{
			//判断   \   
			if (arrMap[i][j] == t && arrMap[i + 1][j + 1] == t && arrMap[i + 2][j + 2] == t && arrMap[i + 3][j + 3] == t
				&& arrMap[i + 4][j + 4] == t)
			{
				return 1;
			}
		}
	}

	for (i = 1; i < 16; i++)
	{
		for (j = 5; j < 20; j++)
		{
			//判断   /   
			if (arrMap[i][j] == t && arrMap[i + 1][j - 1] == t && arrMap[i + 2][j - 2] == t && arrMap[i + 3][j - 3] == t
				&& arrMap[i + 4][j - 4] == t)
			{
				return 1;
			}
		}
	}
	return 0;
}


int main()
{
	initgraph(600, 500);//打开窗口  宽度600  高度500

	chessboard();

	playBackgammon();
	
	closegraph();//关闭窗口

	return 0;
}