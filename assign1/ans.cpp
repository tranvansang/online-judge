#include <stdio.h>

using namespace std;

#define nmax 300

int a[nmax + 1][nmax + 1], res, n, amin, amax, list[nmax + 1], nlist, match[nmax + 1];
bool mark[nmax + 1], found;


void enter()
{
	scanf("%d", &n);
	amin = 1000000000;
	amax = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
		{
			scanf("%d", &a[i][j]);
			if (a[i][j] > amax)
				amax = a[i][j];
			if (a[i][j] < amin)
				amin = a[i][j];
		};
}

void visit(int x, int max)
{
	for(int i = 1; i <=n ;i++)
		if((a[x][i] <= max) && (!mark[i]))
		{
			mark[i] = true;
			if (match[i] == 0)
				found = true;
			else
				visit(match[i], max);
			if (found)
			{
				match[i] = x;
				return;
			};
		};
}

bool possible(int x)
{
	for(int i = 1;i <= n; i++)
	{
		mark[i] = false;
		match[i] = 0;
	};
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if ((a[i][j] <= x) && (match[j] == 0))
			{
				match[j] = i;
				mark[i] = true;
				break;
			};

	nlist = 0;
	for(int i = 1; i <= n; i++)
		if(!mark[i])
			list[++nlist] = i;

	int old;
	do
	{
		old = nlist;
		for(int i = 1; i <= n; i++)
			mark[i] = false;
		for(int i = nlist; i >= 1; i--)
		{
			found = false;
			visit(list[i], x);
			if (found)
				list[i] = list[nlist--];
		};
	} while (old != nlist);
	return (nlist == 0);
}

void solve()
{
	int l = amin, h = amax, mid;
	while (l <= h) //tim so x thoa man possible(x) && !possible(x - 1)
		//l - 1 < x <= h + 1
	{
		mid = (h + l) / 2;
		if (possible(mid))
			h = mid - 1;
		else
			l = mid + 1;
	};
	printf("%d", l);
}

int main()
{
	enter();
	solve();
	return 0;
}
