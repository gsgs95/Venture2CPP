#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int count = 0; // �䱸����
int n; // ��ǲ, 1~15
// board[y] == x; ==> x,y��ġ�� queen ��ġ(�� �࿡ 1�� ���� ���簡��)
int board[15]; // ����

bool promising(int cdx) // ��ȿ�� �˻�
{
	// ���� ���̳� �밢�����̸� �ȵ�
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

	// cdx �� �������� ���� �����ϰ� ������� ����, ã�� �Ϸ�
	if (cdx == n)
	{
		count++; // �ϳ� �ַ�� ã��. ����
		return;
	}

	for (int i = 0; i < n; i++)
	{
		board[cdx] = i; // cdx��° ��, i��° ���� queen�� ���ƺ���.
		// ���� �� �࿡ �� �Ϳ� ���� �������� �Ǵ��Ѵ�.
		if (promising(cdx))
		{
			nqueen(cdx + 1); // �� ���� �࿡ ���� ���� ���°��� �غ���.
		}
	}
}

int main()
{
	scanf("%d", &n);
	nqueen(0);
	printf("%d", count);
}