#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int count = 0; // 요구조건
int n; // 인풋, 1~15
// board[y] == x; ==> x,y위치에 queen 배치(한 행에 1개 퀸만 존재가능)
int board[15]; // 상태

bool promising(int cdx) // 유효성 검사
{
	// 같은 열이나 대각선상이면 안됨
	for (int i = 0; i < cdx; i++)
	{
		if (board[cdx] == board[i] || cdx - i == abs(board[cdx] - board[i]))
			return false;
	}
	return true;
}


// n-queen algorithm
void nqueen(int cdx)
{

	// cdx 가 마지막행 까지 수행하고 여기까지 오면, 찾기 완료
	if (cdx == n)
	{
		count++; // 하나 솔루션 찾음. 저장
		return;
	}

	for (int i = 0; i < n; i++)
	{
		board[cdx] = i; // cdx번째 행, i번째 열에 queen을 놓아본다.
		// 이후 그 행에 둔 것에 대한 유망성을 판단한다.
		if (promising(cdx))
		{
			nqueen(cdx + 1); // 그 다음 행에 대해 퀸을 놓는것을 해본다.
		}
	}
}

int main()
{
	scanf("%d", &n);
	nqueen(0);
	printf("%d", count);
}