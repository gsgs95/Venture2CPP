#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int n;
int count = 0;
int board[15];

void printBoard()
{
	printf("\n--------------------\n\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (board[i] == j) printf("★");
			else if ((i+j) % 2 == 0) printf("■");
			else printf("□");
		}
		printf("\n");
	}
}

bool promising(int cdx)
{
	for (int i = 0; i < cdx; i++)
	{
		if (cdx - i == abs(board[cdx]-board[i]) || board[cdx] == board[i])
		{
			return false;
		}
	}
	return true;
}

void nqueen(int cdx) // 0~n-1행까지 순차적으로 cdx행에 퀸을 놓을자리를 탐색한다. 모든 퀸을 배치 후 종료한다.
{
	if (cdx == n)
	{
		printBoard();
		count++;
		return;
	}

	for (int i = 0; i < n; i++)
	{
		board[cdx] = i; // cdx행 i열에 퀸을 놓아본다.
		if(promising(cdx)) // 유망하다 판단되면
			nqueen(cdx + 1); // 다음 행에 퀸을 놓을 자리를 골라본다.
	}
}

int main()
{
	scanf("%d", &n);

	nqueen(0);
	printf("\n--------------------\n\n");

	printf("%d", count);

	return 0;
}