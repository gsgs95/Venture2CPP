#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int n;
int a[1001][3];
int d[1001][3];

int main()
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d %d %d", &a[i][0], &a[i][1], &a[i][2]);
	}
	// d[i][0] = min(d[i-1][1], d[i-1][2]) + a[i][0];
	// d[i][1] = min(d[i-1][0], d[i-1][2]) + a[i][1];
	// d[i][2] = min(d[i-1][1], d[i-1][0]) + a[i][2];


	return 0;
}