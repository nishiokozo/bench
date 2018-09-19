#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<math.h>
#include	<stdint.h>
#include <windows.h>
#include <time.h>

#define	EXP(n)  ((int64_t)(((n)>>52)&0x7ff)-1023)
#define	FRAC(n) ((n)&0xfffffffffffff)

#define	MAX_NUM		10
#define	MAX_ORDER		(MAX_NUM-1)
	int64_t max_exec;

bool flgEnd = false;

	int		calcparam;
	double	vals[MAX_NUM+10] = {1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0};
	int		num[MAX_NUM];
	int		ord[MAX_ORDER];
	double	max = 0;
	uint64_t	cntExec = 0;

int	thread_id;
struct ID
{
	int	a;
	int	b;
	int	c;
};
ID	loop_id;
ID	start_id;
ID	max_id;
uint64_t	cntDump = 1;

//----------------------------------------------------------------------
void dump( int max_num, int p, float val )
//----------------------------------------------------------------------
{
				char	str[256] = "";
				for ( int j = 0 ; j < max_num ; j++ )
				{
					sprintf( str, "%s%.1f ", str, vals[num[j]] );
				}
					sprintf( str, ":" );

				for ( int j = 0 ; j < max_num-1 ; j++ )
				{
					switch ((p>>(j*2))&3)
					{
					case 0 :sprintf( str, "%s %d(+)", str, ord[j] );break;
					case 1 :sprintf( str, "%s %d(-)", str, ord[j] );break;
					case 2 :sprintf( str, "%s %d(*)", str, ord[j] );break;
					case 3 :sprintf( str, "%s %d(/)", str, ord[j] );break;
					}
				}
				sprintf( str, " " );

				sprintf( str, "%s = %f", str, val );	
				sprintf( str, "%s : id=%d:%d-%d-%d ", str, thread_id, loop_id.a, loop_id.b, loop_id.c );	
				printf("%s\n", str );

}

//----------------------------------------------------------------------
void	exec( int p, int max_num )
//----------------------------------------------------------------------
{
	cntExec++;

	double	valt[max_num];

	for ( int i = 0 ; i < max_num ; i++ )	valt[i] = vals[num[i]];

	bool	flg[max_num-1];
	for ( int i = 0 ; i < max_num-1 ; i++ ) flg[i] = false;


	for( int j = 0 ; j < max_num-1 ; j++ )
	{
		int	c = ord[j];
		int	d = c+1;

		while( flg[c] ) c--;

		double x = valt[c];
		double y = valt[d]; 
		flg[d] = true;

		int	ptn = (p>>(j*2))&3;

			
#if 0
		union
		{
			float	f;
			int		b;
		};
		 f = y;

			printf("xy %f %20f : %x \n", x, y, b);
			printf("s   %x \n",  b>>31);
			printf("exp %d \n",  (b>>23)&0xff);
			printf("fra %d \n",  b&0x3fffff);

		if ( b&0xefffff == 0 )
#else
		union
		{
			double	val;
			int64_t	b;
		};
		val = y;
	//	printf("xy %f %f exp=%d \n", x, y, EXP(b));
		if ( EXP(b) < -30 ) 
#endif
		{
			union
			{
				double	a;
				int	b[2];
			};
			a = y;
			valt[0] = -0e-1023;
			break;
		}

		switch (ptn)
		{
		case 0 :valt[c] = x + y;break;
		case 1 :valt[c] = x - y;break;
		case 2 :valt[c] = x * y;break;
		case 3 :valt[c] = x / y;break;
		}
	}

	if ( valt[0] > max ) 
	{
		max = valt[0];

//	printf("cntLoop %llu %llu\n", cntLoop1, cntLoop2 );

		dump( max_num, p, valt[0]  );
	}

}
//----------------------------------------------------------------------
void	powloop2(int n, int m, int tbl[], int lvl )
//----------------------------------------------------------------------
{
	m--;
	for ( int i = 0 ; i < n ; i++ )
	{
		int	j;
		for ( j = 0 ; j < lvl ; j++ )
		{
			if( tbl[j] == i ) break;
		}
		if ( j < lvl ) continue;

		tbl[lvl] = i;
		if ( m > 0 ) powloop2( n, m, tbl, lvl+1 );
		else
		{
			loop_id.b++;
			if ( loop_id.b < start_id.b ) continue;

			for( int p = 0 ; p < calcparam ; p++ )
			{
				loop_id.c = p;
				if ( loop_id.c < start_id.c ) continue;

				if ( cntExec < cntDump ) exec( p, n+1 );
			}
		}
		
	}
}

