#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef 
	struct {
		int exp ; // 지수 
		double coef ; //계수 
	} 
	term_t ;

typedef 
	struct {
		int degree ; // 다항식의 차수
		int n_terms ; // 다항식의 개수
		term_t * terms ; // 항들의 배열 ex)2x+1 = (지수,계수) (1,2),(0,1) 
	} 
	poly_t ;

poly_t * poly_zero () // 새로운 다항식 생성, 초기화 상태로 반환
{
	poly_t * p = (poly_t *) malloc(sizeof(poly_t)) ; 
	// malloc(sizeof(poly_t)) - > poly_t 구조체의 크기만큼 메모리 동적할당.
		//(poly_t *) ->malloc은 void*(void 포인터)를 return한다. 근데 (poly_t *)로 캐스팅해서 
		// ->malloc이 반환한 메모리 주소를 p라는 포인터 변수에 할당한다는 뜻 
		// ->즉, p는 동적으로 할당된 poly_t 구조체를 가리키게 된다.
	
	p->degree = 0 ;
	p->n_terms = 0 ;
	p->terms = NULL ;
	return p ; 
}

int poly_degree (poly_t * p) // 주어진 다항식의 차수를 반환한다. 
{
	return p->degree ;
	// -> 화살표는 .(점)과 같은 의미를 갖는데, 화살표는 p가 구조체를 가리키는 포인터인 경우 사용.
	// .(점)은 p가 구조체 변수일때 사용
}

double poly_coef (poly_t * p, int exp) // 주어진 다항식 특정 "지수의 계수" 반환
{
	if (exp < 0) // 만약 지수가 음수라면, 항이 존재하지 않으므로 0.0 반환
		return 0.0 ;
	if (p->degree < exp) //만약 지수가 다항식의 최고 차수보다 크다면, 지수의 항이 존재하지 않으므로 0.0반환
		return 0.0 ;

	int i ; 
	for (i = 0 ; i < p->n_terms ; i++) { // i< p->n_terms 될 때 까지 순회
		if ((p->terms[i]).exp == exp) { // 만약 검사중인 지수와, 파라미터로 넘어온 지수가 같으면
			return (p->terms[i]).coef ; // 그 지수의 계수를 반환
		}         
	}                                                                  
	return 0.0 ;                                                                                                                                                                                                                  
}	                                                           
                                                                           
poly_t * poly_attach (poly_t * p, double coef, int exp) // 새로운 항 추가 (포인터, 추가할 항의 계수, 추가할 항의 지수)
{
	if (exp < 0) // 만약 지수가 음수면 항 추가 x -> NULL
		return NULL ;
	if (coef == 0.0) // 만약 계수가 0이면 항 추가 x -> NULL 
		return NULL ;
	if (poly_coef(p, exp) != 0.0) // 만약 계수가 0이 아니라면 (이미 존재하는 항이라면), 중복되므로 NULL
		return NULL ;

	if (p->degree < exp) { // 만약 추가하려는 항의 지수가 현재 다항식의 최고차항보다 크면 
		p->degree = exp ; // 최고차항 업데이트
	}
	p->terms = realloc(p->terms, sizeof(term_t) * (p->n_terms + 1)) ; // 항 하나를 추가했으므로 메모리 재할당.
	// realloc으로 새로운 메모리 주소를 할당하면, 현재 포인터는 새로운 메모리 주소를 가리킴
	(p->terms[p->n_terms]).coef = coef ; // 그 새로운 주소에 지수와 계수를 집어넣음. 
	(p->terms[p->n_terms]).exp = exp ;
	p->n_terms += 1 ; // 이제 마지막으로 다항식의 항의 개수를 증가시키는 작업이 끝났으므로 항의 개수 카운트도+1 해줌. 

	return p ;
}

poly_t * poly_remove (poly_t * p, int exp) //주어진 지수에 해당하는 항을 제거 후 변경된 다항식 반환.
{
	if (exp < 0) // 지수가 음수 -> NULL
		return NULL ;
	if (p->degree < exp) // 최고차항보다 지수가 큰 경우 -> 없는 항이므로 NULL
		return NULL ;
	if (poly_coef(p, exp) == 0.0) // 계수가 0인 경우 -> 없는 항이므로 NULL
		return NULL ;

	int i = 0 ;
	while (p->terms[i].exp != exp) { // 해당 지수가 나올때까지 반복하고, 해당 항 인덱스 찾기.
		i++ ;
	}
	// assert p->terms[i].exp == exp

	for ( ; i < p->n_terms - 1 ; i++) { // 찾은 항을 제거하기 위해 해당 항 이후의 모든 항을 왼쪽으로 밀어넣기. 
		p->terms[i] = p->terms[i + 1] ;
	}
	p->terms = realloc(p->terms, (p->n_terms - 1) * sizeof(term_t)) ; // 항 하나가 제거 되었으므로, (n_terms-1)만큼의 메모리로 재할당
	p->n_terms -= 1 ; //항을 하나 제거했으므로, 카운트도 -1

	int j ; 
	p->degree = 0 ; //제거된 항이 최고차항이었을 수도 있으므로, 최고차항 다시 계산을 위해 degree= 0으로 초기값 세팅
	for (j = 0 ; j < p->n_terms ; j++) { // 모든 항을 순회
		if (p->degree < p->terms[j].exp) { // 
			p->degree = p->terms[j].exp ;
		}
	}

	return p ;
}


