#define MAX_SIZE 100

#include <stdio.h>
#include <stdlib.h>

double sum (double list [], int n)
{
	int i ;
	double tempsum = 0.0 ; //sum의 결과값을 저장할 tempsum

	for (i = 0 ; i < n ; i++) {
		tempsum += list[i] ; // tempsum에 list에 있는 인덱스 값들 하나씩 더함.
		list[i] = 0.0 ;
	}
	return tempsum ;
}

//double input[MAX_SIZE] ;

int main ()
{
	//double input[MAX_SIZE] ;
	double * input ;
	input = (double *) malloc(MAX_SIZE * sizeof(int)) ; // input을 double 포인터로 <최대 크기(MAX_SIZE)* int> 크기만큼 할당

	int i ;
	for (i = 0 ; i < MAX_SIZE; i++) { // MAX_SIZE만큼 input[]리스트에 i번째 인덱스에 i 넣기
		input[i] = (double) i ; //그러면 input[]리스트에는 double형의 숫자들이 순서대로 채워져있음.
	}

	double ans = sum(input, MAX_SIZE) ; //ans에 input과 max_size를 더한 값 출력 
	printf("%lf\n", ans) ;
	printf("%f\n", input[1]) ;

	free(input) ;

	return EXIT_SUCCESS ;
}
