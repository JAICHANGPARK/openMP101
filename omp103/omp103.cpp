// ompTest102.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <omp.h>
#include <math.h>

void InputData(float* Data, int Size)
{

	int i = 0;
	for (i = 0; i < Size; i++)
	{
		Data[i] = i;
	}
}

void PrintData(float* Data){

	printf("%f,%f,%f,%f \n", Data[0], Data[1], Data[2], Data[3]);

}

void CalsSQRT(float* Data, int Size){

#pragma omp parallel 
	{
#pragma omp for
		for (int i = 0; i < Size; i++)
		{
			Data[i] = sqrt(Data[i]);
		}
	}
}

void CalcLog(float* Data, int Size){

	for (int i = 0; i < Size; i++)
	{
		Data[i] = log(Data[i]);
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	const int max = 10000000;
	int i = 0;
	float* Data1 = new float[max];
	float* Data2 = new float[max]; // 메모리 동적 할당 

	InputData(Data1, max);
	InputData(Data2, max);

#pragma omp parallel
	{
#pragma omp sections
		{
#pragma omp section
			CalsSQRT(Data1, max);
#pragma omp section
			CalcLog(Data2, max);
		}
	}
	//CalsSQRT(Data1,max);
	//CalcLog(Data2,max);
	PrintData(Data1);
	PrintData(Data2);
	delete Data1;
	delete Data2;
	return 0;
}


