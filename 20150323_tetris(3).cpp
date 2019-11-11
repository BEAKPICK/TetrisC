#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cstdlib>
#include <iomanip>
#include <ctime>
using namespace std;

#define ESC 27 //게임종료
#define LEFT 75 //왼쪽화살표키
#define RIGHT 77 //오른쪽화살표키
#define DOWN 80 //아래화살표키
#define UP 72 //위쪽화살표키
#define SPACE 32 //스페이스바
#define NORMAL 80 // 평소 블록이 내려가는 속도
#define FAST 10 // 아래 버튼을 눌렀을때 내려가는 속도
#define LEFTMAX 12 // 왼쪽끝
#define RIGHTMAX 30 // 오른쪽끝
#define BSIZE 4 //블록크기
#define BROTATION 28 //회전블럭수(블록추가할때마다 바꿔줌)
#define HSIZE 14 // 테두리포함 GAME BOARD 가로크기
#define VSIZE 36 // 테두리포함 GAME BOARD 세로크기
#define GAMEBOARDSTARTX 10
#define GAMEBOARDSTARTY 1
#define NEXTBLOCKSTARTX 40
#define NEXTBLOCKSTARTY 3
#define SCORESTARTX 40
#define SCORESTARTY 16
#define NEXTBLOCKV 5
#define NEXTBLOCKH 5
#define SCOREV 2
#define SCOREH 5
#define SAFE 1
#define NOTSAFE 0

int block[BROTATION][BSIZE][BSIZE] = {{0,0,0,0,
									   1,1,1,1,
									   0,0,0,0,
									   0,0,0,0}, //블럭 0도

									  {0,0,1,0,
									   0,0,1,0,
									   0,0,1,0,
									   0,0,1,0}, //블럭 90도

									  {0,0,0,0,
									   1,1,1,1,
									   0,0,0,0,
									   0,0,0,0}, //블럭 180도

									  {0,1,0,0,
									   0,1,0,0,
									   0,1,0,0,
									   0,1,0,0}, //블럭 270도

									  {0,0,0,0,
									   0,1,1,0,
									   0,0,1,0,
									   0,0,1,0}, //블럭 0도

									  {0,0,0,0,
									   0,0,0,1,
									   0,1,1,1,
									   0,0,0,0}, //블럭 90도

									  {0,1,0,0,
									   0,1,0,0,
									   0,1,1,0,
									   0,0,0,0}, //블럭 180도

									  {0,0,0,0,
									   1,1,1,0,
									   1,0,0,0,
									   0,0,0,0}, //블럭 270도

									  {0,0,0,0,
									   0,1,1,0,
									   0,1,1,0,
									   0,0,0,0}, //블럭 0도

									  {0,0,0,0,
									   0,1,1,0,
									   0,1,1,0,
									   0,0,0,0}, //블럭 90도

									  {0,0,0,0,
									   0,1,1,0,
									   0,1,1,0,
									   0,0,0,0}, //블럭 180도

									  {0,0,0,0,
									   0,1,1,0,
									   0,1,1,0,
									   0,0,0,0}, //블럭 270도

									  {0,0,0,0,
									   0,0,1,0,
									   0,1,1,0,
									   0,1,0,0}, //블럭 0도

									  {0,0,0,0,
									   0,1,1,0,
									   0,0,1,1,
									   0,0,0,0}, //블럭 90도

									  {0,1,0,0,
									   0,1,1,0,
									   0,0,1,0,
									   0,0,0,0}, //블럭 180도

									  {0,0,0,0,
									   0,0,1,1,
									   0,1,1,0,
									   0,0,0,0}, //블럭 270도

									  {0,0,0,0,
									   0,1,0,0,
									   1,1,1,0,
									   0,0,0,0}, //블럭 0도

									  {0,0,1,0,
									   0,1,1,0,
									   0,0,1,0,
									   0,0,0,0}, //블럭 90도

									  {0,0,0,0,
									   0,1,1,1,
									   0,0,1,0,
									   0,0,0,0}, //블럭 180도

									  {0,0,0,0,
									   0,1,0,0,
									   0,1,1,0,
									   0,1,0,0}, //블럭 270도
									  
									  {0,0,0,0,
									   1,1,1,0,
									   0,0,1,0,
									   0,0,0,0}, //블럭 0도

									  {0,0,1,0,
									   0,0,1,0,
									   0,1,1,0,
									   0,0,0,0}, //블럭 90도

									  {0,0,0,0,
									   0,1,0,0,
									   0,1,1,1,
									   0,0,0,0}, //블럭 180도

									  {0,0,0,0,
									   0,1,1,0,
									   0,1,0,0,
									   0,1,0,0}, //블럭 270도

									  {0,0,0,0,
									   1,1,0,1,
									   0,1,1,1,
									   0,0,0,0}, //블럭 0도

									  {0,1,1,0,
									   0,0,1,0,
									   0,1,1,0,
									   0,1,0,0}, //블럭 90도

									  {0,0,0,0,
									   1,1,1,0,
									   1,0,1,1,
									   0,0,0,0}, //블럭 180도

									  {0,0,1,0,
									   0,1,1,0,
									   0,1,0,0,
									   0,1,1,0}}; //블럭 270도