//----------------------------------------------------------------------
void	powloop1(int n, int m, int tbl[], int lvl )
//----------------------------------------------------------------------
{
	m--;
	for ( int i = 0 ; i < n ; i++ )
	{
		int	j;
		for ( j = 0 ; j < lvl ; j++ )
		{
			if( tbl[j] == i ) break;
		}
		if ( j < lvl ) continue;

		tbl[lvl] = i;
		if ( m > 0 ) powloop1( n, m, tbl, lvl+1 );
		else
		{
			loop_id.a++;
			if ( loop_id.a < start_id.a ) continue;
		
			for ( int i = 0 ; i < n-1 ; i++ ) ord[i] = -1;
			powloop2( n-1, n-1, ord, 0 );

		}
		
	}
}

//----------------------------------------------------------------------
void func(int *pNum )
//----------------------------------------------------------------------
{

	int	max_num = 10;

	calcparam = pow(4,max_num-1);

	thread_id = *pNum;

	start_id.a = 0;
	start_id.b = 0;
	start_id.c = 0;

	loop_id.a = 0;
	loop_id.b = 0;
	loop_id.c = 0;

	max_id.a = 1;
	max_id.b = 1;
	max_id.c = 1;


	max_exec = calcparam;
	for ( int i = max_num ; i > 0 ; i-- )		max_exec = max_exec * i;
	for ( int i = max_num-1 ; i > 0 ; i-- )		max_exec = max_exec * i;
	printf("max_exec = %llu\n", max_exec );	

	max_id.c = calcparam;
	for ( int i = max_num ; i > 0 ; i-- )		max_id.a = max_id.a * i;
	for ( int i = max_num-1 ; i > 0 ; i-- )		max_id.b = max_id.b * i;
	printf("max_id = %d %d %d\n", max_id.a, max_id.b, max_id.c );	

	cntDump = max_exec;
#if 0
	start_id.a = 4;
	start_id.b = 418;
	start_id.c = 900;
	cntDump = 1;
#endif


	for ( int i = 0 ; i < max_num ; i++ ) num[i] = -1;

	powloop1( max_num, max_num, num, 0 );

	printf("last max=%f cntExec = %llu\n", max, cntExec );	

	flgEnd = true;
}
//----------------------------------------------------------------------
int	main()
//----------------------------------------------------------------------
{

	#define	MAX_THREAD	16

	HANDLE tblHandle[MAX_THREAD];
//	int	tbl[MAX_THREAD+10] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

	for ( int i = 0 ; i < MAX_THREAD ; i++ )
	{
//	   tblHandle[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) func, &tbl[i], 0, NULL);
	   tblHandle[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) func, i, 0, NULL);
	}

//	WaitForMultipleObjects( MAX_THREAD, tblHandle, true, INFINITE );

	int	cntTime=0;
	while(flgEnd==false)
	{
		printf("main %d:%d-%d-%d:%d\n",thread_id,loop_id.a,loop_id.b,loop_id.c, cntTime++);
//		printf("%s\n",time() );

		Sleep(6*1000);
	}




	for ( int i = 0 ; i < MAX_THREAD ; i++ )
	{
		CloseHandle(tblHandle[i])   ;
	}


	return	0;
}