void poly_delete (poly_t * p) //다항식과 관련된 메모리 해제  
{
	if (p->terms != NULL) { // 만약 terms가 null이 아닌 경우 -> 메모리가 할당되어 있는 경우
		free(p->terms) ; // 항 하나하나에 대한 메모리를 free
	}
	free(p) ; // 전체적인 부분(구조체 전체)에 대한 메모리 free
}


//homework


poly_t * poly_scale (poly_t * p, double s) // s 값을 각 계수에 곱해서 반환
{
	poly_t *result = poly_zero(); // 새로운 다항식 생성

	int i;
	for (i = 0 ; i < p->n_terms ; i++){// 전체 항 순회 
		if (poly_coef(p, i) != 0.0) // 만약 계수가 0이 아니라면 (이미 존재하는 항이라면)
			p->terms[i].coef*=s;
	}
	return result;
}

poly_t * poly_add (poly_t * p1, poly_t * p2) // 두 다항식 더하기
{
	poly_t *p3 = poly_zero();  
	p3->n_terms = 0;
	p3->degree = (p1->degree > p2->degree) ? p1->degree : p2->degree;
	//만약 p1.degree > p2.degree 이면 p1->degree를 따르고, 아니면 p2->degree를 따름
	p3->terms = (term_t *)malloc(sizeof(term_t) * (p3->degree + 1));
	// 0차까지 생각해서 degre+1 까지 동적할당

	int i;
	for (i=0; i<= p3->degree; i++){ // p3 최고차항까지 각 다항식 순회
		double coef1 = 0.0 , coef2 = 0.0; // 더할 계수 변수 설정

		if(i<= p1->degree){ // 현재 검사하고 있는 지수보다 p1의 최고차항이 더 크다면, 항이 존재할 가능성이 있으므로 검사. 
			for (int j = 0; j< p1->n_terms; j++){ // 첫 번째 다항식 순회
				if (p1->terms[j].exp == i){ // 만약 지수의 값이 검사하고 있는 지수의 값과 같은 경우
					coef1 = p1->terms[j].coef; // coef에 지수 담아놓고 일단 반복 멈추기
					break;
				}
			}
		}

		if(i<=p2->degree){ // 두 번째 다항식 최고차항까지 순회
			for (int j = 0; j< p2->n_terms; j++){ 
				if(p2->terms[j].exp == i){ 
					coef2 = p2->terms[j].coef;
					break;
				}
			}
			double sum = coef1+coef2; // 추출한 계수 더하기
			if(sum!= 0.0){ // 더한 계수의 값이 0이 아니라면
				p3->terms[p3->degree-i].exp=i; // 검사하고 있는 지수 
				p3->terms[p3->degree-i].coef=sum; // 검사 중인 지수의 계수 합한 값
				// 출력은 최고차항 - i로 저장해야 정방향으로 출력된다.  
				p3->n_terms++; // 새로운 다항식 p3의 다항식 개수 한 개 카운트
			}
		}
		
	}
	return p3;
}



poly_t * poly_sub (poly_t * p1, poly_t * p2) // 두 다항식 빼기
{
	 poly_t *p3 = poly_zero();  
	p3->n_terms = 0;
	p3->degree = (p1->degree > p2->degree) ? p1->degree : p2->degree;
	//만약 p1.degree > p2.degree 이면 p1->degree를 따르고, 아니면 p2->degree를 따름
	p3->terms = (term_t *)malloc(sizeof(term_t) * (p3->degree + 1));
	// 0차까지 생각해서 degre+1 까지 동적할당

	int i;
	for (i=0; i<= p3->degree; i++){ // p3 최고차항까지 각 다항식 순회
		double coef1 = 0.0 , coef2 = 0.0; // 더할 계수 변수 설정

		if(i<= p1->degree){ // 현재 검사하고 있는 지수보다 p1의 최고차항이 더 크다면, 항이 존재할 가능성이 있으므로 검사. 
			for (int j = 0; j< p1->n_terms; j++){ // 첫 번째 다항식 순회
				if (p1->terms[j].exp == i){ // 만약 지수의 값이 검사하고 있는 지수의 값과 같은 경우
					coef1 = p1->terms[j].coef; // coef에 지수 담아놓고 일단 반복 멈추기
					break;
				}
			}
		}

		if(i<=p2->degree){ // 두 번째 다항식 최고차항까지 순회
			for (int j = 0; j< p2->n_terms; j++){ 
				if(p2->terms[j].exp == i){ 
					coef2 = p2->terms[j].coef;
					break;
				}
			}
			double sub = coef1-coef2; // 추출한 계수 더하기
			if(sub!= 0.0){ // 더한 계수의 값이 0이 아니라면
				p3->terms[p3->degree-i].exp=i; // 검사하고 있는 지수 
				p3->terms[p3->degree-i].coef=sub; // 검사 중인 지수의 계수 합한 값
				// 출력은 최고차항 - i로 저장해야 정방향으로 출력된다.  
				p3->n_terms++; // 새로운 다항식 p3의 다항식 개수 한 개 카운트
			}
		}
		
	}
	return p3;
}

