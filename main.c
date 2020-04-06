#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

// 控制台窗口 宽80 x 高40

int step = 0;
long int score = 0;
long int Time;
int BOX[4][4] = {0};

void gotoxy(int x, int y); // 设置控制台光标位置
void color(int x);         // 设置控制台窗口字体颜色和背景色
void mainMenu();           // 主菜单界面
void menuChoice();         // 菜单选择
void drawGameBox();        // 绘制游戏网格
void regulation();         // 游戏规则
void textColor(int x);     // 设置数字颜色
int keyDown();             // 键盘输入
int ifLeft();              // 能否左移
int ifRight();             // 能否右移
int ifUp();                // 能否上移
int ifDown();              // 能否下移
void drawNums();           // 绘制棋盘数字
void produceNums();        // 生成随机数字
void gamePlay();           // 开始游戏
void rePlay();             // 重新开始游戏
int ifWin();               // 游戏胜利
int ifLose();              // 游戏失败

// 设置控制台光标位置
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// 设置控制台窗口字体颜色和背景色
void color(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

// 数字颜色
void textColor(int x)
{
	switch(x)
	{
	case 2:
		color(1);
		break;
	case 4:
		color(2);
		break;
	case 8:
		color(3);
		break;
	case 16:
		color(4);
		break;
	case 32:
		color(5);
		break;
	case 64:
		color(6);
		break;
	case 128:
		color(7);
		break;
	case 256:
		color(8);
		break;
	case 512:
		color(9);
		break;
	case 1024:
		color(10);
		break;
	case 2048:
		color(11);
		break;
	}
}

// 能否左移
int ifLeft()
{
	int i, j;
	for(i = 0;i < 4;++i)
	{
		for(j = 3;j > 0;--j)
		{
			if(BOX[i][j] && (BOX[i][j] == BOX[i][j-1] || !BOX[i][j-1]))
				return 1;
		}
	}
	return 0;
}

// 能否右移
int ifRight()
{
	int i, j;
	for(i = 0;i < 4;++i)
	{
		for(j = 0;j < 3;++j)
		{
			if(BOX[i][j] && (BOX[i][j] == BOX[i][j+1] || !BOX[i][j+1]))
				return 1;
		}
	}
	return 0;
}

// 能否上移
int ifUp()
{
	int i, j;
	for(j = 0;j < 4;++j)
	{
		for(i = 3;i > 0;--i)
		{
			if(BOX[i][j] && (BOX[i][j] == BOX[i-1][j] || !BOX[i-1][j]))
				return 1;
		}
	}
	return 0;
}

// 能否下移
int ifDown()
{
	int i, j;
	for(j = 0;j < 4;++j)
	{
		for(i = 0;i < 3;++i)
		{
			if(BOX[i][j] && (BOX[i+1][j] == BOX[i][j] || !BOX[i+1][j]))
				return 1;
		}
	}
	return 0;
}

// 合并相同数字
int *add(int *item)
{
	int i, k = 0;
	int *nums = (int*)calloc(4, sizeof(int));
	int *tmp = (int*)calloc(4, sizeof(int));
	for(i = 0;i < 4;++i)
	{
		if(item[i])
			nums[k++] = item[i];
	}
	for(i = 0;i < 3;++i)
	{
		if(nums[i] == nums[i+1])
		{
			nums[i] *= 2;
			nums[i+1] = 0;
			score += nums[i];
		}
	}
	for(i = 0, k = 0;i < 4;++i)
	{
		if(nums[i])
			tmp[k++] = nums[i];
	}
	return tmp;
}

// 绘制游戏棋盘
void drawGameBox()
{
	int i, j;
	color(7);
	for(i = 3;i < 20;++i)
	{
		for(j = 20;j < 61;++j)
		{
			gotoxy(j, i);
			if(i == 3 || i == 7 || i == 11 || i == 15 || i == 19)
				printf("-");
			else
			{
				printf("|         |         |         |         |");
				break;
			}
		}
	}
	gotoxy(20, 2);
	printf("得分：%d", score);
	gotoxy(45, 2);
	printf("执行步数：%d", step);
	gotoxy(45, 20);
	printf("已用时：%d s", time(NULL) - Time);
}

// 绘制棋盘数字
void drawNums()
{
	int i, j;
	for(i = 0;i < 4;++i)
	{
		for(j = 0;j < 4;++j)
		{
			if(BOX[i][j])
			{
				gotoxy(25 + j * 10, 5 + i * 4);
				textColor(BOX[i][j]);
				printf("%d", BOX[i][j]);
			}
		}
	}
}

// 游戏规则说明
void regulation()
{
	int i, j;
	system("cls");
	color(15);
	gotoxy(35, 3);
	printf("游戏规则");
	color(7);
	for(i = 5;i < 20;++i)
	{
		for(j = 10;j < 70;++j)
		{
			gotoxy(j, i);
			if(i == 5 || i == 19)
				printf("=");
			else if(j == 10 || j == 68)
				printf("||");
		}
	}
	color(15);
	gotoxy(13, 7);
	printf("tips1：玩家可以通过↑ ↓ ← →方向键来移动方块");
	gotoxy(13, 9);
	printf("tips2：按ESC退出游戏");
	gotoxy(13, 11);
	printf("tips3：玩家选择的方向上，若有相同的数字则合并");
	gotoxy(13, 13);
	printf("tips4：每移动一步，空位随机出现一个2或4");
	gotoxy(13, 15);
	printf("tips5：棋盘被数字填满，无法进行有效移动，游戏失败");
	gotoxy(13, 17);
	printf("tips6：棋盘上出现2048，游戏胜利");
}

// 生成随机数字
void produceNums()
{
	int x, y;
	srand(time(0));
	do{
		x = rand() % 4;
		y = rand() % 4;
	}while(BOX[x][y]);
	if(rand() % 4 == 0)
		BOX[x][y] = 4;
	else
		BOX[x][y] = 2;
}

// 求棋盘上最大数字
int maxNums()
{
	int i, j, max = INT_MIN;
	for(i = 0;i < 4;++i)
	{
		for(j = 0;j < 4;++j)
		{
			if(BOX[i][j] > max)
				max = BOX[i][j];
		}
	}
	return max;
}

// 游戏胜利
int ifWin()
{
	int flag = 0;
	if(2048 == maxNums())
	{
		system("cls");
		color(11);
		gotoxy(6,6);
		printf("■              ■              ■     ■■■■■     ■       ■");
		gotoxy(6,7);
		printf(" ■            ■■            ■          ■         ■■     ■");
		gotoxy(6,8);
		printf("  ■          ■  ■          ■           ■         ■ ■    ■");
		gotoxy(6,9);
		printf("   ■        ■    ■        ■            ■         ■  ■   ■");
		gotoxy(6,10);
		printf("    ■      ■      ■      ■             ■         ■   ■  ■");
		gotoxy(6,11);
		printf("     ■    ■        ■    ■              ■         ■    ■ ■");
		gotoxy(6,12);
		printf("      ■  ■          ■  ■               ■         ■     ■■");
		gotoxy(6,13);
		printf("       ■■            ■■            ■■■■■     ■      ■");
		flag = 1;
	}
	return flag;
}

// 游戏失败
int ifLose()
{
	int flag = 0;
	if(ifLeft() + ifRight() + ifUp() + ifDown() == 0)
	{
		system("cls");
		color(12);
		gotoxy(19, 6);
		printf("■■■■■    ■         ■    ■■");
		gotoxy(19, 7);
		printf("■            ■■       ■    ■ ■");
		gotoxy(19, 8);
		printf("■            ■ ■      ■    ■  ■");
		gotoxy(19, 9);
		printf("■            ■  ■     ■    ■   ■");
		gotoxy(19, 10);
		printf("■■■■      ■   ■    ■    ■    ■");
		gotoxy(19, 11);
		printf("■            ■    ■   ■    ■   ■");
		gotoxy(19, 12);
		printf("■            ■     ■  ■    ■  ■");
		gotoxy(19, 13);
		printf("■            ■      ■ ■    ■ ■");
		gotoxy(19, 14);
		printf("■■■■■    ■       ■■    ■■");
		flag = 1;
	}
	return flag;
}

// 开始游戏
void gamePlay()
{
	int i, j, x, y, n;
	system("cls");
	Time = time(NULL);
	drawGameBox();
	produceNums();
	drawNums();

	while(1)
	{
		if(keyDown(getch()))
		{
			drawGameBox();
			produceNums();
			drawNums();
			++step;

			if(ifWin() || ifLose())
			{
				gotoxy(20, 20);
				color(12);
				printf("请输入：（1.再来一局 2.结束游戏）：");
				scanf("%d",&n);
				switch(n)
				{
				case 1:
					rePlay();
					break;
				case 2:
					exit(0);
					break;
				default:
					printf("输入错误，请重新输入！\n");
				}
			}
		}
	}
}

// 重新开始游戏
void rePlay()
{
	system("cls");
	score = 0;
	step = 0;
	memset(BOX, 0, 16 * sizeof(int));
	gamePlay();
}

// 键盘输入
int keyDown(int key)
{
	int i, tmp[4] = {0};
	int *p;
	char ch;
	switch(key)
	{
	case 27: // ESC的ASCII码
		color(12);
		gotoxy(20, 20);
		printf("确定退出游戏么？（y/n）");
		ch = getch();
		if(ch == 'Y' || ch == 'y')
			exit(0);
		else if(ch == 'N' || ch == 'n')
		{
			gotoxy(20,20);
			printf("                            ");
		}
		break;
	case 75: // 左
		if(ifLeft())
		{
			for(i = 0;i < 4;++i)
			{
				tmp[0] = BOX[i][0];
				tmp[1] = BOX[i][1];
				tmp[2] = BOX[i][2];
				tmp[3] = BOX[i][3];
				p = add(tmp);
				BOX[i][0] = p[0];
				BOX[i][1] = p[1];
				BOX[i][2] = p[2];
				BOX[i][3] = p[3];
			}
		}
		break;
	case 72: // 上
		if(ifUp())
		{
			for(i = 0;i < 4;++i)
			{
				tmp[0] = BOX[0][i];
				tmp[1] = BOX[1][i];
				tmp[2] = BOX[2][i];
				tmp[3] = BOX[3][i];
				p = add(tmp);
				BOX[0][i] = p[0];
				BOX[1][i] = p[1];
				BOX[2][i] = p[2];
				BOX[3][i] = p[3];
			}
		}
		break;
	case 77: // 右
		if(ifRight())
		{
			for(i = 0;i < 4;++i)
			{
				tmp[3] = BOX[i][0];
				tmp[2] = BOX[i][1];
				tmp[1] = BOX[i][2];
				tmp[0] = BOX[i][3];
				p = add(tmp);
				BOX[i][0] = p[3];
				BOX[i][1] = p[2];
				BOX[i][2] = p[1];
				BOX[i][3] = p[0];
			}
		}
		break;
	case 80: // 下
		if(ifDown())
		{
			for(i = 0;i < 4;++i)
			{
				tmp[3] = BOX[0][i];
				tmp[2] = BOX[1][i];
				tmp[1] = BOX[2][i];
				tmp[0] = BOX[3][i];
				p = add(tmp);
				BOX[0][i] = p[3];
				BOX[1][i] = p[2];
				BOX[2][i] = p[1];
				BOX[3][i] = p[0];
			}
		}
		break;
	default:
		return 0;
		break;
	}
	return 1;
}

// 主菜单界面
void mainMenu()
{
	int i, j;
	// 绘制标题2048
	color(11);
	gotoxy(15,2);
	printf("■■■■■   ■■■■■   ■   ■     ■■■■■");
	gotoxy(15,3);
	printf("        ■   ■      ■   ■   ■     ■      ■");
	gotoxy(15,4);
	printf("        ■   ■      ■   ■   ■     ■      ■");
	gotoxy(15,5);
	printf("■■■■■   ■      ■   ■   ■     ■■■■■");
	gotoxy(15,6);
	printf("■           ■      ■   ■■■■■  ■      ■");
	gotoxy(15,7);
	printf("■           ■      ■        ■     ■      ■");
	gotoxy(15,8);
	printf("■■■■■   ■■■■■        ■     ■■■■■");

	// 绘制选项菜单
	color(7);
	for(j = 10;j < 21;++j) // 行
	{
		for(i = 15;i < 63;++i) // 列
		{
			gotoxy(i, j);
			if(j == 10 || j == 20)
				printf("=");
			else if(i == 15 || i == 61)
				printf("||");
		}
	}
	color(15);
	gotoxy(33, 12);
	printf("1.开始游戏");
	gotoxy(33, 15);
	printf("2.游戏规则");
	gotoxy(33, 18);
	printf("3.退出");
}

// 菜单选择
void menuChoice()
{
	int n;
	gotoxy(28, 21);
	printf("请输入[1 2 3]：[ ]\b\b");
	scanf("%d", &n);
	switch(n)
	{
	case 1:
		system("cls");
		gamePlay();
		break;
	case 2:
		regulation();
		break;
	case 3:
		exit(0);
		break;
	default:
		break;
	}
}

void main()
{
	while(1)
	{
		mainMenu();
		menuChoice();
		getch();
		system("cls");
	}
}
