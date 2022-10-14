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
			if (board[i] == j) printf("��");
			else if ((i+j) % 2 == 0) printf("��");
			else printf("��");
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

void nqueen(int cdx) // 0~n-1����� ���������� cdx�࿡ ���� �����ڸ��� Ž���Ѵ�. ��� ���� ��ġ �� �����Ѵ�.
{
	if (cdx == n)
	{
		printBoard();
		count++;
		return;
	}

	for (int i = 0; i < n; i++)
	{
		board[cdx] = i; // cdx�� i���� ���� ���ƺ���.
		if(promising(cdx)) // �����ϴ� �ǴܵǸ�
			nqueen(cdx + 1); // ���� �࿡ ���� ���� �ڸ��� ��󺻴�.
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