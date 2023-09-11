//Golang
/*
* @name:Golang
* @Language:C
* @tools:EasyX��Visual Studio commity 2022
* @author:yq
* @time:20230911

*/
#include<easyx.h>
#include<math.h>
#include<stdio.h>
#pragma comment(lib,"winmm.lib")//open the static music library


//���̱���ͼ
IMAGE pic;
//�����������ݽṹ������
int arrMap[20][20] = { 0 };//0��ʾ�հ�   1��ʾ����   2��ʾ����
//��־λ
int flag = 0;//ż����ʾҪ�º���   ������ʾҪ�°���

//����
void chessboard();//������ʽ
void playBackgammon();//�������ӵ�����λ�ú�����λ�ã��������壻�����жϡ�������ʤ��Ϣ������ѭ����
int judge();//�ж�WIN


//��ͼ
void chessboard()
{
	//������ͼ
	BeginBatchDraw();

	loadimage(NULL, _T("./����.jpg"));
	putimage(0, 0, &pic);

	//������
	setlinecolor(BLACK);//���õ�ǰ�Ļ�����ɫ�Ǻ�ɫ
	for (int j = 1; j < 20; j++)
	{
		line(25 * j, 0, 25 * j, 500);  //������
		line(0, 25 * j, 500, 25 * j); //������
	}
	//���߽���
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);//���û��ߵ���ʽ
	line(500, 0, 500, 500);

	//��ʾ�����Ϣ
	TCHAR s1[] = _T("���1:����");
	TCHAR s2[] = _T("���2:����");
	outtextxy(512, 100, s1);
	outtextxy(512, 130, s2);

	//����������ͼ
	EndBatchDraw();
}

//����
void playBackgammon()
{
	int x = 0, y = 0;//�����������ϵ�λ��

	mciSendString(_T("open G��֮��.mp3"), 0, 0, 0);//������
	mciSendString(_T("play G��֮��.mp3"), 0, 0, 0);//��������

	//�����Ϣ���� 
	ExMessage msg;
	BYTE filter = EX_MOUSE;
	while (1)
	{
		//��ȡ�����Ϣ
		msg = getmessage(filter);
		
		int i = 0, j = 0;
		int a = 0, b = 0;//�����������λ��
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

		//�������
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (arrMap[a][b] != 0)//���ӵ�λ�������ӣ���Ҫ������
			{
				continue;
			}
			if (flag % 2 == 0)//�º���
			{
				setfillcolor(BLACK);//���õ�ǰ�豸�����ɫ�Ǻ�ɫ
				solidcircle(x, y, 10);
				arrMap[a][b] = 1;
			}
			else//�°���
			{
				setfillcolor(WHITE);//���õ�ǰ�豸�����ɫ�ǰ�ɫ
				solidcircle(x, y, 10);
				arrMap[a][b] = 2;
			}
			flag++;

			//���Ӯ
			if (judge())
			{
				mciSendString(_T("close G��֮��.mp3"), 0, 0, 0);//�ر�����
				if (flag % 2 == 1)//��
				{
					MessageBox(GetHWnd(), _T("���1��ʤ��!"), _T("��Ϸ����"), MB_OK);
					return;
				}
				else  //��
				{
					MessageBox(GetHWnd(), _T("���2��ʤ��!"), _T("��Ϸ����"), MB_OK);
					return;
				}
			}
		}
	}
}

//�ж���Ӯ
int judge()
{
	int i = 0, j = 0;
	int t = 2 - flag % 2;//1����   2��ʾ����

	for (i = 1; i < 20; i++)//i��ʾ������±�
	{
		for (j = 1; j < 16; j++)
		{
			//����
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
			//����
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
			//�ж�   \   
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
			//�ж�   /   
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
	initgraph(600, 500);//�򿪴���  ���600  �߶�500

	chessboard();

	playBackgammon();
	
	closegraph();//�رմ���

	return 0;
}