//3차원 배열 한개에 블록 모두 다 저장


enum GameAction{MOVE_LEFT = 1, MOVE_RIGHT, MOVE_DOWN, GAME_QUIT, ROTATION, SKIP_DOWN};

void gotoxy(int x, int y) 
{
 COORD Pos = {x, y};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void setdisplay(int (*gameboard)[HSIZE])
{
	int a;
	gotoxy(GAMEBOARDSTARTX, GAMEBOARDSTARTY-1);
	cout << "[GAME BOARD]";
	gotoxy(NEXTBLOCKSTARTX, NEXTBLOCKSTARTY-1);
	cout << "[NEXT BLOCK]";
	gotoxy(SCORESTARTX, SCORESTARTY-1);
	cout << "[GAME SCORE]";
	for(a = GAMEBOARDSTARTX; a < GAMEBOARDSTARTX+(2*HSIZE)-2; a+=2)		//gameboard=
	{
		gotoxy(a, GAMEBOARDSTARTY);
		cout << "□";
		gotoxy(a, GAMEBOARDSTARTY+VSIZE-1);
		cout << "□";
	}
	for(a = GAMEBOARDSTARTY; a <= GAMEBOARDSTARTY+VSIZE-1; a++)		//gameboard||
	{
		gotoxy(GAMEBOARDSTARTX, a);
		cout << "□";
		gotoxy(GAMEBOARDSTARTX+(HSIZE*2)-2, a);
		cout << "□";
	}
	for(a = NEXTBLOCKSTARTX; a < NEXTBLOCKSTARTX+(NEXTBLOCKH*2); a+=2)	//nextblock=
	{
		gotoxy(a, NEXTBLOCKSTARTY);
		cout << "□";
		gotoxy(a, NEXTBLOCKSTARTY+NEXTBLOCKH);
		cout << "□";
	}
	for(a = NEXTBLOCKSTARTY; a <= NEXTBLOCKSTARTY+NEXTBLOCKV; a++)	//nextblock||
	{
		gotoxy(NEXTBLOCKSTARTX, a);
		cout << "□";
		gotoxy(NEXTBLOCKSTARTX+(NEXTBLOCKH*2), a);
		cout << "□";
	}
	for(a = SCORESTARTX; a <= SCORESTARTX+(SCOREH*2); a+=2)		//score=
	{
		gotoxy(a, SCORESTARTY);
		cout << "□";
		gotoxy(a, SCORESTARTY+SCOREV);
		cout << "□";
	}
	for(a = SCORESTARTY; a <= SCORESTARTY+SCOREV; a++)		//score||
	{
		gotoxy(SCORESTARTX, a);
		cout << "□";
		gotoxy(SCORESTARTX+(SCOREH*2), a);
		cout << "□";
	}
	for(a = 0; a < VSIZE; a++)		//게임보드배열테두리에 1 칠하기
	{
		gameboard[a][0] = 1;
		gameboard[a][HSIZE-1] = 1;
	}
	for(a = 0; a < HSIZE; a++)
	{
		gameboard[0][a] = 1;
		gameboard[VSIZE-1][a] = 1;
	}
}

int getGameAction(int action)
{
 int keyValue,act=action;
 if(kbhit() != 0) 
 {
	  keyValue=getch(); 
	 if (keyValue == 224)
	 {
		keyValue=getch();
	 }
	 switch (keyValue)
	 {
	   case ESC:
		   act = GAME_QUIT;
			   break;
	   case LEFT: 
		  act = MOVE_LEFT;
		  break;
	   case RIGHT: 
		  act = MOVE_RIGHT;
		  break;
	   case DOWN:
		  act = MOVE_DOWN;
      		  break;
	   case UP:
		   act = ROTATION;
		   break;
	   case SPACE:
		   act = SKIP_DOWN;
		   break;
	   default :
		  break;
	  }
 }
  return act;
}

int choose(int (*nextblock)[BSIZE])		//블록추가시 랜덤고를때도 추가하기
{
	int r, i1, i2, h = 0;
	r = rand()%7 + 1;
	switch(r)
	{
	case 1:
		{
			for(i1=0;i1<BSIZE;i1++)
			{
				for(i2=0;i2<BSIZE;i2++)
				{
					nextblock[i1][i2] = block[0][i1][i2];
				}
			}
			break;
		}
	case 2:
		{
			for(i1=0;i1<BSIZE;i1++)
			{
				for(i2=0;i2<BSIZE;i2++)
				{
					nextblock[i1][i2] = block[4][i1][i2];
				}
			}
			break;
		}
	case 3:
		{
			for(i1=0;i1<BSIZE;i1++)
			{
				for(i2=0;i2<BSIZE;i2++)
				{
					nextblock[i1][i2] = block[8][i1][i2];
				}
			}
			break;
		}
	case 4:
		{
			for(i1=0;i1<BSIZE;i1++)
			{
				for(i2=0;i2<BSIZE;i2++)
				{
					nextblock[i1][i2] = block[12][i1][i2];
				}
			}
			break;
		}
	case 5:
		{
			for(i1=0;i1<BSIZE;i1++)
			{
				for(i2=0;i2<BSIZE;i2++)
				{
					nextblock[i1][i2] = block[16][i1][i2];
				}
			}
			break;
		}
	case 6:
		{
			for(i1=0;i1<BSIZE;i1++)
			{
				for(i2=0;i2<BSIZE;i2++)
				{
					nextblock[i1][i2] = block[20][i1][i2];
				}
			}
			break;
		}
	case 7:
		{
			for(i1=0;i1<BSIZE;i1++)
			{
				for(i2=0;i2<BSIZE;i2++)
				{
					nextblock[i1][i2] = block[24][i1][i2];
				}
			}
			break;
		}
	}

	gotoxy(NEXTBLOCKSTARTX+2, NEXTBLOCKSTARTY+2);
		for(i1 = 0; i1 < BSIZE; i1++)
		{
			for(i2 = 0; i2 < BSIZE; i2++)
			{
				gotoxy(NEXTBLOCKSTARTX+2+h, NEXTBLOCKSTARTY+1+i1);
				cout << "  ";
				h+=2;
			}
			h = 0;
		}
	gotoxy(NEXTBLOCKSTARTX+2, NEXTBLOCKSTARTY+2);
		for(i1 = 0; i1 < BSIZE; i1++)
		{
			for(i2 = 0; i2 < BSIZE; i2++)
			{
				gotoxy(NEXTBLOCKSTARTX+2+h, NEXTBLOCKSTARTY+1+i1);
				if(nextblock[i1][i2] == 1) cout << "■";
				h+=2;
			}
			h = 0;
		}
	if(r==1) return 0;
	else if(r==2) return 4;
	else if(r==3) return 8;
	else if(r==4) return 12;
	else if(r==5) return 16;
	else if(r==6) return 20;
	else if(r==7) return 24;
	else
	{
		cout << "치명적인 에러가 발생했습니다";
	}
}

void scoreprint (int &score)
{
	gotoxy(SCORESTARTX+4, SCORESTARTY+(SCOREV/2));
	score+=10;
	cout << score;
}

void boardprint (int (*gameboard)[HSIZE])		//쌓였을 때 새긴후의 모습을 출력
{
	int i = 1, h = 1, x = GAMEBOARDSTARTX, y = GAMEBOARDSTARTY+1;
	for(i = 1; i < VSIZE-1; i++)
	{
		for(h = 1; h < HSIZE-1; h++)
		{
			gotoxy(x+=2, y);
			if(gameboard[i][h] == 1) cout << "▨";
			else if(gameboard[i][h] == 0) cout << "  ";
		}
		cout << endl;
		y++;
		x = GAMEBOARDSTARTX;
	}
}

void boardprint_debug (int (*gameboard)[HSIZE])		//gameboard배열을 1과0으로 표현해줌 디버깅용
{
	int i = 0, h = 0;
	//gotoxy(GAMEBOARDSTARTX+2,GAMEBOARDSTARTY+1);
	gotoxy(0, 23);
	for(i = 0; i < VSIZE; i++)
	{
		for(h = 0; h < HSIZE; h++)
		{
			cout <<setw(2)<< gameboard[i][h];
		}
		//gotoxy(GAMEBOARDSTARTX+2, GAMEBOARDSTARTY+1+i);
		cout << endl;
	}
}

void test_debug(int (*test)[4])		//test배열을 1과0으로 표현해줌 디버깅용
{
	int i = 0, h = 0;
	for(i = 0; i < 4; i++)
	{
		for(h = 0; h < 4; h ++)
		{
			cout << test[i][h] << ", ";
		}
		cout << endl;
	}
}

int scann(int (*gameboard)[HSIZE], int x, int y, int (*test)[4])
{
	int i = 0, h = 0, ix =x, num = 0, yhigh = BSIZE;
	if(y == VSIZE-BSIZE+1) yhigh = 3;
	else if(y == VSIZE-BSIZE+2) yhigh = 2;
	for(i = 0; i < yhigh; i++)
	{
		for(h = 0; h < BSIZE; h++)
		{
			if(test[i][h] + gameboard[y][x] >= 2) num++;
			x++;
		}
		y++;
		x = ix;
	}
	if(num == 0) return SAFE;
	else return NOTSAFE;
}

void blocktotest(int (*test)[4], int& brotation)		//현재공간에 블록을 넣어준다
{
	int i = 0, h = 0;
	for(i = 0; i < BSIZE; i++)
	{
		for(h = 0; h < BSIZE; h++)
		{
			test[i][h] = block[brotation][i][h];
		}
	}
}

void printblock(int x, int y, const int& brotation)		//좌표를 활용해 현재블록 출력
{
	int i = 0, h = 0, ix = x;
	for(i = 0; i < BSIZE; i++)
	{
		for(h = 0; h < BSIZE; h++)
		{
			gotoxy(GAMEBOARDSTARTX+(2*x), GAMEBOARDSTARTY+y);
			if(block[brotation][i][h] == 1) cout << "■";
			x++;
		}
		y++;
		x = ix;
	}
}

void eraseblock(int x, int y, int& brotation)		//좌표를 활용해 현재블록 삭제
{
	int i = 0, h = 0, ix = x;
	for(i = 0; i < BSIZE; i++)
	{
		for(h = 0; h < BSIZE; h++)
		{
			gotoxy(GAMEBOARDSTARTX+(2*x), GAMEBOARDSTARTY+y);
			if(block[brotation][i][h] == 1) cout << "  ";
			x++;
		}
		y++;
		x = ix;
	}
}

void carve(int (*test)[BSIZE], int x, int y, int (*gameboard)[HSIZE])
{
	int yhigh=BSIZE,i=0,h=0,ix = x;
	for(i=0;i<yhigh;i++)
	{
		for(h=0;h<BSIZE;h++)
		{
			if(test[i][h] == 1)
			{
				gameboard[y][x] = 1;
			}
			x++;
		}
		y++;
		x = ix;
	}
}

void checkoverlap(int (*test)[BSIZE], int& x, int y, int (*gameboard)[HSIZE])
{
	int yhigh = BSIZE,i,h,ix=x, left = 0, right = 0;
	if(y == VSIZE-BSIZE+1) yhigh = 3;
	else if(y == VSIZE-BSIZE+2) yhigh = 2;
	/*for(i=0;i<yhigh;i++)
	{
		for(h=0;h<BSIZE;h++)
		{
			if(test[i][h]+gameboard[y][ix] == 2)
			{
				if(h==1) x+=3;
				else if(h==0) x+=2;
				else if(h==2) x-=2;
				else if(h==3) x-=1;
				i = BSIZE;
				break;
			}
			ix++;
		}
		ix = x;
	}*/
	int** p;
	p = new int *[BSIZE];
	for(i = 0; i<BSIZE; i++)
	{
		p[i] = new int[BSIZE];
	}
	for(i=0;i<yhigh; i++)
	{
		for(h=0; h<BSIZE; h++)
		{
			p[i][h] = test[i][h] + gameboard[y][ix];
			ix++;
			//cout << p[i][h];
		}
		y++;
		ix = x;
		//cout << endl;
	}
	//cout << endl << x;
	for(h=0;h<BSIZE;h++)
	{
		for(i=0;i<yhigh;i++)
		{
			if(p[i][h] == 2)
			{
				if(h < 2) left++;
				else if(h >= 2) right++;
			}
		}
	}
	if(left >= 1 && right >= 1) {}
	else if(left == 2) x+=2;
	else if(right == 2) x-=2;
	else if(left == 1) x+=1;
	else if(right == 1) x-=1;
	
	for(i = 0; i<BSIZE; i++)
	{
		delete[]p[i];
	}
	delete[] p;
}

void checkline(int (*gameboard)[HSIZE])
{
	int line = 0,i,h,pt,a,b;
	int **p;
	for(i=VSIZE-2;i>0;i--)
	{
		for(h=1;h<HSIZE-1;h++)
		{
			if(gameboard[i][h] == 1) line++;	
		}
		if(line == HSIZE-2)
		{
			p = new int*[i-1];
			for(pt = 0; pt < i-1; pt++)
			{
				p[pt] = new int[HSIZE-2];
			}
			for(a=0;a<i-1;a++)
			{
				for(b=0;b<HSIZE-2;b++)
				{
					p[a][b] = gameboard[a+1][b+1];
				}
			}
			for(a=1;a<=i;a++)
			{
				for(b=1;b<HSIZE-1;b++)
				{
					gameboard[a][b] = 0;
				}
			}
			for(a=0;a<i-1;a++)
			{
				for(b=0;b<HSIZE-2;b++)
				{
					gameboard[a+2][b+1] = p[a][b];
				}
			}
			for(a=0;a<i-1;a++)
			{
				delete[]p[a];
			}
			delete[]p;
			i=VSIZE-1;
			line = 0;
		}
		else if(line == 0)
		{
			i = 0;
			break;
		}
		else
		{
			line = 0;
		}
	}				
}

void nextblocktotest(int (*nextblock)[BSIZE], int (*test)[BSIZE])
{
	int i = 0, h = 0;
	for(i = 0; i < BSIZE; i++)
	{
		for(h = 0; h < BSIZE; h++)
		{
			test[i][h] = nextblock[i][h];
		}
	}
}

void brotationplusrange(int& brotation)		//이것역시 블록추가시 수정하기(범위추가해주기)
{
	if(brotation >=0 && brotation <= 3)
	{
		brotation++;
		if(brotation == 4) brotation = 0;
	}
	else if(brotation >=4 && brotation <= 7)
	{
		brotation++;
		if(brotation == 8) brotation = 4;
	}
	else if(brotation >=8 && brotation <= 11)
	{
		brotation++;
		if(brotation == 12) brotation = 8;
	}
	else if(brotation >=12 && brotation <=15)
	{
		brotation++;
		if(brotation == 16) brotation = 12;
	}
	else if(brotation >=16 && brotation <= 19)
	{
		brotation++;
		if(brotation == 20) brotation = 16;
	}
	else if(brotation >=20 && brotation <= 23)
	{
		brotation++;
		if(brotation == 24) brotation = 20;
	}
	else if(brotation >=24 && brotation <= 27)
	{
		brotation++;
		if(brotation == 28) brotation = 24;
	}
}

void brotationminusrange(int& brotation)		//이것도 블록추가시 범위추가하기
{
	if(brotation >=0 && brotation <= 3)
	{
		brotation--;
		if(brotation == -1) brotation = 3;
	}
	else if(brotation >=4 && brotation <= 7)
	{
		brotation--;
		if(brotation == 3) brotation = 7;
	}
	else if(brotation >=8 && brotation <= 11)
	{
		brotation--;
		if(brotation == 7) brotation = 11;
	}
	else if(brotation >=12 && brotation <=15)
	{
		brotation--;
		if(brotation == 11) brotation = 15;
	}
	else if(brotation >=16 && brotation <= 19)
	{
		brotation--;
		if(brotation == 15) brotation = 19;
	}
	else if(brotation >=20 && brotation <= 23)
	{
		brotation--;
		if(brotation == 19) brotation = 23;
	}
	else if(brotation >=24 && brotation <= 27)
	{
		brotation--;
		if(brotation == 23) brotation = 27;
	}
}

void checkend(int (*gameboard)[HSIZE])
{
	int i;
	for(i=1;i<HSIZE-1;i++)
	{
		if(gameboard[2][i] == 1)
			exit(1);
	}
}

int main()
{
	int gameboard[VSIZE][HSIZE] = {0,};
	int test[BSIZE][BSIZE] = {0,};
	int nextblock[BSIZE][BSIZE] = {0,};
	int nextbrotation = 0;

	int x = 4, y = 0;
	int h = 4;
	int score = -10;
	int ch = 0;			//for getting GameAction(1,2,3,4)
	int gameAction = 0;	//for keyvalue(<,>,v)
	int safe = 0;
	int brotation = 0;
	srand(time(NULL));
	/***************************set initial setting***************************/
	setdisplay(gameboard);
	scoreprint(score);
	nextbrotation = choose(nextblock);
	blocktotest(test, brotation);
	/***************************set initial setting***************************/

	/*****************************for no cursor*******************************/
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	/*****************************for no cursor*******************************/

	while(ch != GAME_QUIT)
	{
		safe = scann(gameboard, x, y+1, test);
		if(safe == SAFE) y++;
		else if(safe == NOTSAFE)
		{
			checkend(gameboard);
			carve(test, x, y, gameboard);
			checkline(gameboard);
			boardprint(gameboard);
			x = 4;
			y = 0;
			scoreprint(score);
			nextblocktotest(nextblock, test);
			brotation = nextbrotation;
			nextbrotation = choose(nextblock);
			continue;
		}
		printblock(x,y,brotation);
		Sleep(30);
		if(_kbhit())
		{
			ch = getGameAction(gameAction); 
			if(ch == MOVE_LEFT)
			{
				safe = scann(gameboard, x-1, y, test);
				if(safe == SAFE)
				{
					eraseblock(x,y,brotation);
					x--;
					printblock(x,y,brotation);
				}
			}
			else if(ch == MOVE_RIGHT)
			{
				safe = scann(gameboard, x+1, y, test);
				if(safe == SAFE) 
				{
					eraseblock(x,y,brotation);
					x++;
					printblock(x,y,brotation);
				}
			}
			else if(ch == MOVE_DOWN)
			{
				Sleep(FAST);
				eraseblock(x,y,brotation);
				continue;
			}
			else if(ch == ROTATION)
			{
				eraseblock(x,y,brotation);
				brotationplusrange(brotation);
				blocktotest(test, brotation);
				checkoverlap(test, x, y, gameboard);
				safe = scann(gameboard, x, y, test);
				if(safe==NOTSAFE)
				{
					checkoverlap(test, x, y, gameboard);
					brotationminusrange(brotation);
					blocktotest(test, brotation);
				}
			}
			else if(ch == SKIP_DOWN)
			{
				while(safe != NOTSAFE)
				{
					safe = scann(gameboard, x, y+1, test);
					if(safe == SAFE) y++;
				}
				checkend(gameboard);
				carve(test, x, y, gameboard);
				checkline(gameboard);
				boardprint(gameboard);
				x = 4;
				y = 0;
				scoreprint(score);
				nextblocktotest(nextblock, test);
				brotation = nextbrotation;
				nextbrotation = choose(nextblock);
				continue;
			}
		}
		Sleep(NORMAL);
		eraseblock(x,y,brotation);
	}
}