// myRand.cpp : Defines the entry point for the console application.
//


#include <stdio.h>		//for atoi()
#include <stdlib.h>
#include <time.h>		//for time()

#if 0	//windows
#include "stdafx.h"

#include <windows.h>	//for Sleep()
#include <Shlwapi.h>	//for PathFindFileName()
#pragma comment(lib,"Shlwapi.LIB")	//区分大小写?仅首字母大写?

#else	//linux
#include <string.h>
#endif


int main(int argc, char* argv[])
{
	int ibeg;
	int iend;
	int i;
	int irand;
	char strbin[256]="";
	char* lpszTitle;
	
	strcpy(strbin,argv[0]);

	if (argc == 1)
	{
		printf("Usage:\n");

		//lpszTitle = PathFindFileName(argv[0]);
		//StrTrim(lpszTitle,".exe");
		printf("\t %s\n",strbin);
		printf("\t\t used to random integer\n");

		printf("\t myrand 50\n");
		printf("\t\t generate 10 rand int 1~50\n");

		printf("\t myrand 50 100\n");
		printf("\t\t generate 10 rand int 50~100\n");
	}

	//zz// 不加 srand(),每次产生的数都是确定的...
	if (argc == 2)
	{
		ibeg = 0;
		iend = atoi(argv[1]);
		
		if (iend>0)
		{
			srand((int)time(0));
			printf("Generate 10 random int: 1~%s!\n\t",argv[1]);
			for (i=0;i<10;i++)
			{
				printf("%4d ",1+rand()%iend);
			}

			//################################################################//
			printf("\nGenerate 10 random int: 0~%d!\n\t",iend-1);
			for (i=0;i<10;i++)
			{
				//zz//windows	irand = 1 + iend*rand()/(RAND_MAX+1);
				//zz//linux	
				irand = 1 + (int)((float)iend*rand()/(RAND_MAX+1.0));
				printf("%4d ",irand);
			}
		}

	}

	if (argc == 3)
	{
		ibeg = atoi(argv[1]);
		iend = atoi(argv[2]);
		
		printf("Generate 10 random int: %s~%s!\n\t",argv[1],argv[2]);
		
		if (ibeg>=0 &&iend>0)
		{
			srand((unsigned)time(NULL));
			for (i=0;i<10;i++)
			{
				printf("%4d ",1+ibeg+rand()%(iend-ibeg));
			}

			//#############################################################//
			printf("\nGenerate 10 random int: %d~%d!\n\t",ibeg,iend-1);
			for (i=0;i<10;i++)
			{
				irand = ibeg + (int)((float)(iend-ibeg)*rand()/(RAND_MAX+1.0));
				printf("%4d ",irand);
			}

			printf("\nGenerate 10 random int: %d~%d!\n\t",ibeg+1,iend);
			for (i=0;i<10;i++)
			{
				irand = 1 + ibeg + (int)((float)(iend-ibeg)*rand()/(RAND_MAX+1.0));
				printf("%4d ",irand);
			}

			printf("\nGenerate 10 random int: %d~%d!\n\t",ibeg,iend);
			for (i=0;i<10;i++)
			{
				irand = ibeg + (int)((float)(iend+1-ibeg)*rand()/(RAND_MAX+1.0));
				printf("%4d ",irand);
			}
		}
		printf("\n");
	}
	return 0;
}

