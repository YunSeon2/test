#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<stdlib.h>

#define SIZE 4
#define TRUE 1
#define FALSE 0

void DrawMap(int* score, int board[][4])
{
	system("cls");
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j] == 0)
				printf("    .");
			else
				printf("%5d", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("Score: %d", *score);
}

void NewNum(int board[][4])
{
	int x, y;
	int num;
	int count = 0;

	if (rand() % 100 < 80)
		num = 2;
	else
		num = 4;

	x = rand() % SIZE;
	y = rand() % SIZE;

	if (board[y][x] == 0)
		board[y][x] = num;
	else
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
				if (board[i][j] == 0)
				{
					board[i][j] = num;
					count++;
					break;
				}
			if (count != 0)
				break;
		}
	}
}
int CheckGameOver(int board[][4])
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (board[i][j] == 2048)
			{
				printf("\nGame Clear!\n");
				system("pause");
				return FALSE;
			}
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (board[i][j] == 0)
				return TRUE;
	for (int i = 0; i < SIZE - 1; i++)
		for (int j = 0; j < SIZE - 1; j++)
			if (board[i][j] == board[i + 1][j] || board[i][j] == board[i][j + 1])
				return TRUE;
	for (int i = 0; i < SIZE - 1; i++)
		if (board[i][SIZE - 1] == board[i + 1][SIZE - 1])
			return TRUE;
	for (int j = 0; j < SIZE - 1; j++)
		if (board[SIZE - 1][j] == board[SIZE - 1][j + 1])
			return TRUE;

	printf("\nGame Over!\n");
	system("pause");
	return FALSE;
}
void PlusNumWidth(int board[][4], int* score, int way, int startx)
{
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = startx; x >= 0 && x < SIZE; x += way)
		{
			if (board[y][x] == 0)
				continue;
			for (int r = x + way; r >= 0 && r < SIZE; r += way)
			{
				if (board[y][r] == board[y][x])
				{
					board[y][x] += board[y][r];
					board[y][r] = 0;
					*score += board[y][x];
					break;
				}
				else if (board[y][r] != 0)
					break;
			}
		}
	}
}
void PlusNumLength(int board[][4], int* score, int way, int starty)
{
	for (int x = 0; x < SIZE; x++)
	{
		for (int y = starty; y >= 0 && y < SIZE; y += way)
		{
			if (board[y][x] == 0)
				continue;
			for (int r = y + way; r >= 0 && r < SIZE; r += way)
			{
				if (board[y][x] == board[r][x])
				{
					board[y][x] += board[r][x];
					board[r][x] = 0;
					*score += board[y][x];
					break;
				}
				else if (board[r][x] != 0)
					break;
			}
		}
	}
}
void MoveWidth(int board[][4], int way, int startx)
{
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = startx; x >= 0 && x < SIZE; x += way)
		{
			for (int r = x; r >= 0 && r < SIZE; r -= way)
			{
				if (board[y][r] == 0) //숫자가 0이라서 처리할 게 없음
					break;
				//내가 이동할 곳에 숫자가 있으면서 나랑 같지 않으면 이동 불가
				if (board[y][r - way] != 0 && board[y][r - way] != board[y][r])
					break;
				if (r == startx)
					continue;
				if (board[y][r - way] == 0) //옆이 비어있으면 숫자를 당김
				{
					board[y][r - way] = board[y][r];
					board[y][r] = 0;
				}
			}
		}
	}
}
void MoveLength(int board[][4], int way, int starty)
{
	for (int x = 0; x < SIZE; x++)
	{
		for (int y = starty; y >= 0 && y < SIZE; y += way)
		{
			for (int r = y; r >= 0 && r < SIZE; r -= way)
			{
				if (board[r][x] == 0)
					break;
				if (board[r - way][x] != 0 && board[r - way][x] != board[r][x])
					break;
				if (r == starty)
					continue;
				if (board[r - way][x] == 0)
				{
					board[r - way][x] = board[r][x];
					board[r][x] = 0;
				}
			}
		}
	}
}
void main()
{
	int board[SIZE][SIZE] = {
		{ 4,2,2,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 } };

	char key;
	int score = 0;

	srand((unsigned)time(NULL));
	NewNum(board);
	NewNum(board);
	DrawMap(&score, board);

	while (CheckGameOver(board))
	{
		key = _getch();
		switch (key)
		{
		case 'a':
			PlusNumWidth(board, &score, -1, SIZE - 1);
			MoveWidth(board, 1, 0);
			break;

		case 'd':
			PlusNumWidth(board, &score, 1, 0);
			MoveWidth(board, -1, SIZE - 1);
			break;

		case 'w':
			PlusNumLength(board, &score, -1, SIZE - 1);
			MoveLength(board, 1, 0);
			break;

		case 's':
			PlusNumLength(board, &score, 1, 0);
			MoveLength(board, -1, SIZE - 1);
			break;
		}
		if (key == 'a' || key == 'd' || key == 'w' || key == 's')
		{
			NewNum(board);
			DrawMap(&score, board);
			CheckGameOver(board);
		}
	}
}