poly_t * poly_mult (poly_t * p1, poly_t * p2) // 두 다항식 곱하기
{
    poly_t *p3 = poly_zero();

    for (int i = 0; i <= p1->degree; i++) {
        for (int j = 0; j <= p2->degree; j++) {
            double coef1 = p1->terms[i].coef;
            double coef2 = p2->terms[j].coef;
            int exp1 = p1->terms[i].exp;   //지수곱(합)
            int exp2 = p2->terms[j].exp;
            double coef_p3 = coef1 * coef2;  //계수곱
            int exp_p3 = exp1 + exp2;

            // 새로운 항 추가
            int n = 0;
            for (int k = 0; k < p3->n_terms; k++) {
                if (p3->terms[k].exp == exp_p3) {
                    p3->terms[k].coef += coef_p3;
                    n = 1;
                    break;
                }
            }
            if (n == 0) {
                poly_attach(p3, coef_p3, exp_p3);
            }
        }
    }

    return p3; 

}


double poly_eval (poly_t * p, double x) // 주어진 값 x에 대한 다항식 값 계산
{
	double result = 0.0; // 결과값 넣을 곳 세팅

	int i =0;
	for (i=0; i<p->n_terms ; i++){ // 전체 항 순회
		int exp2= p->terms[i].exp; // 검사하는 항의 지수 추출
		double coef2= poly_coef(p,i); // 검사하는 항의 계수 추출 
		
		double value = 1.0; // 곱해지는 수 이므로 "1"로 해야함
		
		int j;
		for(j=0; j<exp2; j++){ // 지수만큼 x를 곱해서 value에 저장
			value *= x;
		}
		
		result += coef2*value; // 결과값 
	}
	return result; 
}



void poly_show (poly_t * p) // 다항식 출력
{
	int i ;
	for (i = 0 ; i < p->n_terms ; i++) {
		printf("%lf", p->terms[i].coef) ;
		if (p->terms[i].exp != 0) {
			printf("x^%d", p->terms[i].exp) ;
		}
		if (i != p->n_terms - 1) {
			if (p->terms[i + 1].coef >= 0.0) {
				printf("+") ;
			}
		}
	}
	printf("\n") ;
}

int main ()
{
	//1.0x^2 + 2.0x+ 1.0 
	poly_t * p = poly_zero() ;
	printf("%d\n", p == poly_attach(p, 1.0, 2)) ;
	printf("%d\n", p == poly_attach(p, 2.0, 1)) ;
	printf("%d\n", p == poly_attach(p, 1.0, 0)) ;
	printf("%d\n", p == poly_attach(p, 2.0, 2)) ;
	poly_show(p) ;

//remove
	printf("%d\n", p == poly_remove(p, 1)) ;

//delete
	poly_delete(p) ;
	poly_show(p) ;



// TODO
//scale_test = 4x^3 + 2x^2+ 5x +3 
	poly_t * scale_test = poly_zero();
	poly_attach(scale_test,4.0,3);
	poly_attach(scale_test,2.0,2);
	poly_attach(scale_test,5.0,1);
	poly_attach(scale_test,3.0,0);
	printf("scale_test-->");
	poly_show(scale_test);

//p1 = x^2 + 2x+ 1
	poly_t * p1 = poly_zero();
	poly_attach(p1,1.0,2);
	poly_attach(p1,2.0,1);
	poly_attach(p1,1.0,0);
	printf("p1-->");
	poly_show(p1);

//p2 = 3x^2+1
	poly_t * p2 = poly_zero();
	poly_attach(p2,3.0,2);
	poly_attach(p2,0.0,1);
	poly_attach(p2,1.0,0);
	printf("p2-->");
	poly_show(p2);	

//scale
	printf("poly_scale-->");
	poly_scale(scale_test ,2);
	poly_show(scale_test);
//add
	poly_t * add_result = poly_add(p1,p2);
	printf("poly_add result-->");
	poly_show(add_result);

//sub
	 poly_t *sub_result = poly_sub(p1, p2);
    printf("poly_sub result--> ");
    poly_show(sub_result);

//mult
    poly_t *mult_result = poly_mult(p1, p2);
    printf("poly_mult result--> ");
    poly_show(mult_result);

//eval 
	double eval_result = poly_eval(p1,3);
	printf("poly_eval result-->%f\n", eval_result);
	

    poly_delete(p1);
    poly_delete(p2);
	poly_delete(add_result);
	poly_delete(sub_result);
	poly_delete(scale_test);
    poly_delete(mult_result);



	return EXIT_SUCCESS ;
}
